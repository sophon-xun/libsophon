/*
 * Copyright (c) 2015-2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch_helpers.h>
#include <bl_common.h>
#include <platform_def.h>
#include <bm_private.h>
#include <xlat_tables.h>

#define MAP_DEVICE0    MAP_REGION_FLAT(DEVICE0_BASE,            \
                    DEVICE0_SIZE,            \
                    MT_DEVICE | MT_RW | MT_SECURE)

#ifdef DEVICE1_BASE
#define MAP_DEVICE1    MAP_REGION_FLAT(DEVICE1_BASE,            \
                    DEVICE1_SIZE,            \
                    MT_DEVICE | MT_RW | MT_SECURE)
#endif

#ifdef DEVICE2_BASE
#define MAP_DEVICE2    MAP_REGION_FLAT(DEVICE2_BASE,            \
                    DEVICE2_SIZE,            \
                    MT_DEVICE | MT_RO | MT_SECURE)
#endif

#define MAP_SHARED_RAM    MAP_REGION_FLAT(SHARED_RAM_BASE,        \
                    SHARED_RAM_SIZE,        \
                    MT_DEVICE  | MT_RW | MT_SECURE)

#define MAP_NS_DRAM0    MAP_REGION_FLAT(NS_DRAM0_BASE, NS_DRAM0_SIZE,    \
                    MT_MEMORY | MT_RW | MT_NS)

#ifdef BL1_USE_CLI
#define MAP_FLASH0    MAP_REGION_FLAT(BM_FLASH0_BASE, BM_FLASH0_SIZE, \
                    MT_MEMORY | MT_RW | MT_SECURE)
#else
#define MAP_FLASH0    MAP_REGION_FLAT(BM_FLASH0_BASE, BM_FLASH0_SIZE, \
                    MT_MEMORY | MT_RO | MT_SECURE)
#endif

/*
 * Table of regions for various BL stages to map using the MMU.
 * This doesn't include TZRAM as the 'mem_layout' argument passed to
 * arm_configure_mmu_elx() will give the available subset of that,
 */
#ifdef IMAGE_BL1
static const mmap_region_t plat_bm_mmap[] = {
    MAP_FLASH0,
    MAP_SHARED_RAM,
    MAP_DEVICE0,
#ifdef MAP_DEVICE1
    MAP_DEVICE1,
#endif
#ifdef MAP_DEVICE2
    MAP_DEVICE2,
#endif
#ifdef BL1_USE_CLI
    MAP_NS_DRAM0,
#endif
    {0}
};
#endif
#ifdef IMAGE_BL2
static const mmap_region_t plat_bm_mmap[] = {
    MAP_FLASH0,
    MAP_SHARED_RAM,
    MAP_DEVICE0,
#ifdef MAP_DEVICE1
    MAP_DEVICE1,
#endif
#ifdef MAP_DEVICE2
    MAP_DEVICE2,
#endif
    MAP_NS_DRAM0,
    {0}
};
#endif
#ifdef IMAGE_BL31
static const mmap_region_t plat_bm_mmap[] = {
    MAP_SHARED_RAM,
    MAP_DEVICE0,
#ifdef MAP_DEVICE1
    MAP_DEVICE1,
#endif
    MAP_NS_DRAM0,
    {0}
};
#endif

/*******************************************************************************
 * Macro generating the code for the function setting up the pagetables as per
 * the platform memory map & initialize the mmu, for the given exception level
 ******************************************************************************/

#define DEFINE_CONFIGURE_MMU_EL(_el)                    \
    void bm_configure_mmu_el##_el(unsigned long total_base,    \
                   unsigned long total_size,        \
                   unsigned long ro_start,        \
                   unsigned long ro_limit,        \
                   unsigned long coh_start,        \
                   unsigned long coh_limit)        \
    {                                \
        mmap_add_region(total_base, total_base,            \
                total_size,                \
                MT_MEMORY | MT_RW | MT_SECURE);        \
        mmap_add_region(ro_start, ro_start,            \
                ro_limit - ro_start,            \
                MT_MEMORY | MT_RO | MT_SECURE);        \
        mmap_add_region(coh_start, coh_start,            \
                coh_limit - coh_start,            \
                MT_DEVICE | MT_RW | MT_SECURE);        \
        mmap_add(plat_bm_mmap);                \
        init_xlat_tables();                    \
                                    \
        enable_mmu_el##_el(0);                    \
    }

/* Define EL1 and EL3 variants of the function initialising the MMU */
DEFINE_CONFIGURE_MMU_EL(1)
DEFINE_CONFIGURE_MMU_EL(3)


#pragma weak plat_bm_ddr_init

void plat_bm_ddr_init(void)
{
    /* dummy */
}

