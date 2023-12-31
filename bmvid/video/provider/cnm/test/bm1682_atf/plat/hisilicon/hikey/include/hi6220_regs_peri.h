/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef __HI6220_PERI_H__
#define __HI6220_PERI_H__

#define PERI_BASE                0xF7030000

#define PERI_SC_PERIPH_CTRL1            (PERI_BASE + 0x000)
#define PERI_SC_PERIPH_CTRL2            (PERI_BASE + 0x004)
#define PERI_SC_PERIPH_CTRL3            (PERI_BASE + 0x008)
#define PERI_SC_PERIPH_CTRL4            (PERI_BASE + 0x00c)
#define PERI_SC_PERIPH_CTRL5            (PERI_BASE + 0x010)
#define PERI_SC_PERIPH_CTRL6            (PERI_BASE + 0x014)
#define PERI_SC_PERIPH_CTRL8            (PERI_BASE + 0x018)
#define PERI_SC_PERIPH_CTRL9            (PERI_BASE + 0x01c)
#define PERI_SC_PERIPH_CTRL10            (PERI_BASE + 0x020)
#define PERI_SC_PERIPH_CTRL12            (PERI_BASE + 0x024)
#define PERI_SC_PERIPH_CTRL13            (PERI_BASE + 0x028)
#define PERI_SC_PERIPH_CTRL14            (PERI_BASE + 0x02c)

#define PERI_SC_DDR_CTRL0            (PERI_BASE + 0x050)
#define PERI_SC_PERIPH_STAT1            (PERI_BASE + 0x094)

#define PERI_SC_PERIPH_CLKEN0            (PERI_BASE + 0x200)
#define PERI_SC_PERIPH_CLKDIS0            (PERI_BASE + 0x204)
#define PERI_SC_PERIPH_CLKSTAT0            (PERI_BASE + 0x208)
#define PERI_SC_PERIPH_CLKEN1            (PERI_BASE + 0x210)
#define PERI_SC_PERIPH_CLKDIS1            (PERI_BASE + 0x214)
#define PERI_SC_PERIPH_CLKSTAT1            (PERI_BASE + 0x218)
#define PERI_SC_PERIPH_CLKEN2            (PERI_BASE + 0x220)
#define PERI_SC_PERIPH_CLKDIS2            (PERI_BASE + 0x224)
#define PERI_SC_PERIPH_CLKSTAT2            (PERI_BASE + 0x228)
#define PERI_SC_PERIPH_CLKEN3            (PERI_BASE + 0x230)
#define PERI_SC_PERIPH_CLKDIS3            (PERI_BASE + 0x234)
#define PERI_SC_PERIPH_CLKSTAT3            (PERI_BASE + 0x238)
#define PERI_SC_PERIPH_CLKEN8            (PERI_BASE + 0x240)
#define PERI_SC_PERIPH_CLKDIS8            (PERI_BASE + 0x244)
#define PERI_SC_PERIPH_CLKSTAT8            (PERI_BASE + 0x248)
#define PERI_SC_PERIPH_CLKEN9            (PERI_BASE + 0x250)
#define PERI_SC_PERIPH_CLKDIS9            (PERI_BASE + 0x254)
#define PERI_SC_PERIPH_CLKSTAT9            (PERI_BASE + 0x258)
#define PERI_SC_PERIPH_CLKEN10            (PERI_BASE + 0x260)
#define PERI_SC_PERIPH_CLKDIS10            (PERI_BASE + 0x264)
#define PERI_SC_PERIPH_CLKSTAT10        (PERI_BASE + 0x268)
#define PERI_SC_PERIPH_CLKEN12            (PERI_BASE + 0x270)
#define PERI_SC_PERIPH_CLKDIS12            (PERI_BASE + 0x274)
#define PERI_SC_PERIPH_CLKSTAT12        (PERI_BASE + 0x278)

#define PERI_SC_PERIPH_RSTEN0            (PERI_BASE + 0x300)
#define PERI_SC_PERIPH_RSTDIS0            (PERI_BASE + 0x304)
#define PERI_SC_PERIPH_RSTSTAT0            (PERI_BASE + 0x308)
#define PERI_SC_PERIPH_RSTEN1            (PERI_BASE + 0x310)
#define PERI_SC_PERIPH_RSTDIS1            (PERI_BASE + 0x314)
#define PERI_SC_PERIPH_RSTSTAT1            (PERI_BASE + 0x318)
#define PERI_SC_PERIPH_RSTEN2            (PERI_BASE + 0x320)
#define PERI_SC_PERIPH_RSTDIS2            (PERI_BASE + 0x324)
#define PERI_SC_PERIPH_RSTSTAT2            (PERI_BASE + 0x328)
#define PERI_SC_PERIPH_RSTEN3            (PERI_BASE + 0x330)
#define PERI_SC_PERIPH_RSTDIS3            (PERI_BASE + 0x334)
#define PERI_SC_PERIPH_RSTSTAT3            (PERI_BASE + 0x338)
#define PERI_SC_PERIPH_RSTEN8            (PERI_BASE + 0x340)
#define PERI_SC_PERIPH_RSTDIS8            (PERI_BASE + 0x344)
#define PERI_SC_PERIPH_RSTSTAT8            (PERI_BASE + 0x338)

#define PERI_SC_CLK_SEL0            (PERI_BASE + 0x400)
#define PERI_SC_CLKCFG8BIT1            (PERI_BASE + 0x494)
#define PERI_SC_CLKCFG8BIT2            (PERI_BASE + 0x498)
#define PERI_SC_RESERVED8_ADDR            (PERI_BASE + 0xd04)

/* PERI_SC_PERIPH_CTRL1 */
#define PERI_CTRL1_ETR_AXI_CSYSREQ_N        (1 << 0)
#define PERI_CTRL1_ETR_AXI_CSYSREQ_N        (1 << 0)
#define PERI_CTRL1_HIFI_INT_MASK        (1 << 1)
#define PERI_CTRL1_HIFI_ALL_INT_MASK        (1 << 2)
#define PERI_CTRL1_ETR_AXI_CSYSREQ_N_MSK    (1 << 16)
#define PERI_CTRL1_HIFI_INT_MASK_MSK        (1 << 17)
#define PERI_CTRL1_HIFI_ALL_INT_MASK_MSK    (1 << 18)

/* PERI_SC_PERIPH_CTRL2    */
#define PERI_CTRL2_MMC_CLK_PHASE_BYPASS_EN_MMC0    (1 << 0)
#define PERI_CTRL2_MMC_CLK_PHASE_BYPASS_EN_MMC1    (1 << 2)
#define PERI_CTRL2_NAND_SYS_MEM_SEL        (1 << 6)
#define PERI_CTRL2_G3D_DDRT_AXI_SEL        (1 << 7)
#define PERI_CTRL2_GU_MDM_BBP_TESTPIN_SEL    (1 << 8)
#define PERI_CTRL2_CODEC_SSI_MASTER_CHECK    (1 << 9)
#define PERI_CTRL2_FUNC_TEST_SOFT        (1 << 12)
#define PERI_CTRL2_CSSYS_TS_ENABLE        (1 << 15)
#define PERI_CTRL2_HIFI_RAMCTRL_S_EMA        (1 << 16)
#define PERI_CTRL2_HIFI_RAMCTRL_S_EMAW        (1 << 20)
#define PERI_CTRL2_HIFI_RAMCTRL_S_EMAS        (1 << 22)
#define PERI_CTRL2_HIFI_RAMCTRL_S_RET1N        (1 << 26)
#define PERI_CTRL2_HIFI_RAMCTRL_S_RET2N        (1 << 27)
#define PERI_CTRL2_HIFI_RAMCTRL_S_PGEN        (1 << 28)

/* PERI_SC_PERIPH_CTRL3 */
#define PERI_CTRL3_HIFI_DDR_HARQMEM_ADDR    (1 << 0)
#define PERI_CTRL3_HIFI_HARQMEMRMP_EN        (1 << 12)
#define PERI_CTRL3_HARQMEM_SYS_MED_SEL        (1 << 13)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP1        (1 << 14)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP2        (1 << 16)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP3        (1 << 18)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP4        (1 << 20)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP5        (1 << 22)
#define PERI_CTRL3_SOC_AP_OCCUPY_GRP6        (1 << 24)

/* PERI_SC_PERIPH_CTRL4 */
#define PERI_CTRL4_PICO_FSELV            (1 << 0)
#define PERI_CTRL4_FPGA_EXT_PHY_SEL        (1 << 3)
#define PERI_CTRL4_PICO_REFCLKSEL        (1 << 4)
#define PERI_CTRL4_PICO_SIDDQ            (1 << 6)
#define PERI_CTRL4_PICO_SUSPENDM_SLEEPM        (1 << 7)
#define PERI_CTRL4_PICO_OGDISABLE        (1 << 8)
#define PERI_CTRL4_PICO_COMMONONN        (1 << 9)
#define PERI_CTRL4_PICO_VBUSVLDEXT        (1 << 10)
#define PERI_CTRL4_PICO_VBUSVLDEXTSEL        (1 << 11)
#define PERI_CTRL4_PICO_VATESTENB        (1 << 12)
#define PERI_CTRL4_PICO_SUSPENDM        (1 << 14)
#define PERI_CTRL4_PICO_SLEEPM            (1 << 15)
#define PERI_CTRL4_BC11_C            (1 << 16)
#define PERI_CTRL4_BC11_B            (1 << 17)
#define PERI_CTRL4_BC11_A            (1 << 18)
#define PERI_CTRL4_BC11_GND            (1 << 19)
#define PERI_CTRL4_BC11_FLOAT            (1 << 20)
#define PERI_CTRL4_OTG_PHY_SEL            (1 << 21)
#define PERI_CTRL4_USB_OTG_SS_SCALEDOWN_MODE    (1 << 22)
#define PERI_CTRL4_OTG_DM_PULLDOWN        (1 << 24)
#define PERI_CTRL4_OTG_DP_PULLDOWN        (1 << 25)
#define PERI_CTRL4_OTG_IDPULLUP            (1 << 26)
#define PERI_CTRL4_OTG_DRVBUS            (1 << 27)
#define PERI_CTRL4_OTG_SESSEND            (1 << 28)
#define PERI_CTRL4_OTG_BVALID            (1 << 29)
#define PERI_CTRL4_OTG_AVALID            (1 << 30)
#define PERI_CTRL4_OTG_VBUSVALID        (1 << 31)

/* PERI_SC_PERIPH_CTRL5 */
#define PERI_CTRL5_USBOTG_RES_SEL        (1 << 3)
#define PERI_CTRL5_PICOPHY_ACAENB        (1 << 4)
#define PERI_CTRL5_PICOPHY_BC_MODE        (1 << 5)
#define PERI_CTRL5_PICOPHY_CHRGSEL        (1 << 6)
#define PERI_CTRL5_PICOPHY_VDATSRCEND        (1 << 7)
#define PERI_CTRL5_PICOPHY_VDATDETENB        (1 << 8)
#define PERI_CTRL5_PICOPHY_DCDENB        (1 << 9)
#define PERI_CTRL5_PICOPHY_IDDIG        (1 << 10)
#define PERI_CTRL5_DBG_MUX            (1 << 11)

/* PERI_SC_PERIPH_CTRL6 */
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_EMA    (1 << 0)
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_EMAW    (1 << 4)
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_EMAS    (1 << 6)
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_RET1N    (1 << 10)
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_RET2N    (1 << 11)
#define PERI_CTRL6_CSSYSOFF_RAMCTRL_S_PGEN    (1 << 12)

/* PERI_SC_PERIPH_CTRL8 */
#define PERI_CTRL8_PICOPHY_TXRISETUNE0        (1 << 0)
#define PERI_CTRL8_PICOPHY_TXPREEMPAMPTUNE0    (1 << 2)
#define PERI_CTRL8_PICOPHY_TXRESTUNE0        (1 << 4)
#define PERI_CTRL8_PICOPHY_TXHSSVTUNE0        (1 << 6)
#define PERI_CTRL8_PICOPHY_COMPDISTUNE0        (1 << 8)
#define PERI_CTRL8_PICOPHY_TXPREEMPPULSETUNE0    (1 << 11)
#define PERI_CTRL8_PICOPHY_OTGTUNE0        (1 << 12)
#define PERI_CTRL8_PICOPHY_SQRXTUNE0        (1 << 16)
#define PERI_CTRL8_PICOPHY_TXVREFTUNE0        (1 << 20)
#define PERI_CTRL8_PICOPHY_TXFSLSTUNE0        (1 << 28)

/* PERI_SC_PERIPH_CTRL9    */
#define PERI_CTRL9_PICOPLY_TESTCLKEN        (1 << 0)
#define PERI_CTRL9_PICOPLY_TESTDATAOUTSEL    (1 << 1)
#define PERI_CTRL9_PICOPLY_TESTADDR        (1 << 4)
#define PERI_CTRL9_PICOPLY_TESTDATAIN        (1 << 8)

/*
 * PERI_SC_PERIPH_CLKEN0
 * PERI_SC_PERIPH_CLKDIS0
 * PERI_SC_PERIPH_CLKSTAT0
 */
#define PERI_CLK0_MMC0                (1 << 0)
#define PERI_CLK0_MMC1                (1 << 1)
#define PERI_CLK0_MMC2                (1 << 2)
#define PERI_CLK0_NANDC                (1 << 3)
#define PERI_CLK0_USBOTG            (1 << 4)
#define PERI_CLK0_PICOPHY            (1 << 5)
#define PERI_CLK0_PLL                (1 << 6)

/*
 * PERI_SC_PERIPH_CLKEN1
 * PERI_SC_PERIPH_CLKDIS1
 * PERI_SC_PERIPH_CLKSTAT1
 */
#define PERI_CLK1_HIFI                (1 << 0)
#define PERI_CLK1_DIGACODEC            (1 << 5)

/*
 * PERI_SC_PERIPH_CLKEN2
 * PERI_SC_PERIPH_CLKDIS2
 * PERI_SC_PERIPH_CLKSTAT2
 */
#define PERI_CLK2_IPF                (1 << 0)
#define PERI_CLK2_SOCP                (1 << 1)
#define PERI_CLK2_DMAC                (1 << 2)
#define PERI_CLK2_SECENG            (1 << 3)
#define PERI_CLK2_HPM0                (1 << 5)
#define PERI_CLK2_HPM1                (1 << 6)
#define PERI_CLK2_HPM2                (1 << 7)
#define PERI_CLK2_HPM3                (1 << 8)

/*
 * PERI_SC_PERIPH_CLKEN3
 * PERI_SC_PERIPH_CLKDIS3
 * PERI_SC_PERIPH_CLKSTAT3
 */
#define PERI_CLK3_CSSYS                (1 << 0)
#define PERI_CLK3_I2C0                (1 << 1)
#define PERI_CLK3_I2C1                (1 << 2)
#define PERI_CLK3_I2C2                (1 << 3)
#define PERI_CLK3_I2C3                (1 << 4)
#define PERI_CLK3_UART1                (1 << 5)
#define PERI_CLK3_UART2                (1 << 6)
#define PERI_CLK3_UART3                (1 << 7)
#define PERI_CLK3_UART4                (1 << 8)
#define PERI_CLK3_SSP                (1 << 9)
#define PERI_CLK3_PWM                (1 << 10)
#define PERI_CLK3_BLPWM                (1 << 11)
#define PERI_CLK3_TSENSOR            (1 << 12)
#define PERI_CLK3_GPS                (1 << 15)
#define PERI_CLK3_TCXO_PAD0            (1 << 16)
#define PERI_CLK3_TCXO_PAD1            (1 << 17)
#define PERI_CLK3_DAPB                (1 << 18)
#define PERI_CLK3_HKADC                (1 << 19)
#define PERI_CLK3_CODEC_SSI            (1 << 20)
#define PERI_CLK3_TZPC_DEP            (1 << 21)

/*
 * PERI_SC_PERIPH_CLKEN8
 * PERI_SC_PERIPH_CLKDIS8
 * PERI_SC_PERIPH_CLKSTAT8
 */
#define PERI_CLK8_RS0                (1 << 0)
#define PERI_CLK8_RS2                (1 << 1)
#define PERI_CLK8_RS3                (1 << 2)
#define PERI_CLK8_MS0                (1 << 3)
#define PERI_CLK8_MS2                (1 << 5)
#define PERI_CLK8_XG2RAM0            (1 << 6)
#define PERI_CLK8_X2SRAM            (1 << 7)
#define PERI_CLK8_SRAM                (1 << 8)
#define PERI_CLK8_ROM                (1 << 9)
#define PERI_CLK8_HARQ                (1 << 10)
#define PERI_CLK8_MMU                (1 << 11)
#define PERI_CLK8_DDRC                (1 << 12)
#define PERI_CLK8_DDRPHY            (1 << 13)
#define PERI_CLK8_DDRPHY_REF            (1 << 14)
#define PERI_CLK8_X2X_SYSNOC            (1 << 15)
#define PERI_CLK8_X2X_CCPU            (1 << 16)
#define PERI_CLK8_DDRT                (1 << 17)
#define PERI_CLK8_DDRPACK_RS            (1 << 18)

/*
 * PERI_SC_PERIPH_CLKEN9
 * PERI_SC_PERIPH_CLKDIS9
 * PERI_SC_PERIPH_CLKSTAT9
 */
#define PERI_CLK9_CARM_DAP            (1 << 0)
#define PERI_CLK9_CARM_ATB            (1 << 1)
#define PERI_CLK9_CARM_LBUS            (1 << 2)
#define PERI_CLK9_CARM_KERNEL            (1 << 3)

/*
 * PERI_SC_PERIPH_CLKEN10
 * PERI_SC_PERIPH_CLKDIS10
 * PERI_SC_PERIPH_CLKSTAT10
 */
#define PERI_CLK10_IPF_CCPU            (1 << 0)
#define PERI_CLK10_SOCP_CCPU            (1 << 1)
#define PERI_CLK10_SECENG_CCPU            (1 << 2)
#define PERI_CLK10_HARQ_CCPU            (1 << 3)
#define PERI_CLK10_IPF_MCU            (1 << 16)
#define PERI_CLK10_SOCP_MCU            (1 << 17)
#define PERI_CLK10_SECENG_MCU            (1 << 18)
#define PERI_CLK10_HARQ_MCU            (1 << 19)

/*
 * PERI_SC_PERIPH_CLKEN12
 * PERI_SC_PERIPH_CLKDIS12
 * PERI_SC_PERIPH_CLKSTAT12
 */
#define PERI_CLK12_HIFI_SRC            (1 << 0)
#define PERI_CLK12_MMC0_SRC            (1 << 1)
#define PERI_CLK12_MMC1_SRC            (1 << 2)
#define PERI_CLK12_MMC2_SRC            (1 << 3)
#define PERI_CLK12_SYSPLL_DIV            (1 << 4)
#define PERI_CLK12_TPIU_SRC            (1 << 5)
#define PERI_CLK12_MMC0_HF            (1 << 6)
#define PERI_CLK12_MMC1_HF            (1 << 7)
#define PERI_CLK12_PLL_TEST_SRC            (1 << 8)
#define PERI_CLK12_CODEC_SOC            (1 << 9)
#define PERI_CLK12_MEDIA            (1 << 10)

/*
 * PERI_SC_PERIPH_RSTEN0
 * PERI_SC_PERIPH_RSTDIS0
 * PERI_SC_PERIPH_RSTSTAT0
 */
#define PERI_RST0_MMC0                (1 << 0)
#define PERI_RST0_MMC1                (1 << 1)
#define PERI_RST0_MMC2                (1 << 2)
#define PERI_RST0_NANDC                (1 << 3)
#define PERI_RST0_USBOTG_BUS            (1 << 4)
#define PERI_RST0_POR_PICOPHY            (1 << 5)
#define PERI_RST0_USBOTG            (1 << 6)
#define PERI_RST0_USBOTG_32K            (1 << 7)

/*
 * PERI_SC_PERIPH_RSTEN1
 * PERI_SC_PERIPH_RSTDIS1
 * PERI_SC_PERIPH_RSTSTAT1
 */
#define PERI_RST1_HIFI                (1 << 0)
#define PERI_RST1_DIGACODEC            (1 << 5)

/*
 * PERI_SC_PERIPH_RSTEN2
 * PERI_SC_PERIPH_RSTDIS2
 * PERI_SC_PERIPH_RSTSTAT2
 */
#define PERI_RST2_IPF                (1 << 0)
#define PERI_RST2_SOCP                (1 << 1)
#define PERI_RST2_DMAC                (1 << 2)
#define PERI_RST2_SECENG            (1 << 3)
#define PERI_RST2_ABB                (1 << 4)
#define PERI_RST2_HPM0                (1 << 5)
#define PERI_RST2_HPM1                (1 << 6)
#define PERI_RST2_HPM2                (1 << 7)
#define PERI_RST2_HPM3                (1 << 8)

/*
 * PERI_SC_PERIPH_RSTEN3
 * PERI_SC_PERIPH_RSTDIS3
 * PERI_SC_PERIPH_RSTSTAT3
 */
#define PERI_RST3_CSSYS                (1 << 0)
#define PERI_RST3_I2C0                (1 << 1)
#define PERI_RST3_I2C1                (1 << 2)
#define PERI_RST3_I2C2                (1 << 3)
#define PERI_RST3_I2C3                (1 << 4)
#define PERI_RST3_UART1                (1 << 5)
#define PERI_RST3_UART2                (1 << 6)
#define PERI_RST3_UART3                (1 << 7)
#define PERI_RST3_UART4                (1 << 8)
#define PERI_RST3_SSP                (1 << 9)
#define PERI_RST3_PWM                (1 << 10)
#define PERI_RST3_BLPWM                (1 << 11)
#define PERI_RST3_TSENSOR            (1 << 12)
#define PERI_RST3_DAPB                (1 << 18)
#define PERI_RST3_HKADC                (1 << 19)
#define PERI_RST3_CODEC                (1 << 20)

/*
 * PERI_SC_PERIPH_RSTEN8
 * PERI_SC_PERIPH_RSTDIS8
 * PERI_SC_PERIPH_RSTSTAT8
 */
#define PERI_RST8_RS0                (1 << 0)
#define PERI_RST8_RS2                (1 << 1)
#define PERI_RST8_RS3                (1 << 2)
#define PERI_RST8_MS0                (1 << 3)
#define PERI_RST8_MS2                (1 << 5)
#define PERI_RST8_XG2RAM0            (1 << 6)
#define PERI_RST8_X2SRAM_TZMA            (1 << 7)
#define PERI_RST8_SRAM                (1 << 8)
#define PERI_RST8_HARQ                (1 << 10)
#define PERI_RST8_DDRC                (1 << 12)
#define PERI_RST8_DDRC_APB            (1 << 13)
#define PERI_RST8_DDRPACK_APB            (1 << 14)
#define PERI_RST8_DDRT                (1 << 17)

#endif /* __HI6220_PERI_H__ */
