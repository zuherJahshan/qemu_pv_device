#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/dax.h>
#include <linux/memremap.h>
#include <linux/mm.h>         /* for PAGE_SIZE, virt_to_page, etc. */
#include <linux/highmem.h>    /* may be needed for virt_to_page */

#define DRV_NAME "zcdrv"
#define PCI_VENDOR_ID_QEMU 0x1234
#define PCI_DEVICE_ID_HUAWEI_ZCDEV 0x1122

#define CHAR_MAJOR  200
#define CHAR_MINOR  0

/* Our device structure */
struct zcdev {
    struct pci_dev          *pdev;
    resource_size_t         bar0;

    struct cdev             cdev;
    dev_t                   devno;
    struct class            *zcdev_class;

    /* DAX-related structures */
    struct dev_pagemap      pgmap;
    struct dev_pagemap_ops  pgmap_ops;
    void                    *mapped_addr; // Virtual address from devm_memremap_pages()
};

/* Memory failure callback */
static int zcdev_memory_failure(struct dev_pagemap *pgmap,
                                unsigned long pfn,
                                unsigned long nr_pages,
                                int mf_flags)
{
    /* If you need access to `struct zcdev`, you can do:
       struct zcdev *dev = container_of(pgmap, struct zcdev, pgmap);
       For now, we just log:
    */
    printk(KERN_ERR "zcdrv: Memory failure at pfn=%lu nr_pages=%lu\n",
           pfn, nr_pages);

    /* Handle memory failure appropriately here. */
    return 0;
}

/* dev_pagemap_ops structure */
static const struct dev_pagemap_ops zcdev_dev_pagemap_ops = {
    .memory_failure = zcdev_memory_failure,
};

/* File operations */

/* .open */
static int zcdev_char_open(struct inode *inode, struct file *filp)
{
    struct zcdev *dev = container_of(inode->i_cdev, struct zcdev, cdev);
    filp->private_data = dev;

    printk(KERN_INFO "zcdrv: Device opened!\n");
    return 0;
}

/* .release */
static int zcdev_char_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "zcdrv: Device closed!\n");
    return 0;
}

/* .read */
static ssize_t zcdev_char_read(struct file *filp, char __user *buf,
                               size_t count, loff_t *f_pos)
{
    struct zcdev *dev = filp->private_data;
    size_t available = pci_resource_len(dev->pdev, 0) - *f_pos;

    if (count > available)
        count = available;
    if (count == 0)
        return 0;

    if (copy_to_user(buf, dev->mapped_addr + *f_pos, count))
        return -EFAULT;

    *f_pos += count;
    return count;
}

/* .write */
static ssize_t zcdev_char_write(struct file *filp, const char __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct zcdev *dev = filp->private_data;
    size_t available = pci_resource_len(dev->pdev, 0) - *f_pos;

    if (count > available)
        count = available;
    if (count == 0)
        return -ENOSPC;

    if (copy_from_user(dev->mapped_addr + *f_pos, buf, count))
        return -EFAULT;

    *f_pos += count;
    return count;
}

/* .mmap - using virt_to_page + page_to_pfn in a while loop */
static int zcdev_char_mmap(struct file *filp, struct vm_area_struct *vma)
{
    struct zcdev *dev = filp->private_data;
    unsigned long size = vma->vm_end - vma->vm_start;
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;
    unsigned long vaddr;   /* kernel virtual address to map */
    unsigned long uaddr;   /* user-space address base */
    unsigned long rem;     /* how many bytes remain */
    int ret = 0;

    /* check bounds */
    if (offset + size > pci_resource_len(dev->pdev, 0))
        return -EINVAL;

    /* Starting addresses */
    vaddr = (unsigned long)dev->mapped_addr + offset; /* kernel VA */
    uaddr = vma->vm_start;                             /* user VA */
    rem = size;

    while (rem > 0) {
        /* map one page at a time */
        unsigned long map_size = PAGE_SIZE;
        struct page *page;
        unsigned long pfn;

        if (rem < PAGE_SIZE)
            map_size = rem;

        /* get struct page* from kernel VA */
        page = virt_to_page((void *)vaddr);
        /* get PFN from that page */
        pfn = page_to_pfn(page);

        /* actually map it */
        ret = remap_pfn_range(vma, uaddr, pfn, map_size, vma->vm_page_prot);
        if (ret) {
            printk(KERN_ERR "zcdrv: remap_pfn_range failed pfn=%lu\n", pfn);
            return ret;
        }

        vaddr += map_size;  /* advance kernel VA by one page */
        uaddr += map_size;  /* advance user VA */
        rem   -= map_size;
    }

    return 0;
}

/* File ops structure */
static const struct file_operations char_fops = {
    .owner   = THIS_MODULE,
    .open    = zcdev_char_open,
    .release = zcdev_char_release,
    .read    = zcdev_char_read,
    .write   = zcdev_char_write,
    .mmap    = zcdev_char_mmap,
};

/* PCI probe */
static int zcdev_pci_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
    int rc;
    struct zcdev *dev;

    dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev)
        return -ENOMEM;

    dev->pdev = pdev;
    pci_set_drvdata(pdev, dev);

    rc = pci_enable_device(pdev);
    if (rc)
        return rc;

    if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
        dev_err(&pdev->dev, "PCI BAR0 not MMIO\n");
        rc = -ENODEV;
        goto err_disable;
    }

    dev_info(&pdev->dev, "PCI BAR0 start=%#llx len=%llu\n",
             (unsigned long long)pci_resource_start(pdev, 0),
             (unsigned long long)pci_resource_len(pdev, 0));

    rc = pci_request_regions(pdev, DRV_NAME);
    if (rc)
        goto err_disable;

    rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
    if (rc) {
        dev_err(&pdev->dev, "dma_set_mask failed\n");
        goto err_release;
    }
    pci_set_master(pdev);

    dev->pgmap_ops = zcdev_dev_pagemap_ops;
    dev->pgmap.ops = &dev->pgmap_ops;
    dev->pgmap.range.start = pci_resource_start(pdev, 0);
    dev->pgmap.range.end   = pci_resource_start(pdev, 0)
                             + pci_resource_len(pdev, 0) - 1;
    dev->pgmap.nr_range    = 1;
    dev->pgmap.type        = MEMORY_DEVICE_FS_DAX;

    dev->mapped_addr = devm_memremap_pages(&pdev->dev, &dev->pgmap);
    if (IS_ERR(dev->mapped_addr)) {
        rc = PTR_ERR(dev->mapped_addr);
        dev_err(&pdev->dev, "devm_memremap_pages failed\n");
        goto err_release;
    }

    /* create class */
    dev->zcdev_class = class_create("zcdrv_class");
    if (IS_ERR(dev->zcdev_class)) {
        rc = PTR_ERR(dev->zcdev_class);
        dev_err(&pdev->dev, "class_create_simple failed\n");
        goto err_unmap;
    }

    dev->devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);
    rc = register_chrdev_region(dev->devno, 1, DRV_NAME);
    if (rc < 0) {
        dev_err(&pdev->dev, "register_chrdev_region failed\n");
        goto err_class;
    }

    cdev_init(&dev->cdev, &char_fops);
    dev->cdev.owner = THIS_MODULE;
    rc = cdev_add(&dev->cdev, dev->devno, 1);
    if (rc) {
        dev_err(&pdev->dev, "cdev_add failed\n");
        goto err_chreg;
    }

    if (!device_create(dev->zcdev_class, &pdev->dev, dev->devno,
                       NULL, "zcdrv0")) {
        dev_err(&pdev->dev, "device_create failed\n");
        rc = -ENOMEM;
        goto err_cdev;
    }

    dev_info(&pdev->dev, "zcdrv: Probed successfully\n");
    return 0;

err_cdev:
    cdev_del(&dev->cdev);
err_chreg:
    unregister_chrdev_region(dev->devno, 1);
err_class:
    class_destroy(dev->zcdev_class);
err_unmap:
    memunmap(dev->mapped_addr);
err_release:
    pci_release_regions(pdev);
err_disable:
    pci_disable_device(pdev);
    return rc;
}

static void zcdev_pci_remove(struct pci_dev *pdev)
{
    struct zcdev *dev = pci_get_drvdata(pdev);

    if (!dev)
        return;

    device_destroy(dev->zcdev_class, dev->devno);
    class_destroy(dev->zcdev_class);
    cdev_del(&dev->cdev);
    unregister_chrdev_region(dev->devno, 1);

    memunmap(dev->mapped_addr);
    pci_release_regions(pdev);
    pci_disable_device(pdev);

    dev_info(&pdev->dev, "zcdrv: Device removed\n");
}

static const struct pci_device_id zcdev_pci_table[] = {
    { PCI_DEVICE(PCI_VENDOR_ID_QEMU, PCI_DEVICE_ID_HUAWEI_ZCDEV), },
    { 0 },
};
MODULE_DEVICE_TABLE(pci, zcdev_pci_table);

static struct pci_driver zcdev_driver = {
    .name     = DRV_NAME,
    .id_table = zcdev_pci_table,
    .probe    = zcdev_pci_probe,
    .remove   = zcdev_pci_remove,
};

static int __init zcdev_init(void)
{
    int rc = pci_register_driver(&zcdev_driver);
    if (rc)
        pr_err("zcdrv: pci_register_driver failed\n");
    else
        pr_info("zcdrv: Module loaded\n");
    return rc;
}

static void __exit zcdev_cleanup(void)
{
    pci_unregister_driver(&zcdev_driver);
    pr_info("zcdrv: Module unloaded\n");
}

module_init(zcdev_init);
module_exit(zcdev_cleanup);

MODULE_AUTHOR("Zuher Jahshan <zuher.jahshan@huawei.com>");
MODULE_DESCRIPTION("Huawei Paravirtual ZCdev driver with memremap_pages, page-by-page mmap");
MODULE_LICENSE("Dual BSD/GPL");
