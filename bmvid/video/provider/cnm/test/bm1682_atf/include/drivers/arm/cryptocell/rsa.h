/*
 * Copyright (c) 2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef RSA_H
#define RSA_H

/*
 * All the includes that are needed for code using this module to
 * compile correctly should be #included here.
 */

#ifdef __cplusplus
extern "C"
{
#endif

#include "cc_pal_types.h"

/************************ Defines ******************************/

/* the modulus size ion bits */
#define RSA_MOD_SIZE_IN_BITS                2048UL
#define RSA_MOD_SIZE_IN_BYTES                (CALC_FULL_BYTES(RSA_MOD_SIZE_IN_BITS))
#define RSA_MOD_SIZE_IN_WORDS                (CALC_FULL_32BIT_WORDS(RSA_MOD_SIZE_IN_BITS))
#define RSA_MOD_SIZE_IN_256BITS                (RSA_MOD_SIZE_IN_WORDS/8)
#define RSA_EXP_SIZE_IN_BITS                17UL
#define RSA_EXP_SIZE_IN_BYTES                (CALC_FULL_BYTES(RSA_EXP_SIZE_IN_BITS))

/* size of buffer for Barrett modulus tag NP, used in PKA algorithms */
#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS    132
#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BYTES    (CALC_FULL_BYTES(RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS))
#define RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_WORDS    (CALC_FULL_32BIT_WORDS(RSA_HW_PKI_PKA_BARRETT_MOD_TAG_SIZE_IN_BITS))

/*
 * @brief The RSA_CalcNp calculates Np value and saves it into Np_ptr:
 *
 *

 * @param[in] hwBaseAddress -    HW base address. Relevant for HW
 *                implementation, for SW it is ignored.
 * @N_ptr[in]               -    The pointer to the modulus buffer.
 * @Np_ptr[out]             -    pointer to Np vector buffer. Its size must be >= 160.
 */
void RSA_CalcNp(unsigned long hwBaseAddress,
        uint32_t *N_ptr,
        uint32_t *Np_ptr);

#ifdef __cplusplus
}
#endif

#endif
