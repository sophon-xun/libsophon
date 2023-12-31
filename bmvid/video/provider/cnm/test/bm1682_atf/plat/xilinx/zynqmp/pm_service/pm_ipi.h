/*
 * Copyright (c) 2013-2015, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#ifndef _PM_IPI_H_
#define _PM_IPI_H_

#include "pm_common.h"

int pm_ipi_init(void);

enum pm_ret_status pm_ipi_send(const struct pm_proc *proc,
                   uint32_t payload[PAYLOAD_ARG_CNT]);
enum pm_ret_status pm_ipi_send_sync(const struct pm_proc *proc,
                    uint32_t payload[PAYLOAD_ARG_CNT],
                    unsigned int *value, size_t count);
void pm_ipi_buff_read_callb(unsigned int *value, size_t count);
void pm_ipi_irq_enable(void);
void pm_ipi_irq_disable(void);
void pm_ipi_irq_clear(void);

#endif /* _PM_IPI_H_ */
