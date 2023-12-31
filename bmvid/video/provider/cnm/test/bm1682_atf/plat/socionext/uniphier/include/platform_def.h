/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __PLATFORM_DEF_H__
#define __PLATFORM_DEF_H__

#include <common_def.h>
#include <tbbr/tbbr_img_def.h>

#define PLATFORM_STACK_SIZE        0x1000

#define CACHE_WRITEBACK_SHIFT        6
#define CACHE_WRITEBACK_GRANULE        (1 << (CACHE_WRITEBACK_SHIFT))

/* topology */
#define UNIPHIER_MAX_CPUS_PER_CLUSTER    4
#define UNIPHIER_CLUSTER_COUNT        2

#define PLATFORM_CORE_COUNT        \
    ((UNIPHIER_MAX_CPUS_PER_CLUSTER) * (UNIPHIER_CLUSTER_COUNT))

#define PLAT_MAX_PWR_LVL        1

#define PLAT_MAX_OFF_STATE        2
#define PLAT_MAX_RET_STATE        1

#define UNIPHIER_SEC_DRAM_BASE        0x81000000
#define UNIPHIER_SEC_DRAM_LIMIT        0x82000000
#define UNIPHIER_SEC_DRAM_SIZE        ((UNIPHIER_SEC_DRAM_LIMIT) - \
                     (UNIPHIER_SEC_DRAM_BASE))

#define BL1_RO_BASE            0x80000000
#define BL1_RO_LIMIT            0x80018000
#define BL1_RW_LIMIT            (UNIPHIER_SEC_DRAM_LIMIT)
#define BL1_RW_BASE            ((BL1_RW_LIMIT) - 0x00040000)

#define BL2_LIMIT            (BL1_RW_BASE)
#define BL2_BASE            ((BL2_LIMIT) - 0x00040000)

#define BL31_BASE            (UNIPHIER_SEC_DRAM_BASE)
#define BL31_LIMIT            ((BL31_BASE) + 0x00080000)

#define BL32_BASE            (BL31_LIMIT)
#define BL32_LIMIT            (UNIPHIER_SEC_DRAM_LIMIT)

#define UNIPHIER_BLOCK_BUF_SIZE        0x00400000
#define UNIPHIER_BLOCK_BUF_BASE        ((BL2_LIMIT) - \
                     (UNIPHIER_BLOCK_BUF_SIZE))

#define PLAT_PHY_ADDR_SPACE_SIZE    (1ULL << 32)
#define PLAT_VIRT_ADDR_SPACE_SIZE    (1ULL << 32)

#define PLAT_XLAT_TABLES_DYNAMIC    1
#define MAX_XLAT_TABLES            7
#define MAX_MMAP_REGIONS        6

#define MAX_IO_HANDLES            2
#define MAX_IO_DEVICES            2
#define MAX_IO_BLOCK_DEVICES        1

#define TSP_SEC_MEM_BASE        (BL32_BASE)
#define TSP_SEC_MEM_SIZE        ((BL32_LIMIT) - (BL32_BASE))
#define TSP_PROGBITS_LIMIT        (UNIPHIER_BLOCK_BUF_BASE)
#define TSP_IRQ_SEC_PHY_TIMER        29

#endif /* __PLATFORM_DEF_H__ */
