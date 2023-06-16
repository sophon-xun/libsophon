/**
 * Copyright (C) 2018 Solan Shang
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

#ifndef __JPEG_COMMON_H__
#define __JPEG_COMMON_H__

#include <stdio.h>
#include <stdarg.h>
#include "bmjpuapi.h"

#define RETVAL_OK     0
#define RETVAL_ERROR  1
#define RETVAL_EOS    2

void logging_fn(BmJpuLogLevel level, char const *file, int const line, char const *fn, const char *format, ...);

#endif /* __JPEG_COMMON_H__ */

