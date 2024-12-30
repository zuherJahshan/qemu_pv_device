
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

/* Driver Definitions */
#define DRV_NAME "zcdrv"
#define PCI_VENDOR_ID_QEMU 0x1234
#define PCI_DEVICE_ID_HUAWEI_ZCDEV 0x1122

#define CHAR_MAJOR  200
#define CHAR_MINOR  0

/* Structure to hold device-specific information */
struct zcdev {
    struct pci_dev *pdev;
    resource_size_t bar0;

    struct cdev cdev;
    dev_t devno;
    struct class *zcdev_class;

    /* DAX-related structures */
    struct dev_pagemap pgmap;
    struct dev_pagemap_ops pgmap_ops;
    void *mapped_addr; // Virtual address returned by devm_memremap_pages()
};

/* Memory Failure Callback */
static int zcdev_memory_failure(struct dev_pagemap *pgmap,
                                unsigned long pfn, unsigned long nr_pages,
                                int mf_flags)
{
    //struct zcdev *dev = container_of(pgmap, struct zcdev, pgmap);

    printk(KERN_ERR "zcdrv: Memory failure detected at pfn %lu, nr_pages %lu\n",
           pfn, nr_pages);

    /* Implement your memory failure handling here */
    /* For example, you might want to log the event or take corrective actions */

    return 0;
}

/* Define dev_pagemap_ops */
static const struct dev_pagemap_ops zcdev_dev_pagemap_ops = {
    .memory_failure = zcdev_memory_failure,
};

/* File Operations */

/* Open */
static int zcdev_char_open(struct inode *inode, struct file *filp)
{
    struct zcdev *dev;

    dev = container_of(inode->i_cdev, struct zcdev, cdev);
    filp->private_data = dev;

    printk(KERN_INFO "zcdrv: Device opened!\n");
    return 0;
}

/* Release */
static int zcdev_char_release(struct inode *inode, struct file *filp)
{
    printk(KERN_INFO "zcdrv: Device closed!\n");
    return 0;
}

/* Read */
static ssize_t zcdev_char_read(struct file *filp, char __user *buf,
                               size_t count, loff_t *f_pos)
{
    struct zcdev *dev = filp->private_data;
    size_t available;
    ssize_t ret;

    available = pci_resource_len(dev->pdev, 0) - *f_pos;
    if (count > available)
        count = available;

    if (count == 0)
        return 0;

    /* Copy data from device memory to userspace */
    ret = copy_to_user(buf, dev->mapped_addr + *f_pos, count);
    if (ret)
        return -EFAULT;

    *f_pos += count;
    return count;
}

/* Write */
static ssize_t zcdev_char_write(struct file *filp, const char __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct zcdev *dev = filp->private_data;
    size_t available;
    ssize_t ret;

    available = pci_resource_len(dev->pdev, 0) - *f_pos;
    if (count > available)
        count = available;

    if (count == 0)
        return -ENOSPC;

    /* Copy data from userspace to device memory */
    ret = copy_from_user(dev->mapped_addr + *f_pos, buf, count);
    if (ret)
        return -EFAULT;

    *f_pos += count;
    return count;
}

/* mmap */
static int zcdev_char_mmap(struct file *filp, struct vm_area_struct *vma)
{
    struct zcdev *dev = filp->private_data;
    unsigned long size = vma->vm_end - vma->vm_start;
    unsigned long pfn;
    unsigned long offset = vma->vm_pgoff << PAGE_SHIFT;

    /* Ensure the offset and size are within device memory */
    if (offset + size > pci_resource_len(dev->pdev, 0))
        return -EINVAL;

    /* Get the physical address of the device memory */
    phys_addr_t phys_addr = pci_resource_start(dev->pdev, 0) + offset;

    /* Convert physical address to page frame number */
    pfn = phys_addr >> PAGE_SHIFT;

    /* Remap the device memory to userspace */
    if (remap_pfn_range(vma, vma->vm_start, pfn, size, vma->vm_page_prot))
        return -EAGAIN;

    return 0;
}

/* Define file_operations structure */
static const struct file_operations char_fops = {
    .owner = THIS_MODULE,
    .open = zcdev_char_open,
    .release = zcdev_char_release,
    .read = zcdev_char_read,
    .write = zcdev_char_write,
    .mmap = zcdev_char_mmap,
};

/* PCI Driver Probe Function */
static int zcdev_pci_probe(struct pci_dev *pdev,
                           const struct pci_device_id *id)
{
    int rc;
    struct zcdev *dev;

    /* Allocate memory for the device structure */
    dev = devm_kzalloc(&pdev->dev, sizeof(*dev), GFP_KERNEL);
    if (!dev) {
        dev_err(&pdev->dev, "Failed to allocate memory for zcdev\n");
        return -ENOMEM;
    }

    /* Initialize PCI device */
    dev->pdev = pdev;
    pci_set_drvdata(pdev, dev);

    rc = pci_enable_device(pdev);
    if (rc) {
        dev_err(&pdev->dev, "Cannot enable PCI device\n");
        return rc;
    }

    /* Check if BAR0 is MMIO */
    if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM)) {
        dev_err(&pdev->dev, "PCI BAR0 is not MMIO\n");
        rc = -ENODEV;
        goto err_disable_pci;
    }

    dev_info(&pdev->dev, "PCI BAR0 %#llx (%lld bytes)\n",
             (unsigned long long)pci_resource_start(pdev, 0),
             (unsigned long long)pci_resource_len(pdev, 0));

    rc = pci_request_regions(pdev, DRV_NAME);
    if (rc) {
        dev_err(&pdev->dev, "Cannot request PCI regions\n");
        goto err_disable_pci;
    }

    /* Set DMA mask */
    rc = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
    if (rc) {
        dev_err(&pdev->dev, "dma_set_mask failed\n");
        goto err_release_regions;
    }
    dma_set_max_seg_size(&pdev->dev, UINT_MAX);
    pci_set_master(pdev);

    /* Initialize dev_pagemap */
    dev->pgmap_ops = zcdev_dev_pagemap_ops;
    dev->pgmap.ops = &dev->pgmap_ops;
    dev->pgmap.range.start = pci_resource_start(pdev, 0);
    dev->pgmap.range.end = pci_resource_start(pdev, 0) + pci_resource_len(pdev, 0) - 1;
    dev->pgmap.nr_range = 1;
    dev->pgmap.type = MEMORY_DEVICE_FS_DAX;

    /* Call devm_memremap_pages */
    dev->mapped_addr = devm_memremap_pages(&pdev->dev, &dev->pgmap);
    if (IS_ERR(dev->mapped_addr)) {
        dev_err(&pdev->dev, "devm_memremap_pages failed\n");
        rc = PTR_ERR(dev->mapped_addr);
        goto err_release_regions;
    }

    /* Create device class using class_create */
    dev->zcdev_class = class_create("zcdrv_class");
    if (IS_ERR(dev->zcdev_class)) {
        dev_err(&pdev->dev, "Failed to create device class\n");
        rc = PTR_ERR(dev->zcdev_class);
        goto err_memunmap;
    }

    /* Allocate device number */
    dev->devno = MKDEV(CHAR_MAJOR, CHAR_MINOR);
    rc = register_chrdev_region(dev->devno, 1, DRV_NAME);
    if (rc < 0) {
        dev_err(&pdev->dev, "Failed to register chrdev region\n");
        goto err_class_destroy;
    }

    /* Initialize and add cdev */
    cdev_init(&dev->cdev, &char_fops);
    dev->cdev.owner = THIS_MODULE;
    rc = cdev_add(&dev->cdev, dev->devno, 1);
    if (rc < 0) {
        dev_err(&pdev->dev, "Failed to add cdev\n");
        goto err_unregister_chrdev;
    }

    /* Create device node */
    if (device_create(dev->zcdev_class, &pdev->dev,
                      dev->devno, NULL, "zcdrv0") == NULL) {
        dev_err(&pdev->dev, "Failed to create device\n");
        rc = -ENOMEM;
        goto err_cdev_del;
    }

    dev_info(&pdev->dev, "zcdrv: Probed to device\n");
    return 0;

err_cdev_del:
    cdev_del(&dev->cdev);
err_unregister_chrdev:
    unregister_chrdev_region(dev->devno, 1);
err_class_destroy:
    class_destroy(dev->zcdev_class);
err_memunmap:
    memunmap(dev->mapped_addr);
err_release_regions:
    pci_release_regions(pdev);
err_disable_pci:
    pci_disable_device(pdev);
    return rc;
}

/* PCI Driver Remove Function */
static void zcdev_pci_remove(struct pci_dev *pdev)
{
    struct zcdev *dev = pci_get_drvdata(pdev);

    if (!dev)
        return;

    /* Destroy device node and class */
    device_destroy(dev->zcdev_class, dev->devno);
    class_destroy(dev->zcdev_class);

    /* Remove cdev and unregister device number */
    cdev_del(&dev->cdev);
    unregister_chrdev_region(dev->devno, 1);

    /* Unmap device memory */
    memunmap(dev->mapped_addr);

    /* Release PCI regions and disable device */
    pci_release_regions(pdev);
    pci_disable_device(pdev);

    dev_info(&pdev->dev, "zcdrv: Device removed\n");
}

/* PCI Device ID Table */
static const struct pci_device_id zcdev_pci_table[] = {
    { PCI_DEVICE(PCI_VENDOR_ID_QEMU, PCI_DEVICE_ID_HUAWEI_ZCDEV), },
    { 0 },
};
MODULE_DEVICE_TABLE(pci, zcdev_pci_table);

/* Define PCI Driver Structure */
static struct pci_driver zcdev_driver = {
    .name       = DRV_NAME,
    .id_table   = zcdev_pci_table,
    .probe      = zcdev_pci_probe,
    .remove     = zcdev_pci_remove,
};

/* Module Initialization */
static int __init zcdev_init(void)
{
    int rc;

    /* Register PCI driver */
    rc = pci_register_driver(&zcdev_driver);
    if (rc) {
        printk(KERN_ERR "zcdrv: Failed to register PCI driver\n");
        return rc;
    }

    printk(KERN_INFO "zcdrv: Module loaded\n");
    return 0;
}

/* Module Exit */
static void __exit zcdev_cleanup(void)
{
    /* Unregister PCI driver */
    pci_unregister_driver(&zcdev_driver);
    printk(KERN_INFO "zcdrv: Module unloaded\n");
}

module_init(zcdev_init);
module_exit(zcdev_cleanup);

MODULE_AUTHOR("Yuval Shaia <yuval.shaia@huawei.com>");
MODULE_DESCRIPTION("Huawei Paravirtual ZCdev driver with memremap_pages");
MODULE_LICENSE("Dual BSD/GPL");
