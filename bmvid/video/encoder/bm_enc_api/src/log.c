/* bmvpuapi API library for the BitMain Sophon SoC
 *
 * Copyright (C) 2018 Solan Shang
 * Copyright (C) 2014 Carlos Rafael Giani
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301
 * USA
 */

#include <string.h>
#include <stdlib.h>

#include "bmvpuapi.h"
#include "bmvpuapi_internal.h"
#include "bmvpu_logging.h"


static void default_logging_fn(BmVpuLogLevel level, char const *file,
                               int const line, char const *fn,
                               const char *format, ...)
{
    BMVPUAPI_UNUSED_PARAM(level);
    BMVPUAPI_UNUSED_PARAM(file);
    BMVPUAPI_UNUSED_PARAM(line);
    BMVPUAPI_UNUSED_PARAM(fn);
    BMVPUAPI_UNUSED_PARAM(format);
}

BmVpuLogLevel bmvpu_cur_log_level_threshold = BM_VPU_LOG_LEVEL_ERROR;
BmVpuLoggingFunc bmvpu_cur_logging_fn = default_logging_fn;

void bmvpu_set_logging_function(BmVpuLoggingFunc logging_fn)
{
    bmvpu_cur_logging_fn = (logging_fn != NULL) ? logging_fn : default_logging_fn;
}

void bmvpu_set_logging_threshold(BmVpuLogLevel threshold)
{
    bmvpu_cur_log_level_threshold = threshold;
    vpu_set_logging_threshold(threshold);
}

BmVpuLogLevel bmvpu_get_logging_threshold()
{
    return bmvpu_cur_log_level_threshold;
}

