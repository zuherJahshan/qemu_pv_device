
/*
 * Zero Copy paravirtual device
 *
 * Copyright (C) 2023 Huawei
 *
 * Authors:
 *     Yuval Shaia <yuval.shaia@huawei.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2 or later.
 * See the COPYING file in the top-level directory.
 *
 */

#include "qemu/osdep.h"
#include "qapi/error.h"
#include "qemu/module.h"
#include "hw/pci/pci.h"
#include "hw/pci/pci_ids.h"
#include "hw/pci/msi.h"
#include "hw/pci/msix.h"
#include "hw/qdev-properties.h"
#include "hw/qdev-properties-system.h"
#include "cpu.h"
#include "monitor/monitor.h"
#include "sysemu/runstate.h"
#include "qemu/log.h"

#define INTERFACE_ZCDEV_PROVIDER "zcdev"
#define BAR0_REGS_SIZE (2 << 29)
#define ZCDEV_REG_BAR_IDX 0

#define ZCDEV_VERSION 0x1

struct ZCDev {
    PCIDevice parent_obj;
    MemoryRegion regs;
    uint8_t regs_data[BAR0_REGS_SIZE];
};

typedef struct ZCDev ZCDev;
DECLARE_INSTANCE_CHECKER(ZCDev, ZCDEV_DEV, "zcdev")

typedef struct ZcdevProviderClass ZcdevProviderClass;
DECLARE_CLASS_CHECKERS(ZcdevProviderClass, ZCDEV_PROVIDER,
                       INTERFACE_ZCDEV_PROVIDER)
#define ZCDEV_PROVIDER(obj) \
    INTERFACE_CHECK(ZcdevProvider, (obj), \
                    INTERFACE_ZCDEV_PROVIDER)

typedef struct ZcdevProvider ZcdevProvider;

struct ZcdevProviderClass {
    InterfaceClass parent;

    void (*format_statistics)(ZcdevProvider *obj, GString *buf);
};


static uint64_t zcdev_regs_read(void *opaque, hwaddr addr, unsigned size)
{
    ZCDev *dev = opaque;

    if (addr > BAR0_REGS_SIZE) {
        qemu_log("zcdev: read out of bounds (addr=0x%"HWADDR_PRIx"\n", addr);
        return 0xfffffff;
    }

    qemu_log("zcdev: Read from addr=0x%"HWADDR_PRIx", size=%u, value=0x%x\n",
        addr, size, dev->regs_data[addr]);

    return dev->regs_data[addr];
}

static void zcdev_regs_write(void *opaque, hwaddr addr, uint64_t val,
                             unsigned size)
{
    ZCDev *dev = opaque;

    if (addr > BAR0_REGS_SIZE) {
        qemu_log("zcdev: Write out of bounds (addr=0x%"HWADDR_PRIx")\n", addr);
        return;
    }

    dev->regs_data[addr] = val;
    qemu_log("zcdev: Write to addr=0x%"HWADDR_PRIx", size=%u, value=0x%"PRIx64"\n",
        addr, size, val);
}

static const MemoryRegionOps regs_ops = {
    .read = zcdev_regs_read,
    .write = zcdev_regs_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .impl = {
        .min_access_size = sizeof(uint8_t),
        .max_access_size = sizeof(uint8_t),
    },
};

static void zcdev_realize(PCIDevice *pdev, Error **errp)
{
    ZCDev *dev = ZCDEV_DEV(pdev);

    pdev->config[PCI_INTERRUPT_PIN] = 1;

    memset(&dev->regs_data, 0, sizeof(dev->regs_data));
    memory_region_init_io(&dev->regs, OBJECT(dev), &regs_ops, dev,
                          "zcdev-regs", sizeof(dev->regs_data));
    pci_register_bar(
        pdev,
        ZCDEV_REG_BAR_IDX,
        PCI_BASE_ADDRESS_SPACE_MEMORY | PCI_BASE_ADDRESS_MEM_TYPE_64,
        &dev->regs
    );
}

static void zcdev_class_init(ObjectClass *klass, void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    PCIDeviceClass *k = PCI_DEVICE_CLASS(klass);
    /* ZcdevProviderClass *ir = ZCDEV_PROVIDER_CLASS(klass); */

    k->realize = zcdev_realize;
    k->vendor_id = PCI_VENDOR_ID_QEMU;
    k->device_id = 0x1122;
    k->revision = 0x00;
    k->class_id = PCI_CLASS_MEMORY_OTHER;

    dc->desc = "ZC Device";
    set_bit(DEVICE_CATEGORY_NETWORK, dc->categories);
}

static const TypeInfo zcdev_info = {
    .name = INTERFACE_ZCDEV_PROVIDER,
    .parent = TYPE_PCI_DEVICE,
    .instance_size = sizeof(ZCDev),
    .class_init = zcdev_class_init,
    .interfaces = (InterfaceInfo[]) {
        { INTERFACE_CONVENTIONAL_PCI_DEVICE },
        { INTERFACE_ZCDEV_PROVIDER },
        { }
    }
};

static void register_types(void)
{
    type_register_static(&zcdev_info);
}

type_init(register_types)
