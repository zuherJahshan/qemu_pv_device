#include <linux/module.h>
#include <linux/init.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/mm.h>
#include <linux/memremap.h>
#include <linux/pgmap.h>
#include <linux/uaccess.h>

#define DRV_NAME "zcdrv"
#define PCI_VENDOR_ID_QEMU 0x1234
#define PCI_DEVICE_ID_HUAWEI_ZCDEV 0x1122

#define CHAR_MAJOR  200
#define CHAR_MINOR  0

static struct cdev zcdev_cdev;

struct zcdev {
	struct pci_dev        *pdev;
	void __iomem          *mmio_base;  /* Optional kernel mapping */
	resource_size_t       bar_start;
	resource_size_t       bar_len;

	/* dev_pagemap used to create struct pages in ZONE_DEVICE */
	struct dev_pagemap    pgmap;
	/* The virtual address returned by memremap_pages() */
	void                  *zone_device_vaddr;
};

static struct zcdev *global_zcdev;

/* ------------------------------------------------------------------
 *  dev_pagemap_ops callbacks
 * ------------------------------------------------------------------ */

static void zcdev_page_free(struct page *page)
{
	/*
	 * Called when the page reference count drops to zero.
	 * For a simple device memory region, we might do nothing special,
	 * or we might notify hardware, etc. For demonstration, do nothing.
	 */
}

static vm_fault_t zcdev_memory_failure(struct dev_pagemap *pgmap,
				       unsigned long pfn, int flags)
{
	pr_err("zcdrv: Memory failure at pfn=0x%lx\n", pfn);
	/*
	 * We could attempt to offline the bad page, etc. For demonstration,
	 * just log an error. Return 0 to indicate we handled it.
	 */
	return 0;
}

static const struct dev_pagemap_ops zcdev_pgmap_ops = {
	.page_free       = zcdev_page_free,
	.memory_failure  = zcdev_memory_failure,
};

/* ------------------------------------------------------------------
 *  Character device file operations
 * ------------------------------------------------------------------ */

static int zcdev_char_open(struct inode *inode, struct file *filp)
{
	pr_info("zcdrv: Device opened\n");
	filp->private_data = global_zcdev;  /* store pointer to our device */
	return 0;
}

static int zcdev_char_release(struct inode *inode, struct file *filp)
{
	pr_info("zcdrv: Device closed\n");
	return 0;
}

/* Optional read/write placeholders */
static ssize_t zcdev_char_read(struct file *filp, char __user *buf,
			       size_t count, loff_t *f_pos)
{
	pr_info("zcdrv: read called (stub)\n");
	return 0;
}

static ssize_t zcdev_char_write(struct file *filp, const char __user *buf,
				size_t count, loff_t *f_pos)
{
	pr_info("zcdrv: write called (stub)\n");
	return count;
}

/*
 * .mmap: map the ZONE_DEVICE memory into user space.
 * We'll demonstrate a simple approach using vm_insert_page.
 */
static int zcdev_char_mmap(struct file *filp, struct vm_area_struct *vma)
{
	struct zcdev *dev = filp->private_data;
	unsigned long vsize = vma->vm_end - vma->vm_start;
	unsigned long pfn_start;
	unsigned long pfn;
	unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
	unsigned long uaddr;
	unsigned long i;

	pr_info("zcdrv: mmap called\n");

	/* Basic range check: do not allow mapping beyond 1GB. */
	if (offset + vsize > dev->bar_len) {
		pr_err("zcdrv: mapping beyond device range\n");
		return -EINVAL;
	}

	/*
	 * The dev_pagemap has created struct pages in ZONE_DEVICE starting at
	 * dev->pgmap.range.start. The PFN base is range.start >> PAGE_SHIFT.
	 */
	pfn_start = dev->pgmap.range.start >> PAGE_SHIFT;  /* first PFN */

	/*
	 * The user's offset is offset>>PAGE_SHIFT pages into the device's region.
	 * So the first PFN for this mapping is pfn_start + (offset >> PAGE_SHIFT).
	 */
	pfn = pfn_start + (offset >> PAGE_SHIFT);

	/* We'll manually insert each page into the VMA. */
	uaddr = vma->vm_start;

	for (i = 0; i < vsize; i += PAGE_SIZE) {
		int ret;
		ret = vm_insert_page(vma, uaddr, pfn_to_page(pfn));
		if (ret) {
			pr_err("zcdrv: vm_insert_page failed at i=%lu\n", i);
			return ret;
		}

		uaddr += PAGE_SIZE;
		pfn   += 1;
	}

	return 0;
}

static const struct file_operations zcdev_fops = {
	.owner   = THIS_MODULE,
	.open    = zcdev_char_open,
	.release = zcdev_char_release,
	.read    = zcdev_char_read,
	.write   = zcdev_char_write,
	.mmap    = zcdev_char_mmap,
};

/* ------------------------------------------------------------------
 *  PCI probe/remove
 * ------------------------------------------------------------------ */

static int zcdev_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *id)
{
	int rc;
	struct zcdev *dev;
	resource_size_t bar_start, bar_len;
	void *vaddr;
	struct dev_pagemap *pgmap;

	pr_info("zcdrv: PCI probe\n");

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev)
		return -ENOMEM;
	global_zcdev = dev; /* store pointer globally for our char dev */

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		goto err_alloc;
	}

	/* Request and map the BAR that we want to treat as device memory. */
	bar_start = pci_resource_start(pdev, 0);
	bar_len   = pci_resource_len(pdev, 0);

	/* For demonstration, assume bar_len == 1GB, or at least enough. */
	if (bar_len < (1ULL << 30)) {
		dev_err(&pdev->dev, "BAR0 is smaller than 1GB: %pa\n", &bar_len);
		rc = -ENODEV;
		goto err_disable;
	}

	rc = pci_request_regions(pdev, DRV_NAME);
	if (rc) {
		dev_err(&pdev->dev, "cannot request PCI regions\n");
		goto err_disable;
	}

	dev->bar_start = bar_start;
	dev->bar_len   = bar_len;

	/*
	 * Optionally (NOT strictly required for ZONE_DEVICE usage),
	 * we can do a standard ioremap for kernel read/write (for debugging).
	 */
	dev->mmio_base = ioremap(bar_start, bar_len);
	if (!dev->mmio_base) {
		dev_err(&pdev->dev, "ioremap failed\n");
		rc = -ENOMEM;
		goto err_regions;
	}

	/*
	 * Set up dev_pagemap so the kernel creates struct pages in ZONE_DEVICE
	 * for this 1GB region.
	 */
	pgmap = &dev->pgmap;
	memset(pgmap, 0, sizeof(*pgmap));

	/* We'll track exactly 1GB for demonstration. */
	pgmap->res.start = bar_start;
	pgmap->res.end   = bar_start + (1ULL << 30) - 1; /* 1GB range */
	pgmap->res.flags = IORESOURCE_MEM;
	pgmap->ops       = (struct dev_pagemap_ops *)&zcdev_pgmap_ops;
	pgmap->type      = PGMAP_DEVICE; /* generic device memory */
	pgmap->dev       = &pdev->dev;   /* link to your struct device */

	/*
	 * memremap_pages() creates the ZONE_DEVICE pages.
	 * On success, we get a CPU VA pointer that can be used in the kernel.
	 * (Similar to ioremap, but with struct pages allocated in ZONE_DEVICE.)
	 */
	vaddr = memremap_pages(pgmap);
	if (IS_ERR(vaddr)) {
		dev_err(&pdev->dev, "memremap_pages() failed\n");
		rc = PTR_ERR(vaddr);
		goto err_unmap;
	}
	dev->zone_device_vaddr = vaddr;

	dev_info(&pdev->dev, "Mapped 1GB device memory into ZONE_DEVICE\n");
	return 0;

err_unmap:
	iounmap(dev->mmio_base);
err_regions:
	pci_release_regions(pdev);
err_disable:
	pci_disable_device(pdev);
err_alloc:
	devm_kfree(&pdev->dev, dev);
	global_zcdev = NULL;
	return rc;
}

static void zcdev_pci_remove(struct pci_dev *pdev)
{
	struct zcdev *dev = pci_get_drvdata(pdev);

	pr_info("zcdrv: PCI remove\n");
	if (!dev)
		return;

	if (dev->zone_device_vaddr) {
		/* Undo the memremap_pages. */
		memunmap_pages(&dev->pgmap);
		dev->zone_device_vaddr = NULL;
	}

	if (dev->mmio_base)
		iounmap(dev->mmio_base);

	pci_release_regions(pdev);
	pci_disable_device(pdev);

	devm_kfree(&pdev->dev, dev);
	global_zcdev = NULL;
}

static const struct pci_device_id zcdev_pci_table[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_QEMU, PCI_DEVICE_ID_HUAWEI_ZCDEV), },
	{ 0 },
};

MODULE_DEVICE_TABLE(pci, zcdev_pci_table);

static struct pci_driver zcdev_pci_driver = {
	.name     = DRV_NAME,
	.id_table = zcdev_pci_table,
	.probe    = zcdev_pci_probe,
	.remove   = zcdev_pci_remove,
};

/* ------------------------------------------------------------------
 *  Module init/exit for the char device + PCI driver
 * ------------------------------------------------------------------ */

static int __init zcdev_module_init(void)
{
	int rc;
	dev_t devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);

	pr_info("zcdrv: module init\n");

	rc = register_chrdev_region(devno, 1, DRV_NAME);
	if (rc < 0) {
		pr_err("zcdrv: failed to register chardev region\n");
		return rc;
	}

	cdev_init(&zcdev_cdev, &zcdev_fops);
	rc = cdev_add(&zcdev_cdev, devno, 1);
	if (rc) {
		pr_err("zcdrv: failed to add chardev\n");
		goto err_chr_region;
	}

	pr_info("zcdrv: create device node with 'mknod /dev/%s_0 c %d 0'\n",
		DRV_NAME, CHAR_MAJOR);

	rc = pci_register_driver(&zcdev_pci_driver);
	if (rc) {
		pr_err("zcdrv: failed to register pci driver\n");
		goto err_cdev_add;
	}

	return 0;

err_cdev_add:
	cdev_del(&zcdev_cdev);
err_chr_region:
	unregister_chrdev_region(devno, 1);
	return rc;
}

static void __exit zcdev_module_exit(void)
{
	dev_t devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);

	pr_info("zcdrv: module exit\n");

	pci_unregister_driver(&zcdev_pci_driver);

	cdev_del(&zcdev_cdev);
	unregister_chrdev_region(devno, 1);
}

module_init(zcdev_module_init);
module_exit(zcdev_module_exit);

MODULE_AUTHOR("Example");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_DESCRIPTION("Huawei Paravirtual ZCdev driver (ZONE_DEVICE example)");
