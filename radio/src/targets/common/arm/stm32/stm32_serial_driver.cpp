/*
 * Copyright (C) EdgeTx
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

#include "stm32_serial_driver.h"
// #include "stm32_hal_ll.h"
// #include "stm32_usart_driver.h"
#include <string.h>

// Serial buffer state
struct stm32_buffer_state {
  volatile uint32_t ridx;
  volatile uint32_t widx;
};

struct stm32_send_buffer {
  volatile const uint8_t* buf;
  volatile uint32_t len;
};

struct stm32_serial_state {
  const stm32_serial_port* sp;
  stm32_buffer_state rx_buf;
  union {
    stm32_buffer_state tx_fifo;
    stm32_send_buffer  tx_buf;
  } u;
  etx_serial_callbacks_t callbacks;
};

enum _STM32_USART {

#if defined(USART1)
  _STM32_USART1,
#endif

#if defined(USART2)
  _STM32_USART2,
#endif

#if defined(USART3)
  _STM32_USART3,
#endif

#if defined(UART4)
  _STM32_UART4,
#endif

#if defined(USART6)
  _STM32_USART6,
#endif

#if defined(UART7)
  _STM32_UART7,
#endif

  _STM32_MAX_UARTS
};

#define STM32_MAX_UART_PORTS _STM32_MAX_UARTS

// allocated as needed: index does not correspond
static stm32_serial_state _serial_states[STM32_MAX_UART_PORTS];

void stm32_serial_init_driver()
{
  memset(_serial_states, 0, sizeof(_serial_states));
}

// Serial context to be used in callbacks
// defined in this driver
static volatile stm32_serial_state* _isr_state;

static uint8_t _on_send_fifo(uint8_t* data)
{
  auto st = _isr_state;
  auto& buf_st = st->u.tx_fifo;

  if (buf_st.ridx == buf_st.widx)
    return 0;

  const auto& tx_buf = st->sp->tx_buffer;
  auto buf = tx_buf.buffer;
  *data = buf[buf_st.ridx];

  auto buf_len = tx_buf.length;
  buf_st.ridx = (buf_st.ridx + 1) & (buf_len - 1);

  return 1;  
}

static uint8_t _on_send_single_buffer(uint8_t* data)
{
  auto sb = &_isr_state->u.tx_buf;
  if (!sb->len) return 0;

  *data = *(sb->buf++);
  sb->len--;

  return 1;
}

static inline void _usart_isr_handler(_STM32_USART n)
{
  auto st = &(_serial_states[n]);

  // This tricks is necessary for now to allow
  // callbacks to use the serial context while
  // keeping the callbacks re-entrant
  auto old_st = _isr_state;
  _isr_state = st;

  stm32_usart_isr(st->sp->usart, &st->callbacks);

  _isr_state = old_st;
}

#define DEFINE_USART_IRQ(usart)                 \
  extern "C" void usart ## _IRQHandler(void)    \
  {                                             \
    _usart_isr_handler(_STM32_ ## usart);       \
  }

#if defined (USART1)
  DEFINE_USART_IRQ(USART1);
#endif

#if defined (USART2)
  DEFINE_USART_IRQ(USART2);
#endif

// #if defined (USART3)
//   DEFINE_USART_IRQ(USART3);
// #endif

#if defined (UART4)
  DEFINE_USART_IRQ(UART4);
#endif

#if defined (USART6)
  DEFINE_USART_IRQ(USART6);
#endif

static stm32_serial_state* stm32_serial_find_state(const stm32_usart_t* usart)
{
#if defined (USART1)
  if (usart->USARTx == USART1) return &_serial_states[_STM32_USART1];
#endif
#if defined (USART2)
  if (usart->USARTx == USART2) return &_serial_states[_STM32_USART2];
#endif
#if defined (USART3)
  if (usart->USARTx == USART3) return &_serial_states[_STM32_USART3];
#endif
#if defined (UART4)
  if (usart->USARTx == UART4) return &_serial_states[_STM32_UART4];
#endif
#if defined (USART6)
  if (usart->USARTx == USART6) return &_serial_states[_STM32_USART6];
#endif

  return nullptr;
}

static void stm32_serial_free_state(stm32_serial_state* st)
{
  memset(st, 0, sizeof(stm32_serial_state));
}

static inline void _dma_clear(stm32_buffer_state* buf_st, uint32_t length,
                              DMA_TypeDef* DMAx, uint32_t stream)
{
  buf_st->ridx = length - LL_DMA_GetDataLength(DMAx, stream);
}

static inline void _fifo_clear(stm32_buffer_state* buf_st)
{
  buf_st->widx = buf_st->ridx = 0;
}

static inline bool _fifo_full(stm32_buffer_state* buf_st, uint32_t length)
{
  return ((buf_st->widx + 1) & (length - 1)) == buf_st->ridx;
}

static inline void _fifo_push(uint8_t c, stm32_buffer_state* buf_st,
                              uint32_t length, uint8_t* buf)
{
  buf_st->widx = (buf_st->widx + 1) & (length - 1);
  buf[buf_st->widx] = c;
}

static void _on_rx_fifo(uint8_t data)
{
  auto st = _isr_state;
  stm32_buffer_state* buf_st = (stm32_buffer_state*)&st->rx_buf;

  auto buf_len = st->sp->rx_buffer.length;
  if (_fifo_full(buf_st, buf_len)) return;

  auto buf = st->sp->rx_buffer.buffer;
  _fifo_push(data, buf_st, buf_len, buf);
}

static void* stm32_serial_init(void* hw_def, const etx_serial_init* params)
{
  // TODO: check if port is already in use
  auto sp = (const stm32_serial_port*)hw_def;
  if (!sp) return nullptr;

  auto usart = sp->usart;
  auto st = stm32_serial_find_state(usart);
  if (!st || st->sp) return nullptr;

  stm32_usart_init(usart, params);
  st->sp = sp; // TODO: only iff init() is sucessful

  // prepare for send_byte()
  if (sp->tx_buffer.length > 0) {
    st->callbacks.on_send = _on_send_fifo;
  }

  if (params->rx_enable) {

    auto rx_buf = sp->rx_buffer.buffer;
    auto buf_len = sp->rx_buffer.length;

    if (usart->rxDMA) {
      stm32_usart_init_rx_dma(usart, rx_buf, buf_len);

      auto dma = usart->rxDMA;
      auto stream = usart->rxDMA_Stream;
      _dma_clear(&st->rx_buf, buf_len, dma, stream);
    } else {
      st->callbacks.on_receive = _on_rx_fifo;
    }
  }

  return (void*)st;
}

static void stm32_serial_deinit(void* ctx)
{
  auto st = (stm32_serial_state*)ctx;
  if (!st) return;

  stm32_usart_deinit(st->sp->usart);
  stm32_serial_free_state(st);
}

static void stm32_serial_send_byte(void* ctx, uint8_t c)
{
  // When sending single bytes,
  // send is based on IRQ, so that this
  // only enables the corresponding IRQ

  auto st = (stm32_serial_state*)ctx;
  if (!st) return;

  auto sp = st->sp;
  auto buf_len = sp->tx_buffer.length;
  if (buf_len > 0) {
  
    auto buf_st = &st->u.tx_fifo;
    auto buf = sp->tx_buffer.buffer;

    if (_fifo_full(buf_st, buf_len)) return;
    _fifo_push(c, buf_st, buf_len, buf);

    stm32_usart_enable_tx_irq(sp->usart);
  } else {
    // No TX FIFO -> fall back to sync send
    stm32_usart_send_byte(sp->usart, c);
  }
}

static void stm32_serial_send_buffer(void* ctx, const uint8_t* data, uint8_t size)
{
  auto st = (stm32_serial_state*)ctx;
  if (!st) return;

  // try TX DMA first
  auto sp = st->sp;
  auto usart = sp->usart;
  if (usart->txDMA) {
    stm32_usart_send_buffer(usart, data, size);
    return;
  }

  // no internal buffer: send one buffer at a time
  if (!sp->tx_buffer.length) {
    st->u.tx_buf.buf = data;
    st->u.tx_buf.len = size;
    st->callbacks.on_send = _on_send_single_buffer;
    stm32_usart_enable_tx_irq(usart);
    return;
  }

  // else stack single bytes into our internal buffer
  while(size > 0) {
    stm32_serial_send_byte(ctx, *data++);
    size--;
  }
}

static void stm32_wait_tx_completed(void* ctx)
{
  // TODO
  (void)ctx;
}

static void stm32_enable_rx(void* ctx)
{
  auto st = (stm32_serial_state*)ctx;
  if (!st) return;

  stm32_usart_enable_rx(st->sp->usart);
}

static int stm32_serial_get_byte(void* ctx, uint8_t* data)
{
  auto st = (stm32_serial_state*)ctx;
  if (!st) return -1;

  auto sp = st->sp;
  const auto& rx_buf = sp->rx_buffer;
  auto buf_len = rx_buf.length;
  if (!buf_len) return -1;
  
  auto buf = rx_buf.buffer;
  auto& buf_st = st->rx_buf;

  uint32_t widx;
  auto usart = sp->usart;
  if (usart->rxDMA) {
    auto dma = usart->rxDMA;
    auto stream = usart->rxDMA_Stream;
    if (!LL_DMA_IsEnabledStream(dma, stream)) return 0;
    widx = LL_DMA_GetDataLength(dma, stream);
  } else {
    widx = buf_st.widx;
  }

  if (buf_st.ridx == widx)
    return 0;

  *data = buf[buf_st.ridx];
  buf_st.ridx = (buf_st.ridx + 1) & (buf_len - 1);

  return 1;
}

static void stm32_serial_clear_rx_buffer(void* ctx)
{
  auto st = (stm32_serial_state*)ctx;
  if (!st) return;

  auto sp = st->sp;
  auto buf_st = &st->rx_buf;
  auto usart = sp->usart;
  if (usart->rxDMA) {
    auto buf_len = sp->rx_buffer.length;
    auto dma = usart->rxDMA;
    auto stream = usart->rxDMA_Stream;
    _dma_clear(buf_st, buf_len, dma, stream);
  } else {
    _fifo_clear(buf_st);
  }
}

const etx_serial_driver_t STM32SerialDriver = {
  .init = stm32_serial_init,
  .deinit = stm32_serial_deinit,
  .sendByte = stm32_serial_send_byte,
  .sendBuffer = stm32_serial_send_buffer,
  .waitForTxCompleted = stm32_wait_tx_completed,
  .enableRx = stm32_enable_rx,
  .getByte = stm32_serial_get_byte,
  .clearRxBuffer = stm32_serial_clear_rx_buffer,
  .getBaudrate = nullptr,
  .setReceiveCb = nullptr, // TODO
  .setBaudrateCb = nullptr,
};
