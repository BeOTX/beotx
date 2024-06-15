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

#include "hal/gpio.h"
#include "stm32_gpio.h"
#include "boards/generic_stm32/rgb_leds.h"
#include "board.h"
#if defined(LED_STRIP_GPIO)
#include "boards/generic_stm32/rgb_leds.h"
#endif

#define GET_RED(color) (((color) & 0xF800) >> 8)
#define GET_GREEN(color) (((color) & 0x07E0) >> 3)
#define GET_BLUE(color) (((color) & 0x001F) << 3)

#if defined(FUNCTION_SWITCHES)
static const uint32_t fsLeds[] = {FSLED_GPIO_PIN_1, FSLED_GPIO_PIN_2,
				  FSLED_GPIO_PIN_3, FSLED_GPIO_PIN_4,
				  FSLED_GPIO_PIN_5, FSLED_GPIO_PIN_6};
#endif

void ledInit()
{
#if defined(LED_GREEN_GPIO)
  gpio_init(LED_GREEN_GPIO, GPIO_OUT, GPIO_PIN_SPEED_LOW);
#endif

#if defined(LED_RED_GPIO)
  gpio_init(LED_RED_GPIO, GPIO_OUT, GPIO_PIN_SPEED_LOW);
#endif

#if defined(LED_BLUE_GPIO)
  gpio_init(LED_BLUE_GPIO, GPIO_OUT, GPIO_PIN_SPEED_LOW);
#endif

#if defined(FUNCTION_SWITCHES) && !defined(FSLEDS_USE_RGB)
  for (size_t i = 0; i < DIM(fsLeds); i++) {
    gpio_init(fsLeds[i], GPIO_OUT, GPIO_PIN_SPEED_LOW);
  }
#endif
}

#if defined(FUNCTION_SWITCHES_RGB_LEDS)
// used to map switch number to led number in the rgbled chain
uint8_t ledMapping[] = {1, 2, 3, 4, 5, 6};

void fsLedOff(uint8_t index, uint32_t color)
{
   rgbSetLedColor(ledMapping[index], GET_RED(color), \
   GET_GREEN(color),GET_BLUE(color));
}

void fsLedOn(uint8_t index, uint32_t color)
{
   rgbSetLedColor(ledMapping[index], GET_RED(color), \
   GET_GREEN(color),GET_BLUE(color));
}

uint8_t getRGBColorIndex(uint32_t color)
{
  static const uint32_t colorTable[] = {0xFFFFFF, 0xF80000, 0x00FC00, 0x0000F8, 0x000000}; // White, red, green, blue, off

  for (uint8_t i = 0; i < (sizeof(colorTable) / sizeof(colorTable[0])); i++) {
    if (color == colorTable[i])
      return(i);
  }
  return 5; // Custom value set with Companion
}
#elif defined(FUNCTION_SWITCHES)
void fsLedOff(uint8_t index)
{
  gpio_clear(fsLeds[index]);
}

void fsLedOn(uint8_t index)
{
  gpio_set(fsLeds[index]);
}

bool fsLedState(uint8_t index)
{
  return gpio_read(fsLeds[index]) ? true : false;
}
#endif

void ledOff()
{
#if defined(LED_RED_GPIO)
  GPIO_LED_GPIO_OFF(LED_RED_GPIO);
#endif
#if defined(LED_BLUE_GPIO)
  GPIO_LED_GPIO_OFF(LED_BLUE_GPIO);
#endif
#if defined(LED_GREEN_GPIO)
  GPIO_LED_GPIO_OFF(LED_GREEN_GPIO);
#endif
}

void ledRed()
{
  ledOff();
#if defined(LED_RED_GPIO)
  GPIO_LED_GPIO_ON(LED_RED_GPIO);
#endif
}

void ledGreen()
{
  ledOff();
#if defined(LED_GREEN_GPIO)
  GPIO_LED_GPIO_ON(LED_GREEN_GPIO);
#endif
}

void ledBlue()
{
  ledOff();
#if defined(LED_BLUE_GPIO)
  GPIO_LED_GPIO_ON(LED_BLUE_GPIO);
#endif
}
