/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __HI3660_H__
#define __HI3660_H__

#include <hi3660_crg.h>
#include <hi3660_hkadc.h>
#include <hi3660_mem_map.h>

#define ASP_CFG_REG_BASE        0xE804E000

#define ASP_CFG_MMBUF_CTRL_REG        (ASP_CFG_REG_BASE + 0x148)

#define LP_RAM_BASE            0xFFF50000

#define SCTRL_REG_BASE            0xFFF0A000

#define SCTRL_CONTROL_REG        (SCTRL_REG_BASE + 0x000)
#define SCTRL_CONTROL_SYS_MODE(x)    (((x) & 0xf) << 3)
#define SCTRL_CONTROL_SYS_MODE_NORMAL    ((1 << 2) << 3)
#define SCTRL_CONTROL_SYS_MODE_SLOW    ((1 << 1) << 3)
#define SCTRL_CONTROL_SYS_MODE_MASK    (0xf << 3)
#define SCTRL_CONTROL_MODE_CTRL_NORMAL    (1 << 2)
#define SCTRL_CONTROL_MODE_CTRL_SLOW    (1 << 1)
#define SCTRL_CONTROL_MODE_CTRL_MASK    0x7

#define SCTRL_SCSYSSTAT_REG        (SCTRL_REG_BASE + 0x004)

#define SCTRL_DEEPSLEEPED_REG        (SCTRL_REG_BASE + 0x008)
#define SCTRL_EFUSE_USB_MASK        (1 << 30)
#define SCTRL_EFUSE_USB_PLL        (1 << 30)
#define SCTRL_EFUSE_USB_ABB        (0 << 30)
#define SCTRL_EFUSE_UFS_MASK        (3 << 6)
#define SCTRL_EFUSE_UFS_PLL        (1 << 6)
#define SCTRL_EFUSE_UFS_ABB        (0 << 6)

#define SCTRL_SCISOEN_REG        (SCTRL_REG_BASE + 0x040)
#define SCTRL_SCISODIS_REG        (SCTRL_REG_BASE + 0x044)
#define SCISO_MMBUFISO            (1 << 3)

#define SCTRL_SCPWREN_REG        (SCTRL_REG_BASE + 0x060)
#define SCPWREN_MMBUFPWREN        (1 << 3)

#define SCTRL_PLL_CTRL0_REG        (SCTRL_REG_BASE + 0x100)
#define SCTRL_PLL0_POSTDIV2(x)        (((x) & 0x7) << 23)
#define SCTRL_PLL0_POSTDIV1(x)        (((x) & 0x7) << 20)
#define SCTRL_PLL0_FBDIV(x)        (((x) & 0xfff) << 8)
#define SCTRL_PLL0_REFDIV(x)        (((x) & 0x3f) << 2)
#define SCTRL_PLL0_EN            (1 << 0)

#define SCTRL_PLL_CTRL1_REG        (SCTRL_REG_BASE + 0x104)
#define SCTRL_PLL0_CLK_NO_GATE        (1 << 26)
#define SCTRL_PLL0_CFG_VLD        (1 << 25)
#define SCTRL_PLL0_FRACDIV(x)        ((x) & 0xFFFFFF)

#define SCTRL_PLL_STAT_REG        (SCTRL_REG_BASE + 0x10C)
#define SCTRL_PLL0_STAT            (1 << 0)

#define SCTRL_SCPEREN0_REG        (SCTRL_REG_BASE + 0x160)
#define SCTRL_SCPERDIS0_REG        (SCTRL_REG_BASE + 0x164)
#define SCTRL_SCPERSTAT0_REG        (SCTRL_REG_BASE + 0x168)

#define SCTRL_SCPEREN1_REG        (SCTRL_REG_BASE + 0x170)
#define SCTRL_SCPERDIS1_REG        (SCTRL_REG_BASE + 0x174)
#define SCTRL_SCPEREN1_REG        (SCTRL_REG_BASE + 0x170)
#define SCTRL_SCPERDIS1_REG        (SCTRL_REG_BASE + 0x174)
#define SCPEREN1_WAIT_DDR_SELFREFRESH_DONE_BYPASS    (1 << 31)
#define SCPEREN_GT_PCLK_MMBUFCFG    (1 << 25)
#define SCPEREN_GT_PCLK_MMBUF        (1 << 23)
#define SCPEREN_GT_ACLK_MMBUF        (1 << 22)
#define SCPEREN_GT_CLK_NOC_AOBUS2MMBUF    (1 << 6)

#define SCTRL_SCPEREN2_REG        (SCTRL_REG_BASE + 0x190)
#define SCTRL_SCPERDIS2_REG        (SCTRL_REG_BASE + 0x194)
#define SCTRL_SCPERSTAT2_REG        (SCTRL_REG_BASE + 0x198)
#define SCTRL_SCPERRSTEN0_REG        (SCTRL_REG_BASE + 0x200)
#define SCTRL_SCPERRSTDIS0_REG        (SCTRL_REG_BASE + 0x204)
#define SCTRL_SCPERRSTSTAT0_REG        (SCTRL_REG_BASE + 0x208)
#define SCTRL_SCPERRSTEN1_REG        (SCTRL_REG_BASE + 0x20C)
#define SCTRL_SCPERRSTDIS1_REG        (SCTRL_REG_BASE + 0x210)
#define SCTRL_SCPERRSTSTAT1_REG        (SCTRL_REG_BASE + 0x214)
#define IP_RST_MMBUFCFG            (1 << 12)
#define IP_RST_MMBUF            (1 << 11)

#define SCTRL_SCPERRSTEN2_REG        (SCTRL_REG_BASE + 0x218)
#define SCTRL_SCPERRSTDIS2_REG        (SCTRL_REG_BASE + 0x21C)
#define SCTRL_SCPERRSTSTAT2_REG        (SCTRL_REG_BASE + 0x220)

#define SCTRL_SCCLKDIV2_REG        (SCTRL_REG_BASE + 0x258)
#define SEL_CLK_MMBUF_MASK        (0x3 << 8)
#define SEL_CLK_MMBUF_PLL0        (0x3 << 8)
#define SCCLKDIV2_GT_PCLK_MMBUF        (1 << 7)

#define SCTRL_SCCLKDIV4_REG        (SCTRL_REG_BASE + 0x260)
#define GT_MMBUF_SYS            (1 << 13)
#define GT_MMBUF_FLL            (1 << 12)
#define GT_PLL_CLK_MMBUF        (1 << 11)

#define SCTRL_SCCLKDIV6_REG        (SCTRL_REG_BASE + 0x268)

#define SCTRL_SCPERCTRL7_REG        (SCTRL_REG_BASE + 0x31C)
#define SCTRL_SCPERSTAT6_REG        (SCTRL_REG_BASE + 0x378)

#define SCTRL_SCINNERSTAT_REG        (SCTRL_REG_BASE + 0x3A0)
#define EMMC_UFS_SEL            (1 << 15)

#define SCTRL_BAK_DATA0_REG        (SCTRL_REG_BASE + 0x40C)
#define SCTRL_BAK_DATA4_REG        (SCTRL_REG_BASE + 0x41C)

#define SCTRL_LPMCU_CLKEN_REG        (SCTRL_REG_BASE + 0x480)
#define SCTRL_LPMCU_CLKDIS_REG        (SCTRL_REG_BASE + 0x484)
#define SCTRL_LPMCU_RSTEN_REG        (SCTRL_REG_BASE + 0x500)
#define SCTRL_LPMCU_RSTDIS_REG        (SCTRL_REG_BASE + 0x504)
#define DDRC_SOFT_BIT            (1 << 6)
#define DDRC_CLK_BIT            (1 << 5)

#define SCTRL_SCPEREN0_SEC_REG        (SCTRL_REG_BASE + 0x900)
#define SCTRL_SCPERDIS0_SEC_REG        (SCTRL_REG_BASE + 0x904)
#define MMBUF_SEC_CTRL_MASK        (0xfff << 20)
#define MMBUF_SEC_CTRL(x)        (((x) & 0xfff) << 20)

#define SCTRL_PERRSTEN1_SEC_REG        (SCTRL_REG_BASE + 0xA50)
#define SCTRL_PERRSTDIS1_SEC_REG    (SCTRL_REG_BASE + 0xA54)
#define SCTRL_PERRSTSTAT1_SEC_REG    (SCTRL_REG_BASE + 0xA58)
#define RST_ASP_SUBSYS_BIT        (1 << 0)

#define SCTRL_PERRSTEN2_SEC_REG        (SCTRL_REG_BASE + 0xB50)
#define SCTRL_PERRSTDIS2_SEC_REG    (SCTRL_REG_BASE + 0xB54)
#define SCTRL_PERRSTSTAT2_SEC_REG    (SCTRL_REG_BASE + 0xB58)

#define SCTRL_HISEECLKDIV_REG        (SCTRL_REG_BASE + 0xC28)
#define SC_SEL_HISEE_PLL_MASK        (1 << 4)
#define SC_SEL_HISEE_PLL0        (1 << 4)
#define SC_SEL_HISEE_PLL2        (0 << 4)
#define SC_DIV_HISEE_PLL_MASK        (7 << 16)
#define SC_DIV_HISEE_PLL(x)        ((x) & 0x7)

#define SCTRL_SCSOCID0_REG        (SCTRL_REG_BASE + 0xE00)

#define PMC_REG_BASE            0xFFF31000
#define PMC_PPLL1_CTRL0_REG        (PMC_REG_BASE + 0x038)
#define PMC_PPLL1_CTRL1_REG        (PMC_REG_BASE + 0x03C)
#define PMC_PPLL2_CTRL0_REG        (PMC_REG_BASE + 0x040)
#define PMC_PPLL2_CTRL1_REG        (PMC_REG_BASE + 0x044)
#define PMC_PPLL3_CTRL0_REG        (PMC_REG_BASE + 0x048)
#define PMC_PPLL3_CTRL1_REG        (PMC_REG_BASE + 0x04C)
#define PPLLx_LOCK            (1 << 26)
#define PPLLx_WITHOUT_CLK_GATE        (1 << 26)
#define PPLLx_CFG_VLD            (1 << 25)
#define PPLLx_INT_MOD            (1 << 24)
#define PPLLx_POSTDIV2_MASK        (0x7 << 23)
#define PPLLx_POSTDIV2(x)        (((x) & 0x7) << 23)
#define PPLLx_POSTDIV1_MASK        (0x7 << 20)
#define PPLLx_POSTDIV1(x)        (((x) & 0x7) << 20)
#define PPLLx_FRACDIV_MASK        (0x00FFFFFF)
#define PPLLx_FRACDIV(x)        ((x) & 0x00FFFFFF)
#define PPLLx_FBDIV_MASK        (0xfff << 8)
#define PPLLx_FBDIV(x)            (((x) & 0xfff) << 8)
#define PPLLx_REFDIV_MASK        (0x3f << 2)
#define PPLLx_REFDIV(x)            (((x) & 0x3f) << 2)
#define PPLLx_BP            (1 << 1)
#define PPLLx_EN            (1 << 0)

#define PMC_DDRLP_CTRL_REG        (PMC_REG_BASE + 0x30C)
#define DDRC_CSYSREQ_CFG(x)        ((x) & 0xF)

#define PMC_NOC_POWER_IDLEREQ_REG    (PMC_REG_BASE + 0x380)
#define PMC_NOC_POWER_IDLEREQ_IVP    (1 << 14)
#define PMC_NOC_POWER_IDLEREQ_DSS    (1 << 13)
#define PMC_NOC_POWER_IDLEREQ_VENC    (1 << 11)
#define PMC_NOC_POWER_IDLEREQ_VDEC    (1 << 10)
#define PMC_NOC_POWER_IDLEREQ_ISP    (1 << 5)
#define PMC_NOC_POWER_IDLEREQ_VCODEC    (1 << 4)
#define DDRPHY_BYPASS_MODE        (1 << 0)

#define PMC_NOC_POWER_IDLEACK_REG    (PMC_REG_BASE + 0x384)
#define PMC_NOC_POWER_IDLE_REG        (PMC_REG_BASE + 0x388)

#define PMU_SSI0_REG_BASE        0xFFF34000

#define PMU_SSI0_LDO8_CTRL0_REG        (PMU_SSI0_REG_BASE + (0x68 << 2))
#define LDO8_CTRL0_EN_1_8V        0x02

#define PMU_SSI0_CLK_TOP_CTRL7_REG    (PMU_SSI0_REG_BASE + (0x10C << 2))
#define NP_XO_ABB_DIG            (1 << 1)

#define LP_CONFIG_REG_BASE        0xFFF3F000

#define DMAC_BASE            0xFDF30000

#define CCI400_REG_BASE            0xE8100000
#define CCI400_SL_IFACE3_CLUSTER_IX    0
#define CCI400_SL_IFACE4_CLUSTER_IX    1

#define GICD_REG_BASE            0xE82B1000
#define GICC_REG_BASE            0xE82B2000
/*
 * GIC400 interrupt handling related constants
 */
#define IRQ_SEC_PHY_TIMER        29
#define IRQ_SEC_SGI_0            8
#define IRQ_SEC_SGI_1            9
#define IRQ_SEC_SGI_2            10
#define IRQ_SEC_SGI_3            11
#define IRQ_SEC_SGI_4            12
#define IRQ_SEC_SGI_5            13
#define IRQ_SEC_SGI_6            14
#define IRQ_SEC_SGI_7            15
#define IRQ_SEC_SGI_8            16

#define IPC_REG_BASE            0xE896A000
#define IPC_BASE            (IPC_REG_BASE)

#define IOMG_REG_BASE            0xE896C000

/* GPIO46: HUB 3.3V enable. active low */
#define IOMG_044_REG            (IOMG_REG_BASE + 0x0B0)
#define IOMG_UART5_RX_REG        (IOMG_REG_BASE + 0x0BC)
#define IOMG_UART5_TX_REG        (IOMG_REG_BASE + 0x0C0)

#define IOCG_REG_BASE            0xE896C800

/* GPIO005: PMIC SSI. (2 << 4) */
#define IOCG_006_REG            (IOCG_REG_BASE + 0x018)

#define TIMER9_REG_BASE            0xE8A00000

#define WDT0_REG_BASE            0xE8A06000
#define WDT1_REG_BASE            0xE8A07000
#define WDT_CONTROL_OFFSET        0x008
#define WDT_LOCK_OFFSET            0xC00

#define WDT_UNLOCK            0x1ACCE551
#define WDT_LOCKED            1

#define PCTRL_REG_BASE            0xE8A09000
#define PCTRL_PERI_CTRL3_REG        (PCTRL_REG_BASE + 0x010)
#define PCTRL_PERI_CTRL24_REG        (PCTRL_REG_BASE + 0x064)

#define TZC_REG_BASE            0xE8A21000
#define TZC_STAT0_REG            (TZC_REG_BASE + 0x800)
#define TZC_EN0_REG            (TZC_REG_BASE + 0x804)
#define TZC_DIS0_REG            (TZC_REG_BASE + 0x808)
#define TZC_STAT1_REG            (TZC_REG_BASE + 0x80C)
#define TZC_EN1_REG            (TZC_REG_BASE + 0x810)
#define TZC_DIS1_REG            (TZC_REG_BASE + 0x814)
#define TZC_STAT2_REG            (TZC_REG_BASE + 0x818)
#define TZC_EN2_REG            (TZC_REG_BASE + 0x81C)
#define TZC_DIS2_REG            (TZC_REG_BASE + 0x820)
#define TZC_STAT3_REG            (TZC_REG_BASE + 0x824)
#define TZC_EN3_REG            (TZC_REG_BASE + 0x828)
#define TZC_DIS3_REG            (TZC_REG_BASE + 0x82C)
#define TZC_STAT4_REG            (TZC_REG_BASE + 0x830)
#define TZC_EN4_REG            (TZC_REG_BASE + 0x834)
#define TZC_DIS4_REG            (TZC_REG_BASE + 0x838)
#define TZC_STAT5_REG            (TZC_REG_BASE + 0x83C)
#define TZC_EN5_REG            (TZC_REG_BASE + 0x840)
#define TZC_DIS5_REG            (TZC_REG_BASE + 0x844)
#define TZC_STAT6_REG            (TZC_REG_BASE + 0x848)
#define TZC_EN6_REG            (TZC_REG_BASE + 0x84C)
#define TZC_DIS6_REG            (TZC_REG_BASE + 0x850)
#define TZC_STAT7_REG            (TZC_REG_BASE + 0x854)
#define TZC_EN7_REG            (TZC_REG_BASE + 0x858)
#define TZC_DIS7_REG            (TZC_REG_BASE + 0x85C)
#define TZC_STAT8_REG            (TZC_REG_BASE + 0x860)
#define TZC_EN8_REG            (TZC_REG_BASE + 0x864)
#define TZC_DIS8_REG            (TZC_REG_BASE + 0x868)

#define MMBUF_BASE            0xEA800000

#define ACPU_DMCPACK0_BASE        0xEA900000

#define ACPU_DMCPACK1_BASE        0xEA920000

#define ACPU_DMCPACK2_BASE        0xEA940000

#define ACPU_DMCPACK3_BASE        0xEA960000

#define UART5_REG_BASE            0xFDF05000

#define USB3OTG_REG_BASE        0xFF100000

#define UFS_REG_BASE            0xFF3B0000

#define UFS_SYS_REG_BASE        0xFF3B1000

#define UFS_SYS_PSW_POWER_CTRL_REG    (UFS_SYS_REG_BASE + 0x004)
#define UFS_SYS_PHY_ISO_EN_REG        (UFS_SYS_REG_BASE + 0x008)
#define UFS_SYS_HC_LP_CTRL_REG        (UFS_SYS_REG_BASE + 0x00C)
#define UFS_SYS_PHY_CLK_CTRL_REG    (UFS_SYS_REG_BASE + 0x010)
#define UFS_SYS_PSW_CLK_CTRL_REG    (UFS_SYS_REG_BASE + 0x014)
#define UFS_SYS_CLOCK_GATE_BYPASS_REG    (UFS_SYS_REG_BASE + 0x018)
#define UFS_SYS_RESET_CTRL_EN_REG    (UFS_SYS_REG_BASE + 0x01C)
#define UFS_SYS_MONITOR_HH_REG        (UFS_SYS_REG_BASE + 0x03C)
#define UFS_SYS_UFS_SYSCTRL_REG        (UFS_SYS_REG_BASE + 0x05C)
#define UFS_SYS_UFS_DEVICE_RESET_CTRL_REG    (UFS_SYS_REG_BASE + 0x060)
#define UFS_SYS_UFS_APB_ADDR_MASK_REG    (UFS_SYS_REG_BASE + 0x064)

#define BIT_UFS_PSW_ISO_CTRL            (1 << 16)
#define BIT_UFS_PSW_MTCMOS_EN            (1 << 0)
#define BIT_UFS_REFCLK_ISO_EN            (1 << 16)
#define BIT_UFS_PHY_ISO_CTRL            (1 << 0)
#define BIT_SYSCTRL_LP_ISOL_EN            (1 << 16)
#define BIT_SYSCTRL_PWR_READY            (1 << 8)
#define BIT_SYSCTRL_REF_CLOCK_EN        (1 << 24)
#define MASK_SYSCTRL_REF_CLOCK_SEL        (3 << 8)
#define MASK_SYSCTRL_CFG_CLOCK_FREQ        (0xFF)
#define BIT_SYSCTRL_PSW_CLK_EN            (1 << 4)
#define MASK_UFS_CLK_GATE_BYPASS        (0x3F)
#define BIT_SYSCTRL_LP_RESET_N            (1 << 0)
#define BIT_UFS_REFCLK_SRC_SE1            (1 << 0)
#define MASK_UFS_SYSCTRL_BYPASS            (0x3F << 16)
#define MASK_UFS_DEVICE_RESET            (1 << 16)
#define BIT_UFS_DEVICE_RESET            (1 << 0)

#define IOMG_FIX_REG_BASE        0xFF3B6000

/* GPIO150: LED */
#define IOMG_FIX_006_REG        (IOMG_FIX_REG_BASE + 0x018)
/* GPIO151: LED */
#define IOMG_FIX_007_REG        (IOMG_FIX_REG_BASE + 0x01C)

#define IOMG_AO_REG_BASE        0xFFF11000

/* GPIO189: LED */
#define IOMG_AO_011_REG            (IOMG_AO_REG_BASE + 0x02C)
/* GPIO190: LED */
#define IOMG_AO_012_REG            (IOMG_AO_REG_BASE + 0x030)
/* GPIO202: type C enable. active low */
#define IOMG_AO_023_REG            (IOMG_AO_REG_BASE + 0x05C)
/* GPIO206: USB switch. active low */
#define IOMG_AO_026_REG            (IOMG_AO_REG_BASE + 0x068)
/* GPIO219: PD interrupt. pull up */
#define IOMG_AO_039_REG            (IOMG_AO_REG_BASE + 0x09C)

#define IOCG_AO_REG_BASE        0xFFF1187C
/* GPIO219: PD interrupt. pull up */
#define IOCG_AO_043_REG            (IOCG_AO_REG_BASE + 0x030)

#endif  /* __HI3660_H__ */
