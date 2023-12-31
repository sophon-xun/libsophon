/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HI6220_REGS_ACPU_H__
#define __HI6220_REGS_ACPU_H__

#define ACPU_CTRL_BASE                0xF6504000

#define ACPU_SC_CPU_CTRL            (ACPU_CTRL_BASE + 0x000)
#define ACPU_SC_CPU_STAT            (ACPU_CTRL_BASE + 0x008)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFIL2        (1 << 0)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFIL2_SHIFT        (0)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI0            (1 << 1)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI0_SHIFT        (1)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI1            (1 << 2)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI1_SHIFT        (2)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI2            (1 << 3)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI2_SHIFT        (3)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI3            (1 << 4)
#define ACPU_SC_CPU_STAT_SC_STANDBYWFI3_SHIFT        (4)
#define ACPU_SC_CPU_STAT_A53_1_STANDBYWFIL2        (1 << 8)
#define ACPU_SC_CPU_STAT_A53_1_STANDBYWFIL2_SHIFT    (8)
#define ACPU_SC_CPU_STAT_A53_1_STANDBYWFI        (1 << 9)
#define ACPU_SC_CPU_STAT_A53_1_STANDBYWFI_SHIFT        (9)
#define ACPU_SC_CPU_STAT_L2FLSHUDONE0            (1 << 16)
#define ACPU_SC_CPU_STAT_L2FLSHUDONE0_SHIFT        (16)
#define ACPU_SC_CPU_STAT_L2FLSHUDONE1            (1 << 17)
#define ACPU_SC_CPU_STAT_L2FLSHUDONE1_SHIFT        (17)
#define ACPU_SC_CPU_STAT_CCI400_ACTIVE            (1 << 18)
#define ACPU_SC_CPU_STAT_CCI400_ACTIVE_SHIFT        (18)
#define ACPU_SC_CPU_STAT_CLK_DIV_STATUS_VD        (1 << 20)
#define ACPU_SC_CPU_STAT_CLK_DIV_STATUS_VD_SHIFT    (20)

#define ACPU_SC_CLKEN                (ACPU_CTRL_BASE + 0x00c)
#define HPM_L2_1_CLKEN                (1 << 9)
#define G_CPU_1_CLKEN                (1 << 8)
#define HPM_L2_CLKEN                (1 << 1)
#define G_CPU_CLKEN                (1 << 0)

#define ACPU_SC_CLKDIS                (ACPU_CTRL_BASE + 0x010)
#define ACPU_SC_CLK_STAT            (ACPU_CTRL_BASE + 0x014)
#define ACPU_SC_RSTEN                (ACPU_CTRL_BASE + 0x018)
#define SRST_PRESET1_RSTEN            (1 << 11)
#define SRST_PRESET0_RSTEN            (1 << 10)
#define SRST_CLUSTER1_RSTEN            (1 << 9)
#define SRST_CLUSTER0_RSTEN            (1 << 8)
#define SRST_L2_HPM_1_RSTEN            (1 << 5)
#define SRST_AARM_L2_1_RSTEN            (1 << 4)
#define SRST_L2_HPM_0_RSTEN            (1 << 3)
#define SRST_AARM_L2_0_RSTEN            (1 << 1)
#define SRST_CLUSTER1                (SRST_PRESET1_RSTEN | \
                         SRST_CLUSTER1_RSTEN | \
                         SRST_L2_HPM_1_RSTEN | \
                         SRST_AARM_L2_1_RSTEN)
#define SRST_CLUSTER0                (SRST_PRESET0_RSTEN | \
                         SRST_CLUSTER0_RSTEN | \
                         SRST_L2_HPM_0_RSTEN | \
                         SRST_AARM_L2_0_RSTEN)

#define ACPU_SC_RSTDIS                (ACPU_CTRL_BASE + 0x01c)
#define ACPU_SC_RST_STAT            (ACPU_CTRL_BASE + 0x020)
#define ACPU_SC_PDBGUP_MBIST            (ACPU_CTRL_BASE + 0x02c)
#define PDBGUP_CLUSTER1_SHIFT            8

#define ACPU_SC_VD_CTRL                (ACPU_CTRL_BASE + 0x054)
#define ACPU_SC_VD_MASK_PATTERN_CTRL        (ACPU_CTRL_BASE + 0x058)
#define ACPU_SC_VD_MASK_PATTERN_VAL        (0xCCB << 12)
#define ACPU_SC_VD_MASK_PATTERN_MASK        ((0x1 << 13) - 1)

#define ACPU_SC_VD_DLY_FIXED_CTRL        (ACPU_CTRL_BASE + 0x05c)
#define ACPU_SC_VD_DLY_TABLE0_CTRL        (ACPU_CTRL_BASE + 0x060)
#define ACPU_SC_VD_DLY_TABLE1_CTRL        (ACPU_CTRL_BASE + 0x064)
#define ACPU_SC_VD_DLY_TABLE2_CTRL        (ACPU_CTRL_BASE + 0x068)
#define ACPU_SC_VD_HPM_CTRL            (ACPU_CTRL_BASE + 0x06c)
#define ACPU_SC_A53_CLUSTER_MTCMOS_EN        (ACPU_CTRL_BASE + 0x088)
#define PW_MTCMOS_EN_A53_1_EN            (1 << 1)
#define PW_MTCMOS_EN_A53_0_EN            (1 << 0)

#define ACPU_SC_A53_CLUSTER_MTCMOS_STA        (ACPU_CTRL_BASE + 0x090)
#define ACPU_SC_A53_CLUSTER_ISO_EN        (ACPU_CTRL_BASE + 0x098)
#define PW_ISO_A53_1_EN                (1 << 1)
#define PW_ISO_A53_0_EN                (1 << 0)

#define ACPU_SC_A53_CLUSTER_ISO_DIS        (ACPU_CTRL_BASE + 0x09c)
#define ACPU_SC_A53_CLUSTER_ISO_STA        (ACPU_CTRL_BASE + 0x0a0)
#define ACPU_SC_A53_1_MTCMOS_TIMER        (ACPU_CTRL_BASE + 0x0b4)
#define ACPU_SC_A53_0_MTCMOS_TIMER        (ACPU_CTRL_BASE + 0x0bc)
#define ACPU_SC_A53_x_MTCMOS_TIMER(x)        ((x) ? ACPU_SC_A53_1_MTCMOS_TIMER : ACPU_SC_A53_0_MTCMOS_TIMER)

#define ACPU_SC_SNOOP_PWD            (ACPU_CTRL_BASE + 0xe4)
#define PD_DETECT_START1            (1 << 16)
#define PD_DETECT_START0            (1 << 0)

#define ACPU_SC_CPU0_CTRL            (ACPU_CTRL_BASE + 0x100)
#define CPU_CTRL_AARCH64_MODE            (1 << 7)

#define ACPU_SC_CPU0_STAT            (ACPU_CTRL_BASE + 0x104)
#define ACPU_SC_CPU0_CLKEN            (ACPU_CTRL_BASE + 0x108)
#define CPU_CLKEN_HPM                (1 << 1)

#define ACPU_SC_CPU0_CLK_STAT            (ACPU_CTRL_BASE + 0x110)

#define ACPU_SC_CPU0_RSTEN            (ACPU_CTRL_BASE + 0x114)
#define ACPU_SC_CPU0_RSTDIS            (ACPU_CTRL_BASE + 0x118)
#define ACPU_SC_CPU0_MTCMOS_EN            (ACPU_CTRL_BASE + 0x120)
#define CPU_MTCMOS_PW                (1 << 0)

#define ACPU_SC_CPU0_PW_ISOEN            (ACPU_CTRL_BASE + 0x130)
#define CPU_PW_ISO                (1 << 0)

#define ACPU_SC_CPU0_PW_ISODIS            (ACPU_CTRL_BASE + 0x134)
#define ACPU_SC_CPU0_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x138)
#define ACPU_SC_CPU0_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x154)
#define CPU_MTCMOS_TIMER_STA            (1 << 0)

#define ACPU_SC_CPU0_RVBARADDR            (ACPU_CTRL_BASE + 0x158)
#define ACPU_SC_CPU1_CTRL            (ACPU_CTRL_BASE + 0x200)
#define ACPU_SC_CPU1_STAT            (ACPU_CTRL_BASE + 0x204)
#define ACPU_SC_CPU1_CLKEN            (ACPU_CTRL_BASE + 0x208)
#define ACPU_SC_CPU1_CLK_STAT            (ACPU_CTRL_BASE + 0x210)
#define ACPU_SC_CPU1_RSTEN            (ACPU_CTRL_BASE + 0x214)
#define ACPU_SC_CPU1_RSTDIS            (ACPU_CTRL_BASE + 0x218)
#define ACPU_SC_CPU1_MTCMOS_EN            (ACPU_CTRL_BASE + 0x220)
#define ACPU_SC_CPU1_PW_ISODIS            (ACPU_CTRL_BASE + 0x234)
#define ACPU_SC_CPU1_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x238)
#define ACPU_SC_CPU1_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x254)
#define ACPU_SC_CPU1_RVBARADDR            (ACPU_CTRL_BASE + 0x258)
#define ACPU_SC_CPU2_CTRL            (ACPU_CTRL_BASE + 0x300)
#define ACPU_SC_CPU2_STAT            (ACPU_CTRL_BASE + 0x304)
#define ACPU_SC_CPU2_CLKEN            (ACPU_CTRL_BASE + 0x308)
#define ACPU_SC_CPU2_CLK_STAT            (ACPU_CTRL_BASE + 0x310)
#define ACPU_SC_CPU2_RSTEN            (ACPU_CTRL_BASE + 0x314)
#define ACPU_SC_CPU2_RSTDIS            (ACPU_CTRL_BASE + 0x318)
#define ACPU_SC_CPU2_MTCMOS_EN            (ACPU_CTRL_BASE + 0x320)
#define ACPU_SC_CPU2_PW_ISODIS            (ACPU_CTRL_BASE + 0x334)
#define ACPU_SC_CPU2_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x338)
#define ACPU_SC_CPU2_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x354)
#define ACPU_SC_CPU2_RVBARADDR            (ACPU_CTRL_BASE + 0x358)
#define ACPU_SC_CPU3_CTRL            (ACPU_CTRL_BASE + 0x400)
#define ACPU_SC_CPU3_STAT            (ACPU_CTRL_BASE + 0x404)
#define ACPU_SC_CPU3_CLKEN            (ACPU_CTRL_BASE + 0x408)
#define ACPU_SC_CPU3_CLK_STAT            (ACPU_CTRL_BASE + 0x410)
#define ACPU_SC_CPU3_RSTEN            (ACPU_CTRL_BASE + 0x414)
#define ACPU_SC_CPU3_RSTDIS            (ACPU_CTRL_BASE + 0x418)
#define ACPU_SC_CPU3_MTCMOS_EN            (ACPU_CTRL_BASE + 0x420)
#define ACPU_SC_CPU3_PW_ISODIS            (ACPU_CTRL_BASE + 0x434)
#define ACPU_SC_CPU3_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x438)
#define ACPU_SC_CPU3_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x454)
#define ACPU_SC_CPU3_RVBARADDR            (ACPU_CTRL_BASE + 0x458)
#define ACPU_SC_CPU4_CTRL            (ACPU_CTRL_BASE + 0x500)
#define ACPU_SC_CPU4_STAT            (ACPU_CTRL_BASE + 0x504)
#define ACPU_SC_CPU4_CLKEN            (ACPU_CTRL_BASE + 0x508)
#define ACPU_SC_CPU4_CLK_STAT            (ACPU_CTRL_BASE + 0x510)
#define ACPU_SC_CPU4_RSTEN            (ACPU_CTRL_BASE + 0x514)
#define ACPU_SC_CPU4_RSTDIS            (ACPU_CTRL_BASE + 0x518)
#define ACPU_SC_CPU4_MTCMOS_EN            (ACPU_CTRL_BASE + 0x520)
#define ACPU_SC_CPU4_PW_ISODIS            (ACPU_CTRL_BASE + 0x534)
#define ACPU_SC_CPU4_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x538)
#define ACPU_SC_CPU4_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x554)
#define ACPU_SC_CPU4_RVBARADDR            (ACPU_CTRL_BASE + 0x558)
#define ACPU_SC_CPU5_CTRL            (ACPU_CTRL_BASE + 0x600)
#define ACPU_SC_CPU5_STAT            (ACPU_CTRL_BASE + 0x604)
#define ACPU_SC_CPU5_CLKEN            (ACPU_CTRL_BASE + 0x608)
#define ACPU_SC_CPU5_CLK_STAT            (ACPU_CTRL_BASE + 0x610)
#define ACPU_SC_CPU5_RSTEN            (ACPU_CTRL_BASE + 0x614)
#define ACPU_SC_CPU5_RSTDIS            (ACPU_CTRL_BASE + 0x618)
#define ACPU_SC_CPU5_MTCMOS_EN            (ACPU_CTRL_BASE + 0x620)
#define ACPU_SC_CPU5_PW_ISODIS            (ACPU_CTRL_BASE + 0x634)
#define ACPU_SC_CPU5_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x638)
#define ACPU_SC_CPU5_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x654)
#define ACPU_SC_CPU5_RVBARADDR            (ACPU_CTRL_BASE + 0x658)
#define ACPU_SC_CPU6_CTRL            (ACPU_CTRL_BASE + 0x700)
#define ACPU_SC_CPU6_STAT            (ACPU_CTRL_BASE + 0x704)
#define ACPU_SC_CPU6_CLKEN            (ACPU_CTRL_BASE + 0x708)
#define ACPU_SC_CPU6_CLK_STAT            (ACPU_CTRL_BASE + 0x710)
#define ACPU_SC_CPU6_RSTEN            (ACPU_CTRL_BASE + 0x714)
#define ACPU_SC_CPU6_RSTDIS            (ACPU_CTRL_BASE + 0x718)
#define ACPU_SC_CPU6_MTCMOS_EN            (ACPU_CTRL_BASE + 0x720)
#define ACPU_SC_CPU6_PW_ISODIS            (ACPU_CTRL_BASE + 0x734)
#define ACPU_SC_CPU6_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x738)
#define ACPU_SC_CPU6_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x754)
#define ACPU_SC_CPU6_RVBARADDR            (ACPU_CTRL_BASE + 0x758)
#define ACPU_SC_CPU7_CTRL            (ACPU_CTRL_BASE + 0x800)
#define ACPU_SC_CPU7_STAT            (ACPU_CTRL_BASE + 0x804)
#define ACPU_SC_CPU7_CLKEN            (ACPU_CTRL_BASE + 0x808)
#define ACPU_SC_CPU7_CLK_STAT            (ACPU_CTRL_BASE + 0x810)
#define ACPU_SC_CPU7_RSTEN            (ACPU_CTRL_BASE + 0x814)
#define ACPU_SC_CPU7_RSTDIS            (ACPU_CTRL_BASE + 0x818)
#define ACPU_SC_CPU7_MTCMOS_EN            (ACPU_CTRL_BASE + 0x820)
#define ACPU_SC_CPU7_PW_ISODIS            (ACPU_CTRL_BASE + 0x834)
#define ACPU_SC_CPU7_PW_ISO_STAT        (ACPU_CTRL_BASE + 0x838)
#define ACPU_SC_CPU7_MTCMOS_TIMER_STAT        (ACPU_CTRL_BASE + 0x854)
#define ACPU_SC_CPU7_RVBARADDR            (ACPU_CTRL_BASE + 0x858)
#define ACPU_SC_CPUx_CTRL(x)            ((x < 8) ? (ACPU_SC_CPU0_CTRL + 0x100 * x) : ACPU_SC_CPU0_CTRL)
#define ACPU_SC_CPUx_STAT(x)            ((x < 8) ? (ACPU_SC_CPU0_STAT + 0x100 * x) : ACPU_SC_CPU0_STAT)
#define ACPU_SC_CPUx_CLKEN(x)            ((x < 8) ? (ACPU_SC_CPU0_CLKEN + 0x100 * x) : ACPU_SC_CPU0_CLKEN)
#define ACPU_SC_CPUx_CLK_STAT(x)        ((x < 8) ? (ACPU_SC_CPU0_CLK_STAT + 0x100 * x) : ACPU_SC_CPU0_CLK_STAT)
#define ACPU_SC_CPUx_RSTEN(x)            ((x < 8) ? (ACPU_SC_CPU0_RSTEN + 0x100 * x) : ACPU_SC_CPU0_RSTEN)
#define ACPU_SC_CPUx_RSTDIS(x)            ((x < 8) ? (ACPU_SC_CPU0_RSTDIS + 0x100 * x) : ACPU_SC_CPU0_RSTDIS)
#define ACPU_SC_CPUx_MTCMOS_EN(x)        ((x < 8) ? (ACPU_SC_CPU0_MTCMOS_EN + 0x100 * x) : ACPU_SC_CPU0_MTCMOS_EN)
#define ACPU_SC_CPUx_PW_ISODIS(x)        ((x < 8) ? (ACPU_SC_CPU0_PW_ISODIS + 0x100 * x) : ACPU_SC_CPU0_PW_ISODIS)
#define ACPU_SC_CPUx_PW_ISO_STAT(x)        ((x < 8) ? (ACPU_SC_CPU0_PW_ISO_STAT + 0x100 * x) : ACPU_SC_CPU0_PW_ISO_STAT)
#define ACPU_SC_CPUx_MTCMOS_TIMER_STAT(x)    ((x < 8) ? (ACPU_SC_CPU0_MTCMOS_TIMER_STAT + 0x100 * x) : ACPU_SC_CPU0_MTCMOS_TIMER_STAT)
#define ACPU_SC_CPUx_RVBARADDR(x)        ((x < 8) ? (ACPU_SC_CPU0_RVBARADDR + 0x100 * x) : ACPU_SC_CPU0_RVBARADDR)

#define ACPU_SC_CPU_STAT_CLKDIV_VD_MASK        (3 << 20)

#define ACPU_SC_VD_CTRL_TUNE_EN_DIF        (1 << 0)
#define ACPU_SC_VD_CTRL_TUNE_EN_DIF_SHIFT    (0)
#define ACPU_SC_VD_CTRL_TUNE            (1 << 1)
#define ACPU_SC_VD_CTRL_TUNE_SHIFT        (1)
#define ACPU_SC_VD_CTRL_CALIBRATE_EN_DIF    (1 << 7)
#define ACPU_SC_VD_CTRL_CALIBRATE_EN_DIF_SHIFT    (7)
#define ACPU_SC_VD_CTRL_CALIBRATE_EN_INI    (1 << 8)
#define ACPU_SC_VD_CTRL_CALIBRATE_EN_INI_SHIFT    (8)
#define ACPU_SC_VD_CTRL_CLK_DIS_CNT_CLR        (1 << 9)
#define ACPU_SC_VD_CTRL_CLK_DIS_CNT_CLR_SHIFT    (9)
#define ACPU_SC_VD_CTRL_CLK_DIS_CNT_EN        (1 << 10)
#define ACPU_SC_VD_CTRL_CLK_DIS_CNT_EN_SHIFT    (10)
#define ACPU_SC_VD_CTRL_TUNE_EN_INT        (1 << 11)
#define ACPU_SC_VD_CTRL_TUNE_EN_INT_SHIFT    (11)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE0        (1 << 12)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE0_MASK    (0xf << 12)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE0_SHIFT    (12)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE1        (1 << 16)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE1_MASK    (0xf << 16)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE1_SHIFT    (16)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE2        (1 << 20)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE2_MASK    (0xf << 20)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE2_SHIFT    (20)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE3        (1 << 24)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE3_MASK    (0xf << 24)
#define ACPU_SC_VD_CTRL_SHIFT_TABLE3_SHIFT    (24)
#define ACPU_SC_VD_CTRL_FORCE_CLK_EN        (1 << 28)
#define ACPU_SC_VD_CTRL_FORCE_CLK_EN_SHIFT    (28)
#define ACPU_SC_VD_CTRL_DIV_EN_DIF        (1 << 29)
#define ACPU_SC_VD_CTRL_DIV_EN_DIF_SHIFT    (29)

#define ACPU_SC_VD_SHIFT_TABLE_TUNE_VAL            \
    ((0x1 << ACPU_SC_VD_CTRL_SHIFT_TABLE0_SHIFT) |    \
     (0x3 << ACPU_SC_VD_CTRL_SHIFT_TABLE1_SHIFT) |    \
     (0x5 << ACPU_SC_VD_CTRL_SHIFT_TABLE2_SHIFT) |    \
     (0x6 << ACPU_SC_VD_CTRL_SHIFT_TABLE3_SHIFT) |    \
     (0x7 << ACPU_SC_VD_CTRL_TUNE_SHIFT))

#define ACPU_SC_VD_SHIFT_TABLE_TUNE_MASK        \
    ((0xF << ACPU_SC_VD_CTRL_SHIFT_TABLE0_SHIFT) |    \
     (0xF << ACPU_SC_VD_CTRL_SHIFT_TABLE1_SHIFT) |    \
     (0xF << ACPU_SC_VD_CTRL_SHIFT_TABLE2_SHIFT) |    \
     (0xF << ACPU_SC_VD_CTRL_SHIFT_TABLE3_SHIFT) |    \
     (0x3F << ACPU_SC_VD_CTRL_TUNE_SHIFT))

#define ACPU_SC_VD_HPM_CTRL_OSC_DIV        (1 << 0)
#define ACPU_SC_VD_HPM_CTRL_OSC_DIV_SHIFT    (0)
#define ACPU_SC_VD_HPM_CTRL_OSC_DIV_MASK    (0x000000FF)
#define ACPU_SC_VD_HPM_CTRL_DLY_EXP        (1 << 8)
#define ACPU_SC_VD_HPM_CTRL_DLY_EXP_SHIFT    (8)
#define ACPU_SC_VD_HPM_CTRL_DLY_EXP_MASK    (0x001FFF00)

#define HPM_OSC_DIV_VAL \
    (0x56 << ACPU_SC_VD_HPM_CTRL_OSC_DIV_SHIFT)
#define HPM_OSC_DIV_MASK \
    (ACPU_SC_VD_HPM_CTRL_OSC_DIV_MASK)

#define HPM_DLY_EXP_VAL \
    (0xC7A << ACPU_SC_VD_HPM_CTRL_DLY_EXP_SHIFT)
#define HPM_DLY_EXP_MASK \
    (ACPU_SC_VD_HPM_CTRL_DLY_EXP_MASK)

#define ACPU_SC_VD_EN_ASIC_VAL                    \
    ((0x0 << ACPU_SC_VD_CTRL_FORCE_CLK_EN_SHIFT) |        \
     (0x0 << ACPU_SC_VD_CTRL_CLK_DIS_CNT_EN_SHIFT) |    \
     (0x0 << ACPU_SC_VD_CTRL_CALIBRATE_EN_INI_SHIFT) |    \
     (0x0 << ACPU_SC_VD_CTRL_CALIBRATE_EN_DIF_SHIFT) |    \
     (0X0 << ACPU_SC_VD_CTRL_DIV_EN_DIF_SHIFT) |        \
     (0X0 << ACPU_SC_VD_CTRL_TUNE_EN_INT_SHIFT) |        \
     (0x0 << ACPU_SC_VD_CTRL_TUNE_EN_DIF_SHIFT))

#define ACPU_SC_VD_EN_SFT_VAL                    \
    ((0x0 << ACPU_SC_VD_CTRL_FORCE_CLK_EN_SHIFT) |        \
     (0x0 << ACPU_SC_VD_CTRL_CLK_DIS_CNT_EN_SHIFT) |    \
     (0x0 << ACPU_SC_VD_CTRL_CALIBRATE_EN_INI_SHIFT) |    \
     (0x0 << ACPU_SC_VD_CTRL_CALIBRATE_EN_DIF_SHIFT) |    \
     (0x0 << ACPU_SC_VD_CTRL_DIV_EN_DIF_SHIFT) |        \
     (0x0 << ACPU_SC_VD_CTRL_TUNE_EN_INT_SHIFT) |        \
     (0x0 << ACPU_SC_VD_CTRL_TUNE_EN_DIF_SHIFT))

#define ACPU_SC_VD_EN_MASK                    \
    ((0x1 << ACPU_SC_VD_CTRL_FORCE_CLK_EN_SHIFT) |        \
     (0x1 << ACPU_SC_VD_CTRL_CLK_DIS_CNT_EN_SHIFT) |    \
     (0x1 << ACPU_SC_VD_CTRL_CALIBRATE_EN_INI_SHIFT) |    \
     (0x1 << ACPU_SC_VD_CTRL_CALIBRATE_EN_DIF_SHIFT) |    \
     (0x1 << ACPU_SC_VD_CTRL_DIV_EN_DIF_SHIFT) |        \
     (0x1 << ACPU_SC_VD_CTRL_TUNE_EN_INT_SHIFT) |        \
     (0x1 << ACPU_SC_VD_CTRL_TUNE_EN_DIF_SHIFT))

#endif /* __HI6220_REGS_ACPU_H__ */
