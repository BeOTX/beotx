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

#include "opentx.h"
#include "sbus.h"
#include "timers_driver.h"

#define SBUS_FRAME_GAP_DELAY   1000 // 500uS

#define SBUS_START_BYTE        0x0F
#define SBUS_END_BYTE          0x00
#define SBUS_FLAGS_IDX         23
#define SBUS_FRAMELOST_BIT     2
#define SBUS_FAILSAFE_BIT      3

#define SBUS_CH_BITS           11
#define SBUS_CH_MASK           ((1<<SBUS_CH_BITS) - 1)

#define SBUS_CH_CENTER         0x3E0

static int (*_sbusAuxGetByte)(void*, uint8_t*) = nullptr;
static void* _sbusAuxGetByteCtx = nullptr;

void sbusSetAuxGetByte(void* ctx, int (*fct)(void*, uint8_t*))
{
  _sbusAuxGetByte = nullptr;
  _sbusAuxGetByteCtx = ctx;
  _sbusAuxGetByte = fct;
}

int sbusAuxGetByte(uint8_t* byte)
{
  auto _getByte = _sbusAuxGetByte;
  auto _ctx = _sbusAuxGetByteCtx;

  if (_getByte) {
    return _getByte(_ctx, byte);
  }

  return -1;
}

static int (*sbusGetByte)(uint8_t*) = nullptr;

void sbusSetGetByte(int (*fct)(uint8_t*))
{
  sbusGetByte = fct;
}

// Range for pulses (ppm input) is [-512:+512]
void processSbusFrame(uint8_t * sbus, int16_t * pulses, uint32_t size)
{
  if (size != SBUS_FRAME_SIZE || sbus[0] != SBUS_START_BYTE ||
      sbus[SBUS_FRAME_SIZE - 1] != SBUS_END_BYTE) {
    return;  // not a valid SBUS frame
  }
  if ((sbus[SBUS_FLAGS_IDX] & (1 << SBUS_FAILSAFE_BIT)) ||
      (sbus[SBUS_FLAGS_IDX] & (1 << SBUS_FRAMELOST_BIT))) {
    return;  // SBUS invalid frame or failsafe mode
  }

//  sbus++; // skip start byte

//  uint32_t inputbitsavailable = 0;
//  uint32_t inputbits = 0;
//  for (uint32_t i=0; i<MAX_TRAINER_CHANNELS; i++) {
//    while (inputbitsavailable < SBUS_CH_BITS) {
//      inputbits |= *sbus++ << inputbitsavailable;
//      inputbitsavailable += 8;
//    }
//    *pulses++ = ((int32_t) (inputbits & SBUS_CH_MASK) - SBUS_CH_CENTER) * 5 / 8;
//    inputbitsavailable -= SBUS_CH_BITS;
//    inputbits >>= SBUS_CH_BITS;
//  }

//  ppmInputValidityTimer = PPM_IN_VALID_TIMEOUT;
//}

//void processSbusInput()
//{
//#if !defined(SIMU)
//  uint8_t rxchar;
//  uint32_t active = 0;
//  static uint8_t SbusIndex = 0;
//  static uint16_t SbusTimer;
//  static uint8_t SbusFrame[SBUS_FRAME_SIZE];

//  while (sbusGetByte(&rxchar)) {
//    active = 1;
//    if (SbusIndex > SBUS_FRAME_SIZE-1) {
//      SbusIndex = SBUS_FRAME_SIZE-1;
//    }
//    SbusFrame[SbusIndex++] = rxchar;
//  }
//  if (active) {
//    SbusTimer = getTmr2MHz();
//    return;
//  }
//  else {
//    if (SbusIndex) {
//      if ((uint16_t) (getTmr2MHz() - SbusTimer) > SBUS_FRAME_GAP_DELAY) {
//        processSbusFrame(SbusFrame, ppmInput, SbusIndex);
//        SbusIndex = 0;
//      }
//    }
//  }
//#endif
//}

namespace  SBus {
    struct Servo {
        enum class State : uint8_t {Undefined, Data, GotEnd, WaitEnd};

        static constexpr uint8_t mPauseCount{2}; // 2ms
        
        static constexpr uint8_t mFrameLostMask{1 << SBUS_FRAMELOST_BIT};
        static constexpr uint8_t mFailSafeMask{1 << SBUS_FAILSAFE_BIT};
        
        static inline void tick1ms() {
            if (mPauseCounter > 0) {
                --mPauseCounter;
            }
            else {
                mState = State::Undefined;
            }
        }
        
        static inline void process(const uint8_t b, std::function<void()> f) {
            mPauseCounter = mPauseCount;
            switch(mState) {
            case State::Undefined:
                if (b == 0x00) {
                    mState = State::GotEnd;
                }
                else if (b == 0x0f) {
                    mState = State::Data;
                    mIndex = 0;
                }
                break;
            case State::GotEnd:
                if (b == 0x0f) {
                    mState = State::Data;
                    mIndex = 0;
                }
                else if (b == 0x00) {
                    mState = State::GotEnd;
                }
                else {
                    mState = State::Undefined;
                }
                break;
            case State::Data:
                mData[mIndex] = b;
                if (mIndex >= (mData.size() - 1)) {
                    mState = State::WaitEnd;
                }
                else {
                    ++mIndex;
                }
                break;
            case State::WaitEnd:
                if (b == 0x00) {
                    mState = State::GotEnd;
                    if (!((mData[mData.size() - 1] & mFrameLostMask) || (mData[mData.size() - 1] & mFailSafeMask))) {
                        f();
                        ++mPackages;
                    }
                }
                else {
                    mState = State::Undefined;
                }
                break;
            }
        }
        static inline void convert(int16_t* pulses) {
            pulses[0]  = (uint16_t) (((mData[0]    | mData[1] << 8))                 & 0x07FF);
            pulses[1]  = (uint16_t) ((mData[1]>>3  | mData[2] <<5)                   & 0x07FF);
            pulses[2]  = (uint16_t) ((mData[2]>>6  | mData[3] <<2 |mData[4]<<10)  	 & 0x07FF);
            pulses[3]  = (uint16_t) ((mData[4]>>1  | mData[5] <<7)                   & 0x07FF);
            pulses[4]  = (uint16_t) ((mData[5]>>4  | mData[6] <<4)                   & 0x07FF);
            pulses[5]  = (uint16_t) ((mData[6]>>7  | mData[7] <<1 |mData[8]<<9)   	 & 0x07FF);
            pulses[6]  = (uint16_t) ((mData[8]>>2  | mData[9] <<6)                   & 0x07FF);
            pulses[7]  = (uint16_t) ((mData[9]>>5  | mData[10]<<3)                   & 0x07FF);
            pulses[8]  = (uint16_t) ((mData[11]    | mData[12]<<8)                   & 0x07FF);
            pulses[9]  = (uint16_t) ((mData[12]>>3 | mData[13]<<5)                   & 0x07FF);
            pulses[10] = (uint16_t) ((mData[13]>>6 | mData[14]<<2 |mData[15]<<10) 	 & 0x07FF);
            pulses[11] = (uint16_t) ((mData[15]>>1 | mData[16]<<7)                   & 0x07FF);
            pulses[12] = (uint16_t) ((mData[16]>>4 | mData[17]<<4)                   & 0x07FF);
            pulses[13] = (uint16_t) ((mData[17]>>7 | mData[18]<<1 |mData[19]<<9)  	 & 0x07FF);
            pulses[14] = (uint16_t) ((mData[19]>>2 | mData[20]<<6)                   & 0x07FF);
            pulses[15] = (uint16_t) ((mData[20]>>5 | mData[21]<<3)                   & 0x07FF);
            
            for(size_t i = 0; i < 16; ++i) {
                pulses[i] -= SBUS_CH_CENTER;
                pulses[i] *= 5;
                pulses[i] /= 8;
            }
        }
        using MesgType = std::array<uint8_t, 23>;
        static State mState;
        static MesgType mData; 
        static uint8_t mIndex;
        static uint16_t mPackages;
        static uint8_t mPauseCounter;
    };
    Servo::State Servo::mState{State::Undefined};
    Servo::MesgType Servo::mData; 
    uint8_t Servo::mIndex{};
    uint16_t Servo::mPackages{};
    uint8_t Servo::mPauseCounter{Servo::mPauseCount}; // 2 ms
}
void sbusTrainerPauseCheck() {
#if !defined(SIMU)
    SBus::Servo::tick1ms();
#endif    
}

//void processSbusInput()
//{

//  // TODO: place this outside of the function
//  static uint8_t SbusIndex = 0;
//  static uint16_t SbusTimer;
//  static uint8_t SbusFrame[SBUS_FRAME_SIZE];

//  uint32_t active = 0;

//  // Drain input first (if existing)
//  uint8_t rxchar;
//  auto _getByte = sbusGetByte;
//  while (_getByte && (_getByte(&rxchar) > 0)) {
//    active = 1;
//    if (SbusIndex > SBUS_FRAME_SIZE - 1) {
//      SbusIndex = SBUS_FRAME_SIZE - 1;
//    }
//    SbusFrame[SbusIndex++] = rxchar;
//  }

//  // Data has been received
//  if (active) {
//    SbusTimer = getTmr2MHz();
//    return;
//  }

//  // Check if end-of-frame is detected
//  if (SbusIndex) {
//    if ((uint16_t)(getTmr2MHz() - SbusTimer) > SBUS_FRAME_GAP_DELAY) {
//      processSbusFrame(SbusFrame, ppmInput, SbusIndex);
//      SbusIndex = 0;
//    }
//  }

void processSbusInput() {
#if !defined(SIMU)
  uint8_t rxchar;

  while (sbusGetByte(&rxchar)) {
      SBus::Servo::process(rxchar, [&](){
          SBus::Servo::convert(ppmInput);
          ppmInputValidityTimer = PPM_IN_VALID_TIMEOUT;        
      });
  }
#endif    
}
