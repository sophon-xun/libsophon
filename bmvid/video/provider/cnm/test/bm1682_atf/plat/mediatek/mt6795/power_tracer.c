/*
 * Copyright (c) 2016, ARM Limited and Contributors. All rights reserved.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <arch.h>
#include <debug.h>
#include <power_tracer.h>

#define trace_log(...)  INFO("psci: " __VA_ARGS__)

void trace_power_flow(unsigned long mpidr, unsigned char mode)
{
    switch (mode) {
    case CPU_UP:
        trace_log("core %ld:%ld ON\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS,
              (mpidr & MPIDR_CPU_MASK));
        break;
    case CPU_DOWN:
        trace_log("core %ld:%ld OFF\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS,
              (mpidr & MPIDR_CPU_MASK));
        break;
    case CPU_SUSPEND:
        trace_log("core %ld:%ld SUSPEND\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS,
              (mpidr & MPIDR_CPU_MASK));
        break;
    case CLUSTER_UP:
        trace_log("cluster %ld ON\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS);
        break;
    case CLUSTER_DOWN:
        trace_log("cluster %ld OFF\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS);
        break;
    case CLUSTER_SUSPEND:
        trace_log("cluster %ld SUSPEND\n",
              (mpidr & MPIDR_CLUSTER_MASK) >> MPIDR_AFFINITY_BITS);
        break;
    default:
        trace_log("unknown power mode\n");
        break;
    }
}
