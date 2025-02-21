/*
 * Copyright (C) EdgeTX
 *
 * Based on code named
 *   opentx - https://github.com/opentx/opentx
 *   th9x - http://code.google.com/p/th9x
 *   er9x - http://code.google.com/p/er9x
 *   gruvin9x - http://code.google.com/p/gruvin9x
 *
 * License GPLv2: http://www.gnu.org/licenses/gpl-2.0.html
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#pragma once

#include <FreeRTOS/include/FreeRTOS.h>
#include <FreeRTOS/include/timers.h>

struct timer_handle_t {
  TimerHandle_t _rtos_handle;
  StaticTimer_t _timer_struct;
};

typedef TimerHandle_t timer_os_handle_t;
typedef void (*timer_func_t)(TimerHandle_t);

#define TIMER_INITIALIZER { ._rtos_handle = nullptr }
#define TIMER_FUNCTION(func) void func(timer_os_handle_t osTimer)
