#include <linux/errno.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define DRV_NAME "zcdrv"
#define PCI_VENDOR_ID_QEMU 0x1234
#define PCI_DEVICE_ID_HUAWEI_ZCDEV 0x1122

#define CHAR_MAJOR  200
#define CHAR_MINOR  0

struct cdev zcdev_cdev;
struct zcdev *zcdev;
resource_size_t bar0;

struct zcdev_dsr {
	uint64_t data_dma;
};

struct zcdev {
	struct pci_dev *pdev;
	void __iomem *regs;
	dma_addr_t dsr_dma;
	struct zcdev_dsr *dsr_virt;
	void *data_virt;

	struct kobj_attribute zcdev_sysfs_attr;
	struct kobject *zcdev_sysfs_kobj;
};

static ssize_t zcdev_data_show(struct kobject *kobj,
			       struct kobj_attribute *attr, char *buf)
{
	struct zcdev *dev = container_of(attr, struct zcdev, zcdev_sysfs_attr);

        return sprintf(buf, "%s\n", (char *)dev->regs);
}

static ssize_t zcdev_data_store(struct kobject *kobj,
				struct kobj_attribute *attr, const char *buf,
				size_t count)
{
	struct zcdev *dev = container_of(attr, struct zcdev, zcdev_sysfs_attr);

	memcpy((char *)dev->regs, buf, count);
	((char *)dev->regs)[count] = 0;

        return count;
}

static int zcdev_create_sysfs(struct zcdev *dev)
{
	int rc;

	dev->zcdev_sysfs_kobj = kobject_create_and_add(DRV_NAME, kernel_kobj);
	if (!dev->zcdev_sysfs_kobj)
		return -ENOMEM;

	dev->zcdev_sysfs_attr.attr.name = "data";
	dev->zcdev_sysfs_attr.attr.mode = S_IWUSR | S_IRUGO;
	dev->zcdev_sysfs_attr.show = zcdev_data_show;
	dev->zcdev_sysfs_attr.store = zcdev_data_store;
	sysfs_attr_init(&dev->zcdev_sysfs_attr.attr);

	rc = sysfs_create_file(dev->zcdev_sysfs_kobj, &dev->zcdev_sysfs_attr.attr);
	if (rc) {
		dev_err(&dev->pdev->dev, "Fail to create sysfs file\n");
		kobject_put(dev->zcdev_sysfs_kobj);
		dev->zcdev_sysfs_kobj = NULL;
	}

	return rc;
}

static void zcdev_destroy_sysfs(struct zcdev *dev)
{
	if (dev->zcdev_sysfs_kobj)
		kobject_put(dev->zcdev_sysfs_kobj);
}

/*
static inline void zcdev_write_reg(struct zcdev *dev, u32 reg, u32 val)
{
	writel(cpu_to_le32(val), dev->regs + reg);
}

static inline u32 zcdev_read_reg(struct zcdev *dev, u32 reg)
{
	return le32_to_cpu(readl(dev->regs + reg));
}

static inline void cp_to_dev(void __iomem *regs, char *data, u32 sz)
{
	int i;
	for (i = 0; i < sz; i++)
		writel(*(data + i), regs + i);
}
static inline void cp_from_dev(char *data, void __iomem *regs, u32 sz)
{
	int i;
	for (i = 0; i < sz; i++)
		*(data + i) = readl(regs + i);
}
*/
char *p;

static int zcdev_pci_probe(struct pci_dev *pdev,
			   const struct pci_device_id *id)
{
	int rc = -EIO;
	struct zcdev *dev;

	dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
	if (!dev) {
		dev_err(&pdev->dev, "Fail to alloc memory for zcdev\n");
		return -EIO;
	}

	/* Save in global so it can be accesible from char devops */
	zcdev = dev;

	dev->pdev = pdev;
	pci_set_drvdata(pdev, dev);

	rc = pci_enable_device(pdev);
	if (rc) {
		dev_err(&pdev->dev, "cannot enable PCI device\n");
		goto err_free_dev;
	}

	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
		dev_err(&pdev->dev, "PCI BAR region not MMIO\n");
		goto err_disable_pdev;
	}

	dev_info(&pdev->dev, "PCI BAR0 %#llx (%lld)\n",
		 (unsigned long long)pci_resource_start(pdev, 0),
		 (unsigned long long)pci_resource_len(pdev, 0));

	rc = pci_request_regions(pdev, DRV_NAME);
	if (rc) {
		dev_err(&pdev->dev, "cannot request PCI resources\n");
		goto err_disable_pdev;
	}

	rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (rc) {
		dev_err(&pdev->dev, "dma_set_mask failed\n");
		goto err_free_regions;
	}
	dma_set_max_seg_size(&pdev->dev, UINT_MAX);
	pci_set_master(pdev);

	rc = -ENOMEM;

	dev->regs = ioremap(pci_resource_start(pdev, 0),
			    pci_resource_len(pdev, 0));
	if (!dev->regs) {
		dev_err(&pdev->dev, "ioremap failed\n");
		goto err_free_regions;
	}

	bar0 = pci_resource_start(pdev, 0);
	dev_info(&pdev->dev, "data1: %s\n", (char *)dev->regs);
	strcpy((char *)dev->regs, "test3");
	dev_info(&pdev->dev, "data2: %s\n", (char *)dev->regs);

	zcdev_create_sysfs(dev);
	dev_info(&pdev->dev, "Probed to device\n");

	p = kmalloc(1024, GFP_KERNEL);

	return 0;

err_free_regions:
	pci_release_regions(pdev);

err_disable_pdev:
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

err_free_dev:
	devm_kfree(&pdev->dev, dev);

	return rc;
}

static void zcdev_pci_remove(struct pci_dev *pdev)
{
	struct zcdev *dev = pci_get_drvdata(pdev);

	kfree(p);

	if (!dev)
		return;

	dev_info(&pdev->dev, "Unprobing from device\n");

	zcdev_destroy_sysfs(dev);

	if (dev->data_virt)
		dma_free_coherent(&pdev->dev, PAGE_SIZE, dev->data_virt,
				  dev->dsr_virt->data_dma);

	if (dev->dsr_virt)
		dma_free_coherent(&pdev->dev, sizeof(*dev->dsr_virt),
				  dev->dsr_virt, dev->dsr_dma);

	iounmap(dev->regs);

	pci_release_regions(pdev);
	pci_disable_device(pdev);
	pci_set_drvdata(pdev, NULL);

	devm_kfree(&pdev->dev, dev);
}

static const struct pci_device_id zcdev_pci_table[] = {
	{ PCI_DEVICE(PCI_VENDOR_ID_QEMU, PCI_DEVICE_ID_HUAWEI_ZCDEV), },
	{ 0 },
};

MODULE_DEVICE_TABLE(pci, zcdev_pci_table);

static struct pci_driver zcdev_driver = {
	.name		= DRV_NAME,
	.id_table	= zcdev_pci_table,
	.probe		= zcdev_pci_probe,
	.remove		= zcdev_pci_remove,
};

static int zcdev_char_open(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Device opened!\n");

	return 0;
}

static int zcdev_char_release(struct inode *inode, struct file *filp)
{
	printk(KERN_INFO "Device closed!\n");

	return 0;
}

static ssize_t zcdev_char_read(struct file *filp, char __user *buf,
			       size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "%s\n", __func__);

	return 0;
}

static ssize_t zcdev_char_write(struct file *filp, const char __user *buf,
				size_t count, loff_t *f_pos)
{
	printk(KERN_INFO "%s\n", __func__);

	return 0;
}

static int zcdev_char_mmap(struct file *filp, struct vm_area_struct *vma)
{
	//unsigned long pfn, len;
	int rc;

	printk(KERN_INFO "%s\n", __func__);

	rc = vm_iomap_memory(vma, bar0, 1024);
	if (rc < 0) {
		printk(KERN_INFO "error in %s\n", "vm_iomap_memory");
		return -1;
	}

	//vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);

	//pfn = virt_to_phys((void *)zcdev->regs) >> PAGE_SHIFT;

	/*
	strcpy(p, "test");
	printk(KERN_INFO "%s\n", p);
	pfn = virt_to_phys((void *)p) >> PAGE_SHIFT;
	printk(KERN_INFO "pfn=%ld\n", pfn);
	len = vma->vm_end - vma->vm_start;
	printk(KERN_INFO "len=%ld\n", len);
	rc = remap_pfn_range(vma, vma->vm_start, pfn, len, vma->vm_page_prot);
	if (rc < 0) {
		printk(KERN_INFO "error in %s\n", "remap_pfn_range");
		return -1;
	}
	*/

	return 0;
}

static const struct file_operations char_fops = {
    .owner = THIS_MODULE,
    .open = zcdev_char_open,
    .release = zcdev_char_release,
    .read = zcdev_char_read,
    .write = zcdev_char_write,
    .mmap = zcdev_char_mmap,
};

static int zcdev_char_init(void)
{
	dev_t devno;
	int rc;

	devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);
	register_chrdev_region(devno, 1 , DRV_NAME);

	// Create a cdev structure
	cdev_init(&zcdev_cdev, &char_fops);
	zcdev_cdev.owner = THIS_MODULE;
	rc = cdev_add(&zcdev_cdev, devno, 1);
	if (rc < 0) {
		printk(KERN_ERR "Failed to add character device\n");
		goto err_cdev_add;
	}

	printk("'mknod /dev/%s_0 c %d 0'.\n", DRV_NAME, CHAR_MAJOR);

	printk(KERN_INFO "Device initialized\n");
	return 0;

err_cdev_add:
	return -1;
}

static void zcdev_char_exit(void)
{
	dev_t devno;

	devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);
	unregister_chrdev_region(devno, 1);
	cdev_del(&zcdev_cdev);

	printk(KERN_INFO "Device removed\n");
}

static int __init zcdev_init(void)
{
	int rc;

	rc = zcdev_char_init();
	if (rc) {
		printk(KERN_ERR "zcdev_char_init\n");
		return rc;
	}

	rc = pci_register_driver(&zcdev_driver);
	if (rc) {
		printk(KERN_ERR "pci_register_driver\n");
		return rc;
	}


	return rc;
}

static void __exit zcdev_cleanup(void)
{
	pci_unregister_driver(&zcdev_driver);
	zcdev_char_exit();
}

module_init(zcdev_init);
module_exit(zcdev_cleanup);

MODULE_AUTHOR("Yuval Shaia <yuval.shaia@huawei.com>");
MODULE_DESCRIPTION("Huawei Paravirtual ZCdev driver");
MODULE_LICENSE("Dual BSD/GPL");
