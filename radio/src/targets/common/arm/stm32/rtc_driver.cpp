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

#include "stm32_hal.h"
#include "rtc.h"
#include "debug.h"

//
// Color screen targets use the first 2 out of the 20 
// RTC backup registers to hold data about startup reason 
// and type.

//
// Calculates the RTC backup memory checksum and stores it
// in the last backup register location (BKP19R).
//
#define RTCCHKSUM() ((RTC->BKP0R ^ RTC->BKP1R) + 45444745)

//  
// resets RTC backup registers if data is corrupt
// and returns the requested backup register
// 
uint32_t getRTCBKPR(uint8_t RTCBKPRegister) {
  uint32_t prim = __get_PRIMASK();
  
  __disable_irq();
  
  if(RTC->BKP19R != RTCCHKSUM()) {
    RTC->BKP0R = 0;
    RTC->BKP1R = 0;
    RTC->BKP19R = RTCCHKSUM();
  }

  uint32_t value = ((uint32_t *)RTCBKBR_BASE)[RTCBKPRegister];   // RTC backup registers are 32bit registers

  if(!prim) 
    __enable_irq();

  return value;
}

//  
// writes data to the specified RTC backup register
// and updates the checksum
// 
void setRTCBKPR(uint8_t RTCBKPRegister, uint32_t value) {
  uint32_t prim = __get_PRIMASK();

  __disable_irq();

  ((uint32_t *)RTCBKBR_BASE)[RTCBKPRegister] = value;   // RTC backup registers are 32bit registers

  RTC->BKP19R = RTCCHKSUM();

  if(!prim) 
    __enable_irq();
}

RTC_HandleTypeDef rtc = {};

void rtcSetTime(const struct gtm * t)
{
  g_ms100 = 0; // start of next second begins now

  RTC_TimeTypeDef RTC_TimeStruct = {};
  RTC_DateTypeDef RTC_DateStruct = {};

  RTC_TimeStruct.Hours = t->tm_hour;
  RTC_TimeStruct.Minutes = t->tm_min;
  RTC_TimeStruct.Seconds = t->tm_sec;
  RTC_DateStruct.Year = t->tm_year - 100;
  RTC_DateStruct.Month = t->tm_mon + 1;
  RTC_DateStruct.Date = t->tm_mday;
  HAL_RTC_SetTime(&rtc, &RTC_TimeStruct, RTC_FORMAT_BIN);
  HAL_RTC_SetDate(&rtc, &RTC_DateStruct, RTC_FORMAT_BIN);
}

void rtcGetTime(struct gtm * t)
{
  RTC_TimeTypeDef RTC_TimeStruct;
  RTC_DateTypeDef RTC_DateStruct;

  HAL_RTC_GetTime(&rtc, &RTC_TimeStruct, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&rtc, &RTC_DateStruct, RTC_FORMAT_BIN);
  
  t->tm_hour = RTC_TimeStruct.Hours;
  t->tm_min  = RTC_TimeStruct.Minutes;
  t->tm_sec  = RTC_TimeStruct.Seconds;
  t->tm_year = RTC_DateStruct.Year + 100; // STM32 year is two decimals only (so base is currently 2000), gtm is based on number of years since 1900
  t->tm_mon  = RTC_DateStruct.Month - 1;
  t->tm_mday = RTC_DateStruct.Date;
}

void rtcInit()
{
  rtc.Instance = RTC;
  __HAL_RCC_PWR_CLK_ENABLE();
  HAL_PWR_EnableBkUpAccess();

  // Enable LSE Oscillator
  RCC_OscInitTypeDef RCC_OscInitStruct;
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.PLL.PLLState   = RCC_PLL_NONE;
  RCC_OscInitStruct.LSEState       = RCC_LSE_ON;

  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) == HAL_OK) {
    __HAL_RCC_RTC_CLKPRESCALER(RCC_RTCCLKSOURCE_LSE);
    __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSE);
  }

  __HAL_RCC_RTC_ENABLE();
  HAL_RTC_WaitForSynchro(&rtc);

#if !defined(BOOT)
  // RTC time base = LSE / ((AsynchPrediv+1) * (SynchPrediv+1)) = 1 Hz*/
  rtc.Init.HourFormat = RTC_HOURFORMAT_24;
  rtc.Init.AsynchPrediv = 127;
  rtc.Init.SynchPrediv = 255;
  rtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  rtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  rtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  HAL_RTC_Init(&rtc);

  struct gtm utm;
  rtcGetTime(&utm);
  g_rtcTime = gmktime(&utm);
#endif
#if defined(RTC_BACKUP_RAM) && !defined(BOOT)
  __HAL_RCC_BKPSRAM_CLK_ENABLE();
  HAL_PWREx_EnableBkUpReg();
#endif
}
