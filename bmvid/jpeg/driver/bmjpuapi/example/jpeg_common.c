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

#include "jpeg_common.h"

void logging_fn(BmJpuLogLevel level, char const *file, int const line, char const *fn, const char *format, ...)
{
    va_list args;

    char const *lvlstr = "";
    switch (level)
    {
        case BM_JPU_LOG_LEVEL_ERROR:   lvlstr = "ERROR";   break;
        case BM_JPU_LOG_LEVEL_WARNING: lvlstr = "WARNING"; break;
        case BM_JPU_LOG_LEVEL_INFO:    lvlstr = "INFO";    break;
        case BM_JPU_LOG_LEVEL_DEBUG:   lvlstr = "DEBUG";   break;
        case BM_JPU_LOG_LEVEL_TRACE:   lvlstr = "TRACE";   break;
        case BM_JPU_LOG_LEVEL_LOG:     lvlstr = "LOG";     break;
        default: break;
    }

    fprintf(stderr, "%s:%d (%s)   %s: ", file, line, fn, lvlstr);

    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);

    fprintf(stderr, "\n");
}

