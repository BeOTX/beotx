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

#ifndef _CLI_H_
#define _CLI_H_

#include "hal/serial_driver.h"

typedef enum CLiMode_e {
  CLI_MODE_COMMAND = 0,
  #if defined(ELDB)
  CLI_MODE_ELDP = 1
  #endif
} CLIMode_t;

// SHOULD NOT BE SET OUTSIDE OF cli.cpp
extern CLIMode_t cliMode;

// CLI task function
void cliStart();

// Connect serial driver to CLI
void cliSetSerialDriver(void* ctx, const etx_serial_driver_t* drv);

#if defined(ELDB)
bool cliELDPSend(uint8_t *buf, size_t len);
#endif

#endif // _CLI_H_
