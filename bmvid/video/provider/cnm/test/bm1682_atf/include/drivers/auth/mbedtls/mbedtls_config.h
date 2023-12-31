/*
 * Copyright (c) 2015-2017, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */
#ifndef __MBEDTLS_CONFIG_H__
#define __MBEDTLS_CONFIG_H__

/*
 * Key algorithms currently supported on mbed TLS libraries
 */
#define TF_MBEDTLS_RSA        1
#define TF_MBEDTLS_ECDSA    2

/*
 * Configuration file to build mbed TLS with the required features for
 * Trusted Boot
 */

#define MBEDTLS_PLATFORM_MEMORY
#define MBEDTLS_PLATFORM_NO_STD_FUNCTIONS
/* Prevent mbed TLS from using snprintf so that it can use tf_snprintf. */
#define MBEDTLS_PLATFORM_SNPRINTF_ALT

#if !ERROR_DEPRECATED
#define MBEDTLS_PKCS1_V15
#endif
#define MBEDTLS_PKCS1_V21

#define MBEDTLS_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION
#define MBEDTLS_X509_CHECK_KEY_USAGE
#define MBEDTLS_X509_CHECK_EXTENDED_KEY_USAGE
#define MBEDTLS_X509_RSASSA_PSS_SUPPORT

#define MBEDTLS_ASN1_PARSE_C
#define MBEDTLS_ASN1_WRITE_C

#define MBEDTLS_BASE64_C
#define MBEDTLS_BIGNUM_C

#define MBEDTLS_ERROR_C
#define MBEDTLS_MD_C

#define MBEDTLS_MEMORY_BUFFER_ALLOC_C
#define MBEDTLS_OID_C

#define MBEDTLS_PK_C
#define MBEDTLS_PK_PARSE_C
#define MBEDTLS_PK_WRITE_C

#define MBEDTLS_PLATFORM_C

#if (TF_MBEDTLS_KEY_ALG_ID == TF_MBEDTLS_ECDSA)
#define MBEDTLS_ECDSA_C
#define MBEDTLS_ECP_C
#define MBEDTLS_ECP_DP_SECP256R1_ENABLED
#elif (TF_MBEDTLS_KEY_ALG_ID == TF_MBEDTLS_RSA)
#define MBEDTLS_RSA_C
#endif

#define MBEDTLS_SHA256_C

#define MBEDTLS_VERSION_C

#define MBEDTLS_X509_USE_C
#define MBEDTLS_X509_CRT_PARSE_C

/* MPI / BIGNUM options */
#define MBEDTLS_MPI_WINDOW_SIZE              2
#define MBEDTLS_MPI_MAX_SIZE               256

/* Memory buffer allocator options */
#define MBEDTLS_MEMORY_ALIGN_MULTIPLE        8

#include "mbedtls/check_config.h"

/* System headers required to build mbed TLS with the current configuration */
#include <stdlib.h>

#endif /* __MBEDTLS_CONFIG_H__ */
