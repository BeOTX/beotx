#include "definitions.h"
#include "lz4_fonts.h"

static const uint8_t lz4FontData[] ={
0x15,0x00,0x01,0x00,0x24,0x40,0x02,0x08,0x00,0xf0,0x06,0x02,0x05,0x00,0x00,0x05,
0x00,0xd0,0x02,0x03,0x02,0x00,0x03,0x08,0x00,0x70,0x04,0x05,0x05,0x00,0x00,0x15,
0x08,0x00,0xf3,0x15,0x06,0x00,0xff,0x24,0x00,0x20,0x07,0x07,0x05,0x00,0x00,0x36,
0x00,0x50,0x05,0x06,0x05,0x00,0x00,0x45,0x00,0x80,0x01,0x02,0x02,0x00,0x03,0x47,
0x00,0xb0,0x02,0x03,0x07,0x00,0xfe,0x52,0x08,0x00,0xf0,0x02,0x5d,0x00,0x20,0x03,
0x03,0x03,0x00,0x02,0x62,0x00,0xb0,0x04,0x05,0x04,0x00,0x01,0x6c,0x58,0x00,0x40,
0x02,0x00,0xff,0x6e,0x20,0x00,0x40,0x01,0x00,0x01,0x70,0x10,0x00,0xc3,0x01,0x00,
0x00,0x71,0x00,0x40,0x02,0x03,0x05,0x00,0x00,0x79,0x68,0x00,0x13,0x86,0x08,0x00,
0x13,0x93,0x08,0x00,0x13,0xa0,0x08,0x00,0x13,0xad,0x08,0x00,0x13,0xba,0x08,0x00,
0x13,0xc7,0x08,0x00,0x13,0xd4,0x08,0x00,0x13,0xe1,0x08,0x00,0x13,0xee,0x08,0x00,
0x10,0xfb,0x60,0x00,0x42,0x04,0x00,0x00,0xff,0xd0,0x00,0x41,0xff,0x04,0x01,0xb0,
0x18,0x00,0x10,0x11,0x08,0x00,0x43,0x03,0x00,0x01,0x19,0x10,0x00,0x22,0x26,0x01,
0x30,0x00,0xa2,0x33,0x01,0x20,0x08,0x08,0x06,0x00,0xff,0x4b,0x01,0xd8,0x00,0x40,
0x5a,0x01,0x50,0x05,0x18,0x00,0x31,0x67,0x01,0xc0,0x10,0x00,0x13,0x76,0x08,0x00,
0x13,0x85,0x18,0x00,0x31,0x92,0x01,0xe0,0x38,0x00,0x40,0x9f,0x01,0x40,0x06,0x18,
0x00,0x13,0xae,0x20,0x00,0x22,0xbd,0x01,0x40,0x01,0x93,0xc2,0x01,0x00,0x04,0x04,
0x05,0x00,0x00,0xcc,0x50,0x00,0x13,0xdb,0x68,0x00,0x40,0xe8,0x01,0xb0,0x06,0x40,
0x01,0x13,0xfa,0x30,0x00,0x22,0x09,0x02,0x40,0x00,0x22,0x18,0x02,0x58,0x00,0x10,
0x25,0x10,0x00,0x52,0x07,0x00,0xfe,0x3a,0x02,0x20,0x00,0x13,0x49,0x18,0x00,0x22,
0x56,0x02,0x70,0x00,0x13,0x63,0x18,0x00,0x22,0x72,0x02,0x58,0x00,0x93,0x81,0x02,
0x90,0x07,0x08,0x05,0x00,0x00,0x95,0x10,0x00,0x13,0xa4,0x08,0x00,0x13,0xb3,0x30,
0x00,0x31,0xc0,0x02,0x40,0x90,0x01,0x22,0xcb,0x02,0x68,0x01,0xf1,0x0b,0xd3,0x02,
0x40,0x02,0x02,0x07,0x00,0xfe,0xda,0x02,0xc0,0x03,0x04,0x03,0x00,0x02,0xe0,0x02,
0x70,0x04,0x06,0x01,0xff,0xfe,0xe3,0x02,0x98,0x01,0x40,0x04,0xe5,0x02,0x70,0xb0,
0x01,0x32,0x00,0xef,0x02,0xb0,0x00,0xb1,0xfc,0x02,0x00,0x04,0x04,0x04,0x00,0x00,
0x04,0x03,0x70,0xd0,0x00,0x22,0x0e,0x03,0x20,0x00,0x22,0x18,0x03,0x50,0x00,0x10,
0x20,0x18,0x00,0x43,0x06,0x00,0xfe,0x2c,0x20,0x00,0x40,0x36,0x03,0xc0,0x01,0x00,
0x01,0xb1,0x3b,0x03,0xc0,0x01,0x03,0x07,0xff,0xfe,0x46,0x03,0x00,0x48,0x00,0x13,
0x53,0x18,0x00,0xb1,0x58,0x03,0xb0,0x06,0x07,0x04,0x00,0x00,0x66,0x03,0x70,0x58,
0x00,0x13,0x6e,0x50,0x00,0x21,0x78,0x03,0x60,0x02,0x23,0xfe,0x87,0x50,0x00,0x31,
0x93,0x03,0xb0,0x60,0x00,0x22,0x9b,0x03,0x80,0x00,0x13,0xa3,0x70,0x00,0x13,0xab,
0x38,0x00,0x13,0xb3,0x18,0x00,0x93,0xbb,0x03,0xc0,0x05,0x07,0x04,0xff,0x00,0xc9,
0x10,0x00,0x31,0xd1,0x03,0x00,0x40,0x00,0x13,0xdd,0x10,0x00,0x22,0xe5,0x03,0x90,
0x02,0x31,0xf0,0x03,0x10,0xf8,0x00,0x13,0xf7,0x10,0x00,0xf3,0x02,0x02,0x04,0xb0,
0x04,0x05,0x01,0x00,0x02,0x05,0x04,0x00,0x08,0x08,0x07,0x00,0x00,0x21,0x08,0x00,
0x93,0x3d,0x04,0x00,0x08,0x07,0x07,0x00,0x00,0x56,0x08,0x00,0x13,0x6f,0x18,0x00,
0x93,0x8b,0x04,0x00,0x08,0x06,0x08,0x01,0xff,0xa3,0x10,0x00,0x13,0xbf,0x20,0x00,
0x13,0xd8,0x18,0x00,0x13,0xf0,0x08,0x00,0xa2,0x08,0x05,0x00,0x08,0x06,0x07,0x01,
0x00,0x1d,0x05,0x10,0x00,0x40,0x35,0x05,0x80,0x07,0x10,0x00,0x22,0x4a,0x05,0x38,
0x00,0x13,0x66,0x20,0x00,0x20,0x7b,0x05,0x40,0x00,0x33,0x01,0x00,0x94,0x10,0x00,
0x30,0xa9,0x05,0x30,0x30,0x03,0x33,0x03,0xae,0x05,0x48,0x02,0x13,0x05,0x48,0x02,
0x92,0x05,0x40,0x02,0x03,0x06,0x00,0x00,0xcb,0x05,0xd8,0x01,0x31,0xda,0x05,0x40,
0x10,0x02,0x22,0xe7,0x05,0x18,0x02,0x31,0xf4,0x05,0x50,0x60,0x01,0x40,0x01,0x06,
0x70,0x05,0x38,0x02,0x22,0x16,0x06,0x18,0x00,0x31,0x23,0x06,0x60,0x18,0x02,0x31,
0x37,0x06,0xd0,0x20,0x00,0x22,0x44,0x06,0x58,0x00,0x30,0x53,0x06,0xc0,0x28,0x00,
0x32,0x00,0x68,0x06,0x00,0x03,0x22,0x75,0x06,0x50,0x00,0x22,0x82,0x06,0x98,0x02,
0x13,0x94,0x28,0x00,0x22,0xa3,0x06,0x98,0x02,0x13,0xb2,0x10,0x00,0x13,0xc1,0x58,
0x00,0x13,0xce,0x10,0x00,0x22,0xdd,0x06,0x60,0x02,0x31,0xea,0x06,0x10,0x10,0x00,
0x31,0xf9,0x06,0x10,0x30,0x00,0x22,0x08,0x07,0xa8,0x00,0x31,0x17,0x07,0xf0,0x90,
0x00,0x22,0x2c,0x07,0x38,0x00,0x31,0x39,0x07,0x50,0x38,0x04,0xa2,0x4b,0x07,0x80,
0x07,0x08,0x07,0x00,0xfe,0x67,0x07,0x78,0x00,0x40,0x74,0x07,0x10,0x08,0xa8,0x00,
0x22,0x88,0x07,0x58,0x00,0x22,0x97,0x07,0x10,0x02,0x30,0xa1,0x07,0x90,0x10,0x02,
0x41,0x00,0xb0,0x07,0x40,0xc8,0x01,0xb1,0xb8,0x07,0xf0,0x02,0x03,0x04,0x00,0x00,
0xbe,0x07,0xb0,0x28,0x02,0x13,0xcd,0x28,0x00,0xc0,0xd7,0x07,0x60,0x05,0x06,0x04,
0x00,0x00,0xe3,0x07,0xb0,0x03,0x28,0x00,0x31,0xeb,0x07,0x80,0x30,0x00,0x30,0xf3,
0x07,0x80,0x08,0x02,0x41,0x00,0xff,0x07,0x80,0x18,0x00,0x31,0x07,0x08,0xb0,0x30,
0x00,0x40,0x11,0x08,0x80,0x05,0x08,0x00,0x22,0x1b,0x08,0x48,0x02,0x22,0x23,0x08,
0x48,0x00,0x31,0x2d,0x08,0x50,0x10,0x00,0x22,0x35,0x08,0x88,0x02,0x22,0x44,0x08,
0x40,0x02,0x22,0x4c,0x08,0x58,0x00,0x22,0x54,0x08,0x58,0x02,0x93,0x60,0x08,0x90,
0x06,0x07,0x07,0x00,0xfe,0x79,0x20,0x00,0x31,0x81,0x08,0x90,0x30,0x00,0x31,0x90,
0x08,0x30,0x10,0x00,0x40,0x98,0x08,0x70,0x06,0x90,0x00,0x10,0xa4,0x28,0x00,0x43,
0x06,0x00,0xfe,0xb9,0x18,0x00,0x31,0xc1,0x08,0x00,0x18,0x00,0x13,0xcd,0x68,0x00,
0x31,0xd5,0x08,0x10,0x08,0x00,0xf1,0x0c,0xdd,0x08,0xc0,0x01,0x02,0x06,0x00,0x00,
0xe3,0x08,0x40,0x02,0x04,0x05,0xff,0x00,0xed,0x08,0xd0,0x02,0x03,0x03,0x00,0x01,
0xf2,0x08,0x60,0x60,0x01,0xb0,0xff,0x08,0x00,0x08,0x08,0x09,0x00,0xff,0x23,0x09,
0x00,0xa0,0x04,0x20,0x00,0x3b,0x08,0x00,0x43,0x08,0x00,0xff,0x5b,0x10,0x00,0x93,
0x73,0x09,0x80,0x05,0x06,0x06,0x00,0x00,0x85,0x18,0x00,0x13,0xa5,0x08,0x00,0x93,
0xc5,0x09,0x00,0x09,0x09,0x08,0x00,0xff,0xe9,0x10,0x00,0xf0,0x0c,0x09,0x0a,0x00,
0x09,0x09,0x06,0x00,0x00,0x24,0x0a,0x00,0x08,0x08,0x0a,0x00,0xfe,0x4c,0x0a,0x00,
0x04,0x04,0x07,0x00,0xff,0x5a,0x0a,0x00,0x70,0x04,0x32,0xff,0x6f,0x0a,0x30,0x00,
0x22,0x93,0x0a,0x58,0x00,0xf0,0x0a,0xab,0x0a,0x80,0x05,0x06,0x08,0x00,0xff,0xc3,
0x0a,0x00,0x07,0x05,0x08,0x01,0xff,0xd7,0x0a,0x00,0x07,0x07,0x0a,0x00,0xfe,0xfa,
0x08,0x00,0x52,0x08,0x00,0xff,0x16,0x0b,0x08,0x00,0x22,0x32,0x0b,0x20,0x00,0xf3,
0x02,0x46,0x0b,0x00,0x07,0x09,0x08,0xff,0xff,0x6a,0x0b,0x00,0x05,0x05,0x08,0x00,
0xff,0x7e,0x08,0x00,0x13,0x92,0x28,0x00,0x10,0xae,0x08,0x00,0x52,0x02,0x00,0x02,
0xb5,0x0b,0x88,0x00,0xc0,0xd0,0x0b,0x00,0x0a,0x0b,0x08,0xff,0xff,0xfc,0x0b,0x00,
0x09,0x08,0x00,0x22,0x28,0x0c,0xa8,0x00,0x93,0x48,0x0c,0x00,0x07,0x07,0x06,0x00,
0x00,0x5d,0x08,0x00,0xa2,0x72,0x0c,0x00,0x0a,0x0b,0x07,0xff,0xff,0x99,0x0c,0x98,
0x00,0x13,0xb1,0x28,0x00,0xc0,0xd1,0x0c,0x00,0x08,0x09,0x09,0xff,0xff,0xfa,0x0c,
0x00,0x07,0x10,0x00,0x22,0x1a,0x0d,0x68,0x00,0x13,0x36,0x08,0x00,0x13,0x52,0x08,
0x00,0x22,0x6e,0x0d,0x38,0x00,0x93,0x86,0x0d,0x00,0x05,0x07,0x08,0xff,0xff,0xa2,
0x18,0x00,0x13,0xbe,0x08,0x00,0x22,0xda,0x0d,0x90,0x00,0xc0,0xf5,0x0d,0x00,0x08,
0x0a,0x0a,0xff,0xfe,0x27,0x0e,0x00,0x06,0xf8,0x00,0x90,0x3f,0x0e,0x00,0x0a,0x0a,
0x08,0x00,0xff,0x67,0x08,0x00,0x00,0x60,0x01,0x03,0x08,0x00,0x13,0xa3,0x08,0x00,
0x13,0xc1,0x08,0x00,0x13,0xdf,0x08,0x00,0x20,0xfd,0x0e,0xd0,0x00,0x42,0x00,0xff,
0x29,0x0f,0x58,0x00,0x13,0x45,0x08,0x00,0x21,0x61,0x0f,0xa8,0x00,0x32,0xfe,0x8a,
0x0f,0x28,0x00,0x40,0xa8,0x0f,0x00,0x06,0x18,0x00,0x60,0xc4,0x0f,0x10,0x08,0x09,
0x06,0x70,0x07,0xf0,0xff,0x21,0x54,0x03,0x56,0x03,0x57,0x03,0x00,0x00,0x02,0x00,
0x03,0x00,0x08,0x00,0x0a,0x00,0x0b,0x00,0xd6,0x1b,0x19,0x1e,0xb5,0xeb,0xbc,0xeb,
0xbf,0xeb,0xc0,0xeb,0xc1,0xeb,0xc5,0xeb,0xc7,0xeb,0xc9,0xeb,0xcd,0xeb,0xd0,0xeb,
0xd5,0xeb,0xda,0xeb,0xdb,0xeb,0xdc,0xeb,0xf2,0xeb,0xf7,0xeb,0xfc,0xeb,0xff,0xeb,
0x00,0xec,0x01,0xec,0x05,0xec,0x06,0xec,0x07,0xec,0x08,0xec,0x1b,0xec,0x1c,0xec,
0x22,0xec,0x24,0xec,0x25,0xec,0x28,0xec,0x2b,0xec,0x2c,0xec,0x2d,0xec,0x2f,0xec,
0x47,0xec,0x49,0xec,0x78,0xec,0x79,0xec,0x7b,0xec,0x7d,0xec,0x94,0xec,0x9b,0xec,
0x9e,0xec,0xa7,0xec,0xd0,0xec,0xd8,0xec,0x0f,0xed,0x9f,0xed,0xf4,0xed,0xf5,0xed,
0xf6,0xed,0xf7,0xed,0xf8,0xed,0x3b,0xee,0x47,0xee,0xa1,0xee,0xb8,0xee,0x0e,0xf1,
0x76,0xf3,0x56,0xf4,0x47,0x37,0x36,0x14,0x35,0xa3,0x75,0x14,0x06,0x07,0x04,0xa6,
0xa2,0x06,0x15,0x07,0x88,0x71,0x50,0x60,0x00,0x59,0xca,0x09,0x37,0x20,0x07,0xc8,
0x04,0x07,0x74,0x69,0xca,0x10,0x03,0x00,0x67,0x70,0x44,0x09,0x09,0x1a,0x74,0x37,
0x49,0x90,0x90,0x06,0x29,0x09,0x03,0x60,0x46,0x60,0x06,0x89,0x00,0x09,0x39,0x00,
0x2a,0xa0,0x50,0xa0,0x78,0x50,0x59,0x8a,0x81,0x91,0x50,0x07,0x31,0x90,0x65,0x07,
0x30,0x65,0x01,0x90,0x07,0x40,0x82,0x00,0xa0,0x0a,0x00,0x82,0x0a,0x00,0xa0,0x82,
0x00,0x27,0x24,0xd5,0x32,0x30,0x00,0x50,0x00,0x09,0x00,0x58,0xc8,0x20,0x09,0x00,
0x36,0x15,0x59,0x20,0x36,0x08,0x10,0x90,0x36,0x08,0x10,0xa0,0x00,0x2a,0x97,0x08,
0x20,0xb0,0xa0,0x09,0x18,0x20,0xa0,0x2a,0x96,0x00,0x08,0xb0,0x01,0x0b,0x00,0x00,
0xb0,0x00,0x0b,0x00,0x38,0xd8,0x00,0x2a,0x98,0x02,0x10,0xb0,0x00,0x75,0x00,0x93,
0x00,0x7b,0x88,0x00,0x3a,0x0d,0x00,0xf0,0xd9,0x03,0xb7,0x03,0x00,0xb0,0x4a,0x99,
0x00,0x00,0xa7,0x00,0x77,0x70,0x36,0x37,0x09,0x89,0xb1,0x00,0x37,0x00,0x5b,0x97,
0x07,0xa8,0x40,0x10,0x0b,0x03,0x10,0xb0,0x3a,0x97,0x00,0x09,0x86,0x06,0x88,0x50,
0x94,0x0b,0x07,0x40,0xa0,0x1a,0x97,0x00,0x59,0x9d,0x00,0x04,0x60,0x00,0xa0,0x00,
0x46,0x00,0x08,0x30,0x00,0x29,0x88,0x06,0x40,0xb0,0x1c,0xa7,0x09,0x20,0xa0,0x49,
0x89,0x00,0x3a,0x86,0x08,0x20,0xb0,0x19,0x7c,0x02,0x10,0xc0,0x2b,0x95,0x00,0x36,
0x00,0x00,0x36,0x36,0x00,0x00,0x35,0x15,0x00,0x00,0x10,0x38,0x81,0x88,0x00,0x00,
0x59,0x60,0x00,0x02,0x10,0x58,0x88,0x20,0x00,0x00,0x58,0x88,0x20,0x20,0x00,0x03,
0x87,0x10,0x00,0x1c,0x32,0x88,0x30,0x30,0x00,0x00,0x3b,0xa9,0x04,0x10,0xa1,0x00,
0x67,0x00,0x16,0x00,0x03,0x50,0x00,0x00,0x77,0x77,0x50,0x09,0x39,0x8b,0x63,0x45,
0xa0,0x0a,0x26,0x53,0xa0,0x57,0x53,0x19,0x57,0x38,0x60,0x01,0x77,0x76,0x00,0x00,
0xe5,0x00,0x06,0x6b,0x00,0x0c,0x09,0x30,0x4c,0x89,0xa0,0xb1,0x00,0xa1,0x5b,0x9a,
0x45,0x60,0x38,0x5b,0x8b,0x35,0x60,0x0c,0x5b,0x89,0x70,0x09,0x9a,0x90,0x67,0x00,
0x31,0x93,0x00,0x00,0x67,0x00,0x32,0x08,0xa9,0x90,0x5b,0x99,0x50,0x56,0x00,0xa2,
0x56,0x00,0x65,0x56,0x00,0xa2,0x5b,0x8a,0x60,0x5b,0x99,0x75,0x60,0x00,0x5b,0x99,
0x55,0x05,0x00,0x13,0x90,0x08,0x00,0xf1,0x06,0x45,0x60,0x00,0x56,0x00,0x00,0x08,
0x99,0xa1,0x56,0x00,0x11,0x83,0x06,0x97,0x67,0x00,0x1a,0x08,0x98,0x92,0x35,0x00,
0x42,0xa2,0x5c,0x99,0xd2,0x09,0x00,0x10,0x47,0x01,0x00,0xf0,0x0d,0x03,0xb6,0x00,
0x56,0x00,0x56,0x40,0x56,0x6a,0xb1,0x56,0x07,0x60,0x56,0x85,0x00,0x5c,0xb1,0x00,
0x56,0x2b,0x00,0x56,0x03,0xa0,0x56,0x00,0x05,0x44,0x00,0x10,0x05,0x4e,0x00,0xf0,
0x22,0x10,0x5d,0x00,0x2f,0x05,0xb4,0x08,0xb0,0x55,0xa0,0x9a,0x05,0x58,0x83,0xa0,
0x55,0x2c,0x0a,0x00,0x5d,0x00,0x82,0x58,0x80,0x82,0x55,0x74,0x82,0x55,0x0a,0x92,
0x55,0x02,0xe2,0x09,0x99,0xa1,0x66,0x00,0x3a,0x93,0x00,0x0c,0x67,0x00,0x39,0x08,
0xa9,0xa1,0x93,0x00,0x32,0x0b,0x5b,0x88,0x86,0x00,0x07,0x1c,0x00,0xd0,0x2a,0x09,
0x99,0x90,0x00,0x0b,0x00,0x00,0x07,0x91,0x5b,0x99,0xa0,0xbe,0x00,0xf2,0x09,0x8b,
0x60,0x56,0x06,0x60,0x56,0x00,0xb1,0x1a,0x89,0x64,0x80,0x02,0x05,0x99,0x42,0x10,
0x0c,0x3a,0x89,0x70,0x79,0xe9,0x60,0xd0,0x01,0x00,0x05,0x00,0x32,0x65,0x00,0x92,
0x03,0x00,0xf0,0x02,0x57,0x00,0xb1,0x08,0x89,0x60,0xb1,0x00,0xa1,0x47,0x02,0x90,
0x0b,0x08,0x20,0x06,0x6a,0xcf,0x09,0xf0,0x1f,0xb0,0x0b,0x40,0x65,0x74,0x09,0x90,
0xa1,0x29,0x54,0xa0,0xa0,0x0b,0x90,0x68,0x60,0x08,0xa0,0x2f,0x10,0x48,0x03,0x90,
0x07,0x6a,0x00,0x00,0xd5,0x00,0x09,0x2a,0x10,0x66,0x01,0xa0,0x75,0x01,0xb0,0x0a,
0x1a,0x20,0x01,0xd5,0x00,0x00,0xb0,0x03,0x00,0xf0,0x03,0x49,0x9d,0x50,0x03,0x90,
0x02,0xa0,0x01,0xa1,0x00,0xab,0x99,0x50,0x69,0x16,0x40,0x64,0x06,0x03,0x00,0xc0,
0x69,0x10,0xa0,0x08,0x10,0x36,0x00,0x90,0x08,0x10,0x7a,0x0a,0x01,0x00,0xf0,0x38,
0x7a,0x05,0x30,0x17,0x90,0x90,0x36,0x07,0x77,0x74,0x27,0x00,0x39,0x87,0x02,0x87,
0xc0,0x92,0x0c,0x05,0x97,0xa3,0x74,0x00,0x07,0x98,0x90,0x75,0x0a,0x07,0x40,0xa0,
0x79,0x79,0x00,0x29,0x95,0x92,0x02,0x92,0x02,0x2a,0x95,0x00,0x0b,0x3a,0x7c,0x92,
0x0c,0x92,0x0c,0x3a,0x7c,0x29,0x88,0x09,0x88,0xa0,0x93,0x01,0x02,0xa8,0x80,0x2a,
0x19,0xa1,0x46,0x04,0x60,0x46,0x00,0x1a,0x00,0xe0,0x91,0x0c,0x4a,0x7c,0x11,0x0b,
0x2a,0x96,0x74,0x00,0x79,0x89,0x74,0x0b,0x02,0x00,0xa0,0x42,0x73,0x73,0x73,0x73,
0x04,0x20,0x73,0x07,0x30,0x03,0x00,0xf0,0x01,0x1b,0x10,0x74,0x00,0x07,0x46,0x60,
0x79,0x70,0x07,0x8a,0x00,0x74,0x39,0x00,0x74,0x01,0x00,0xf2,0x01,0x78,0x89,0x6b,
0x07,0x40,0xb0,0x92,0x74,0x0b,0x09,0x27,0x40,0xb0,0x92,0x78,0x79,0x38,0x00,0xf4,
0x0a,0x29,0x88,0x09,0x20,0xa0,0x92,0x0b,0x02,0x98,0x70,0x78,0x79,0x07,0x40,0xa0,
0x75,0x0a,0x07,0x97,0x90,0x73,0x00,0x07,0x40,0x00,0x81,0x00,0xf2,0x53,0x00,0x0b,
0x00,0x0b,0x00,0x07,0x94,0x75,0x07,0x40,0x74,0x00,0x59,0x95,0x69,0x30,0x01,0x69,
0x68,0x86,0x45,0x09,0xa0,0x65,0x06,0x50,0x3a,0x10,0x73,0x0b,0x73,0x0b,0x73,0x0c,
0x3a,0x7b,0xb0,0x0b,0x64,0x56,0x09,0xa0,0x09,0x80,0x0a,0x09,0x60,0x90,0x91,0x88,
0x45,0x04,0x86,0x89,0x10,0x0e,0x15,0xb0,0x74,0x47,0x09,0x90,0x0a,0xa0,0x83,0x38,
0xb0,0x0b,0x65,0x46,0x0a,0x91,0x09,0x90,0x06,0x40,0x69,0x00,0x48,0xc6,0x02,0xa0,
0x0b,0x10,0x9a,0x84,0x0b,0x40,0xa0,0x19,0x0a,0x40,0x19,0x00,0xa0,0x0b,0x40,0x45,
0x01,0x00,0x10,0x77,0xa5,0x03,0x61,0x95,0x0a,0x00,0xa0,0x77,0x00,0xf1,0x02,0xf0,
0x06,0x20,0x00,0x00,0x00,0xc9,0x00,0x1b,0xaa,0xa5,0x90,0x18,0x00,0x00,0x86,0x1d,
0xaa,0x93,0xa0,0x00,0x00,0xba,0x1d,0x0c,0x20,0x00,0x00,0x27,0x0c,0xf0,0x24,0x4f,
0x00,0x00,0x04,0x98,0xaa,0xa6,0x0c,0x00,0x00,0x18,0x05,0x76,0xaa,0xb8,0x00,0x6e,
0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x07,0x20,0x00,0x08,0x7b,0x10,0x08,0x60,0x1b,
0x11,0xad,0x08,0xb5,0x00,0xa0,0x91,0x00,0x0a,0x09,0x10,0x00,0xaa,0xd1,0x00,0x00,
0x6a,0xa0,0x0b,0x00,0x00,0x12,0x00,0xf1,0x4e,0x8d,0x08,0x94,0x0a,0x60,0x1c,0x30,
0x0b,0x3a,0x30,0x00,0x0c,0x50,0x00,0x00,0x01,0x20,0x00,0x00,0x08,0x80,0x00,0x00,
0x26,0x43,0x00,0x00,0x80,0x08,0x00,0x02,0x60,0x04,0x40,0x08,0x00,0x00,0x80,0x2b,
0x77,0x77,0xa4,0x00,0x02,0x73,0x03,0x6b,0x07,0x44,0x0c,0xa8,0x70,0x48,0x67,0x60,
0x73,0x06,0x70,0x00,0x07,0x27,0x11,0x71,0x01,0x55,0x00,0x00,0x14,0x41,0x00,0x03,
0x5c,0xd9,0x10,0x0a,0x11,0x33,0x80,0x0a,0x00,0x00,0x91,0x0a,0x00,0x02,0xa0,0x06,
0x93,0x4a,0x40,0x00,0x37,0x72,0xb9,0x00,0x90,0x8a,0xb6,0x70,0x0a,0x17,0x21,0x70,
0x76,0x60,0x40,0x06,0xf0,0x56,0x70,0x44,0x00,0x36,0x00,0x46,0x65,0x00,0x00,0x76,
0x66,0x02,0x40,0x16,0x07,0x00,0x70,0x1b,0x5a,0x30,0x70,0x97,0x50,0x73,0x60,0x60,
0x54,0x07,0x20,0x03,0x61,0x00,0x00,0x65,0x00,0x00,0x55,0x00,0x55,0xba,0x80,0x51,
0x55,0x50,0x51,0x55,0x50,0x50,0x00,0x50,0x15,0xed,0x40,0x00,0x88,0x00,0x00,0x29,
0xa5,0xb6,0xe5,0x32,0x67,0xb0,0x00,0x60,0x56,0x00,0x7a,0x70,0x00,0xb6,0xd3,0x11,
0x00,0x4b,0xc6,0x6b,0xa6,0x65,0x67,0x53,0xaa,0x68,0x68,0xeb,0x64,0x30,0x06,0x6a,
0x70,0x06,0x65,0x30,0x06,0x8d,0xb5,0x58,0x11,0x11,0x10,0xfa,0x00,0xf0,0x1e,0xfd,
0x70,0x70,0x66,0x16,0x72,0x69,0x17,0xbb,0x59,0x9a,0xc9,0x00,0xb5,0x03,0x67,0x20,
0x00,0x64,0x00,0x00,0x0c,0xff,0x40,0x00,0x0f,0xff,0xaf,0xd0,0x05,0xff,0x9f,0xf0,
0x07,0x6c,0xff,0x90,0x09,0x6f,0xff,0xf0,0x0a,0xba,0xaa,0xa0,0xf8,0x05,0xf2,0x27,
0x64,0x00,0x33,0x3a,0x50,0x9a,0xaa,0xa2,0x3e,0xee,0xec,0x02,0x90,0x00,0x00,0x25,
0x00,0x00,0x35,0x10,0x00,0x03,0x77,0x70,0x00,0x37,0x73,0x00,0x44,0x84,0x00,0x96,
0x73,0xc0,0x0b,0x5b,0x3d,0x00,0x07,0x57,0x20,0x00,0x46,0x67,0x10,0x60,0x06,0x81,
0x60,0x07,0x47,0x60,0x00,0x06,0x03,0x00,0xf3,0x01,0x76,0x66,0x67,0x16,0x36,0x07,
0x17,0x30,0x09,0x9a,0xa0,0x67,0x00,0x31,0x9a,0x96,0x47,0x04,0x01,0x00,0x04,0x50,
0x64,0x24,0x70,0x47,0x04,0x03,0x00,0x0c,0x80,0x04,0x20,0x99,0x25,0xfa,0x03,0x69,
0x35,0x60,0x0b,0x5b,0x89,0x50,0x8d,0x04,0x32,0x5b,0x99,0x15,0x19,0x04,0x00,0xdc,
0x03,0xf9,0x06,0x04,0xba,0x90,0x07,0x42,0x90,0x09,0x12,0x90,0x0b,0x02,0x90,0xad,
0x9a,0xd2,0xb0,0x00,0x74,0xb0,0x00,0x74,0x91,0x04,0xfb,0x27,0x56,0x0a,0x11,0xa0,
0x08,0x3a,0x1a,0x10,0x02,0xcd,0xa8,0x00,0x0b,0x1a,0x19,0x30,0x85,0x0a,0x10,0xb0,
0x2a,0x9a,0x02,0x10,0x83,0x01,0x9b,0x03,0x00,0x65,0x3b,0x9a,0x10,0x55,0x02,0xf1,
0x55,0x0a,0xa1,0x55,0x74,0x91,0x58,0x90,0x91,0x5d,0x00,0x91,0x03,0x13,0x20,0x02,
0x88,0x00,0x15,0x00,0xfe,0x0b,0x56,0x0a,0x25,0x67,0x50,0x5b,0xc0,0x05,0x64,0x80,
0x56,0x09,0x40,0x07,0xaa,0x90,0x91,0x29,0x0b,0x02,0x90,0xb0,0x29,0xa5,0x02,0x90,
0x9a,0x04,0x0b,0xe6,0x04,0x0b,0x9a,0x04,0x05,0x18,0x00,0x02,0x03,0x00,0x0a,0xa9,
0x04,0x0a,0x67,0x05,0x09,0x87,0x04,0xfb,0x0f,0x76,0x00,0xb0,0x0b,0x17,0x30,0x02,
0xa9,0x00,0x00,0xa1,0x00,0x59,0x50,0x00,0x08,0xab,0x80,0x65,0x56,0x48,0x65,0x56,
0x47,0x07,0xab,0x70,0x00,0x56,0x00,0x73,0x04,0x35,0x56,0x00,0xa1,0x03,0x00,0x40,
0x5b,0x99,0xd7,0x00,0x43,0x00,0xf3,0x06,0x0b,0x66,0x01,0xb6,0x60,0x1b,0x56,0x01,
0xb0,0x98,0x9b,0x00,0x01,0xb0,0x56,0x0b,0x00,0xa5,0x60,0xb0,0x0a,0x07,0x00,0x88,
0x5b,0x9d,0x99,0xa0,0x56,0x0b,0x03,0x80,0x04,0x00,0x80,0x5b,0x9e,0x9a,0xc1,0x00,
0x00,0x00,0x83,0x04,0x00,0x03,0x87,0x05,0x02,0x8d,0x01,0xf1,0x06,0x56,0x07,0x88,
0x90,0x56,0x38,0x00,0x48,0x5c,0xc5,0x00,0x1a,0x56,0x49,0x00,0x57,0x56,0x07,0xa9,
0x90,0x1a,0xd6,0x00,0x96,0x08,0xb8,0xd2,0x09,0x30,0xa2,0x48,0x00,0xa2,0xb2,0x04,
0xf6,0x1d,0x00,0x36,0x00,0x95,0x30,0x66,0x77,0x08,0x50,0x92,0x64,0x08,0x31,0x97,
0x90,0x7a,0x88,0x79,0x96,0x74,0x0c,0x79,0x87,0x79,0x57,0x40,0x74,0x07,0x40,0x0a,
0x7d,0x00,0xb0,0xb0,0x0a,0x0b,0x09,0xa7,0xd3,0xa0,0x01,0x8a,0x00,0x18,0xbf,0x04,
0xf4,0x11,0x91,0xa0,0xa1,0x28,0xa4,0x70,0x0b,0xdb,0x20,0x83,0xa1,0xa1,0x48,0xa2,
0x05,0xb0,0x10,0x75,0x69,0xa1,0x73,0x2e,0x73,0x9b,0x79,0x3a,0x79,0x0a,0x14,0x04,
0x07,0x83,0x0c,0x00,0xfa,0x11,0x74,0x73,0x75,0x90,0x7b,0x60,0x74,0x92,0x0b,0x7c,
0x10,0xb0,0x91,0x19,0x09,0x19,0x30,0x91,0x7c,0x04,0xe7,0xa2,0x8b,0x75,0x88,0xa7,
0x3a,0x4a,0x74,0x0b,0x79,0x7c,0xb5,0x04,0x22,0x79,0x7b,0xc7,0x04,0x0b,0xbd,0x04,
0x04,0x48,0x05,0x40,0x6b,0x93,0x08,0x30,0x02,0x00,0x08,0x83,0x04,0xf0,0x05,0x00,
0x0a,0x00,0x03,0xa7,0xc7,0xa0,0x92,0x1a,0x08,0x39,0x21,0xa0,0x83,0x4a,0x7c,0x7a,
0x00,0x00,0x90,0x15,0x00,0x14,0x00,0xb0,0x04,0xf2,0x0b,0x74,0x0b,0x07,0x40,0xb0,
0x74,0x0b,0x07,0x97,0xd3,0x00,0x03,0x60,0x00,0x36,0x83,0x19,0x83,0x19,0x39,0x79,
0x00,0x19,0x74,0x29,0x0b,0x03,0x00,0xa0,0x79,0x8c,0x7c,0x74,0x28,0x0b,0x07,0x42,
0x80,0xb0,0x07,0x00,0x40,0x98,0xc7,0xd3,0x00,0x28,0x00,0x60,0x00,0x36,0x74,0x00,
0x79,0x74,0x09,0x01,0xf0,0x0f,0x74,0x78,0x83,0x79,0xd0,0x29,0x74,0xa0,0x29,0x74,
0x48,0x92,0x4a,0x7b,0x74,0x0b,0x1b,0x7b,0x65,0x0b,0x28,0x86,0x98,0x50,0x93,0x05,
0x2a,0x95,0x42,0x00,0xa8,0x05,0x42,0x06,0x51,0x03,0x70,0x02,0x00,0xf3,0x02,0x00,
0x07,0xf4,0x6e,0x30,0x74,0x00,0x00,0x59,0x70,0x01,0x6a,0x07,0x82,0x00,0x79,0x99,
0x0b,0x11,0xf0,0x01,0x26,0xbe,0x00,0x8d,0xff,0xff,0x00,0xff,0xe9,0x5f,0x00,0xf3,
0x00,0x0f,0x00,0xf0,0x04,0x00,0xf0,0x07,0x0a,0xff,0xaf,0xf0,0x0a,0xfa,0xaf,0xa0,
0x00,0x00,0xbd,0xcc,0xce,0xab,0x8b,0x00,0x07,0x58,0xcd,0x66,0x6a,0xac,0x04,0x00,
0x00,0x0c,0x00,0x00,0x14,0x00,0xf0,0x01,0x34,0x14,0x44,0x43,0xff,0x7f,0xff,0xff,
0xab,0x4b,0xbb,0xba,0xbc,0x5c,0xcc,0xcb,0x0c,0x00,0x43,0x67,0x17,0x88,0x86,0x14,
0x00,0x00,0x3f,0x05,0xf0,0x48,0x9a,0x00,0x00,0x09,0xfa,0xa9,0x00,0x9f,0xa0,0xaf,
0x99,0xfa,0x00,0x0a,0xff,0xa0,0x00,0x00,0x99,0x00,0x00,0x63,0x00,0x82,0xcf,0x4a,
0xf4,0x1d,0xff,0x60,0x0a,0xff,0x30,0xaf,0x7d,0xf3,0xa6,0x01,0xb3,0x00,0x0c,0x51,
0x00,0x1d,0x7d,0x6e,0x70,0x8d,0x0d,0x65,0xf1,0xc7,0x0d,0x60,0xe6,0xd7,0x06,0x20,
0xe6,0x9d,0x00,0x04,0xf2,0x1e,0xc7,0x8f,0x80,0x01,0x9d,0xc6,0x00,0x00,0x0c,0xc0,
0x00,0x18,0x8f,0xf8,0x81,0x8f,0xfe,0xef,0xf8,0x2f,0xe0,0x0e,0xf2,0x04,0x00,0x00,
0x0c,0x00,0x00,0x14,0x00,0x00,0x1c,0x00,0xf4,0x19,0x00,0x00,0x30,0x22,0x00,0x00,
0xaf,0xaa,0xa0,0x01,0xda,0x6a,0xfa,0x03,0xe8,0xbf,0xb8,0xe3,0xb6,0xdf,0xff,0xd6,
0xb0,0x8f,0xfb,0xff,0x80,0x08,0xfc,0x0c,0xf8,0x00,0x5b,0x80,0x8b,0x50,0x00,0x0f,
0xf0,0x00,0x04,0x00,0xf0,0x17,0x07,0xff,0xff,0x70,0x00,0x9f,0xf9,0x00,0x78,0x7a,
0xa7,0x87,0xff,0xfb,0xbf,0xff,0xff,0xff,0xfb,0xbf,0x05,0xff,0xff,0xf5,0x01,0xe3,
0x00,0x03,0xe1,0xa8,0x00,0x00,0x08,0xaf,0xff,0x60,0x6f,0xff,0x01,0x00,0x10,0xfd,
0x04,0x00,0xf0,0x16,0x00,0x00,0x00,0x03,0x02,0xbf,0xfb,0x3f,0x2e,0x91,0x18,0xff,
0x9a,0x00,0x6c,0xff,0x31,0x00,0x24,0x44,0x44,0x42,0x00,0x13,0xff,0xc6,0x00,0xb9,
0xfe,0xa5,0x5b,0xd1,0xf2,0x8c,0xc8,0x10,0x30,0x48,0x01,0x30,0x09,0x34,0xcf,0x35,
0x00,0xf0,0x06,0xab,0xff,0x00,0x4f,0x00,0x01,0x00,0x09,0x00,0x34,0xcf,0x01,0xff,
0xff,0x1b,0xff,0xff,0x1b,0xbb,0xff,0x01,0x44,0x06,0x11,0x01,0x00,0x0b,0xf2,0x1f,
0x00,0x00,0x90,0x23,0xb3,0x34,0xcf,0x02,0xc3,0xbf,0xff,0xf1,0xb5,0x6c,0xff,0xff,
0x1b,0x56,0xca,0xbf,0xf0,0x2c,0x3a,0x00,0x4f,0x02,0x3b,0x30,0x00,0x10,0x05,0x40,
0xdf,0xff,0xff,0xfd,0xf0,0x7f,0xff,0xff,0xf8,0xcf,0xb1,0xbf,0xfb,0x5b,0xb4,0x00,
0x10,0xdf,0x87,0x00,0xf1,0x10,0xb4,0x00,0x03,0xfb,0x00,0x0b,0xff,0x40,0x6f,0xff,
0xd0,0xdf,0xff,0xf5,0xf8,0xff,0xf7,0xaa,0x8f,0xf2,0x1a,0xfd,0x40,0x40,0x00,0x2f,
0x20,0x8f,0xf2,0x9f,0xff,0x7c,0x00,0xf1,0x16,0x5e,0xff,0xf2,0x2e,0xfb,0x10,0x19,
0x00,0x00,0x00,0x0d,0xa1,0x00,0x00,0xff,0xf7,0x00,0x0f,0xff,0xfd,0x40,0xff,0xff,
0xff,0xaf,0xff,0xff,0xfa,0xff,0xff,0xd4,0x0f,0xff,0x70,0x00,0xda,0x10,0xf5,0x01,
0xb9,0x9b,0x90,0x9b,0x9f,0xff,0x0f,0xff,0xff,0xf0,0xff,0xff,0x07,0x00,0xae,0xf2,
0x42,0x02,0x42,0x24,0x44,0x44,0x2f,0xff,0xff,0x01,0x00,0xc1,0xf8,0xbb,0xbb,0xb8,
0x20,0x00,0x4f,0x80,0x2f,0xff,0x92,0xff,0x70,0x00,0x72,0xfe,0x5f,0xfd,0x22,0xf9,
0x10,0x1b,0x41,0x07,0xf1,0x36,0x8f,0x80,0x00,0x00,0x7f,0xff,0x70,0x00,0x5f,0xff,
0xff,0x50,0x0e,0xff,0xff,0xfe,0x00,0x58,0x88,0x88,0x50,0x0f,0xff,0xff,0xff,0x00,
0xab,0xbb,0xbb,0xa0,0x00,0x06,0x20,0x07,0xf4,0x07,0xf5,0x05,0xf6,0x00,0x1e,0xb0,
0x00,0x2e,0xb0,0x00,0x2e,0x60,0x00,0x10,0x26,0x00,0x04,0xf7,0x00,0x05,0xf7,0x00,
0x06,0xf5,0x00,0xbe,0x10,0xbe,0x20,0x6e,0x20,0x00,0x10,0x59,0x07,0xf0,0x01,0x03,
0xf3,0x00,0x00,0x4f,0x40,0x07,0x8a,0xfa,0x87,0xef,0xff,0xff,0xe0,0x04,0xf4,0x0e,
0x00,0x80,0x00,0x01,0xb1,0x00,0x78,0x88,0x88,0x7e,0x59,0x00,0xf1,0x0c,0x8c,0xcc,
0x80,0x01,0xdd,0x16,0x3d,0xd1,0xcf,0x55,0xed,0x5f,0xcb,0xf5,0xdf,0xd5,0xfc,0x1d,
0xd3,0x73,0xdd,0x10,0x08,0xdc,0xc8,0x10,0x1d,0x89,0x01,0xf1,0x11,0x5e,0x8c,0xcc,
0xa2,0x00,0x00,0x2d,0xb4,0x49,0xf4,0x00,0x7a,0x1a,0xff,0x3f,0xe1,0x07,0xfa,0x06,
0xf7,0xff,0x10,0x0a,0xf3,0x03,0xef,0x40,0x00,0x06,0xcc,0x71,0xbb,0x02,0x01,0x40,
0x89,0x00,0x00,0x3e,0x2e,0x00,0xf0,0x2e,0x0c,0xfc,0x00,0x00,0x00,0x06,0xfc,0xf6,
0x00,0x00,0x00,0xed,0x0d,0xe0,0x00,0x00,0x8f,0xe0,0xef,0x80,0x00,0x2f,0xff,0x6f,
0xff,0x20,0x0b,0xff,0xe2,0xef,0xfa,0x00,0xdf,0xff,0xff,0xff,0xd0,0x00,0x00,0x00,
0x20,0x44,0x00,0x04,0xf5,0xef,0xb1,0xcf,0xfd,0x01,0x8c,0xd1,0xc1,0x01,0xdc,0x81,
0xc1,0xef,0xc1,0xbf,0xfd,0x14,0x00,0x12,0x00,0xff,0x00,0xf2,0x00,0x00,0x04,0xe4,
0x00,0x04,0xfc,0xf4,0x04,0xf8,0x08,0xf4,0xb8,0x00,0x08,0xb0,0x5b,0x03,0xe1,0x0b,
0x80,0x00,0x8b,0x4f,0x80,0x8f,0x40,0x4f,0xcf,0x40,0x00,0x4e,0x40,0x13,0x00,0xf1,
0x12,0x94,0x14,0x44,0x40,0x00,0xbf,0xf8,0xbb,0xbf,0x10,0x08,0xb7,0x60,0x00,0xe1,
0x00,0x0b,0x40,0x00,0x1e,0x20,0x00,0xb7,0x44,0x5e,0xfd,0x50,0x07,0xbb,0xb8,0x5f,
0x80,0x00,0x50,0x00,0x43,0xdf,0xfb,0x00,0x00,0x81,0x02,0x05,0x01,0x00,0x01,0x06,
0x02,0x30,0x09,0x90,0x00,0xbc,0x02,0x01,0xc4,0x02,0x03,0xd0,0x02,0x71,0x78,0x4f,
0xf4,0x87,0xff,0xe8,0x8e,0xc8,0x02,0x03,0xd3,0x03,0x73,0x07,0xea,0x00,0x00,0x00,
0xef,0xe0,0xde,0x00,0xf3,0x33,0x4f,0x70,0x00,0x00,0x1d,0xe0,0x07,0xdc,0x4d,0xf3,
0x00,0xef,0xff,0xe3,0x00,0x0a,0xec,0x70,0x00,0x00,0x03,0x00,0x00,0x00,0xcd,0xc0,
0x2d,0xc0,0xe7,0xf2,0xee,0x20,0x4b,0xff,0xe2,0x00,0x04,0xff,0xa0,0x00,0xcd,0xf9,
0xf9,0x00,0xe7,0xe0,0x7f,0x90,0x4a,0x40,0x04,0x50,0x00,0xff,0xf7,0x47,0x4f,0xff,
0x47,0xf8,0xff,0xff,0xff,0x8f,0xff,0xff,0x07,0x00,0xf0,0x10,0xfb,0x78,0x88,0x7f,
0xff,0xff,0x00,0x24,0x44,0x41,0x0f,0xbb,0xbb,0xe2,0xf0,0x00,0x0f,0xdf,0x44,0x44,
0xff,0xff,0xfc,0xff,0xff,0xf9,0x09,0xff,0xff,0xd5,0xdf,0x20,0x02,0x30,0x01,0x11,
0x11,0xf4,0x01,0xf0,0x06,0x01,0x11,0x11,0x05,0x55,0x55,0x55,0xcc,0xcc,0xcc,0xc0,
0x11,0x11,0x10,0xff,0xff,0xff,0xf0,0x11,0x11,0x10,0xc1,0x00,0xf1,0x00,0x9f,0xff,
0xff,0xf9,0xb7,0xff,0xff,0x7b,0xfe,0x7c,0xc7,0xef,0xff,0xfa,0xaf,0xd5,0x00,0xf1,
0x3b,0x07,0xff,0x60,0x00,0xaf,0xf2,0x00,0x0c,0xff,0x87,0x00,0xef,0xff,0xb0,0x07,
0x8e,0xf2,0x00,0x00,0xf8,0x00,0x00,0x3e,0x00,0x00,0x06,0x50,0x00,0x79,0xb9,0x70,
0x0f,0xfc,0xff,0x00,0xff,0x68,0x83,0x0f,0xf8,0xff,0x8b,0xff,0x8f,0xf8,0x8f,0xf8,
0xff,0xff,0x78,0x8f,0xff,0xf0,0x07,0xff,0xff,0x00,0x0d,0x00,0x00,0x4e,0xfe,0x30,
0x0d,0xff,0xfd,0x00,0xff,0xff,0xf0,0x3f,0xff,0xff,0x3b,0xa3,0x00,0x41,0x88,0x60,
0x04,0xf4,0xb7,0x01,0xf4,0x03,0xdf,0x18,0x81,0x88,0x1f,0xfe,0xaa,0xca,0xae,0xff,
0xea,0xac,0xaa,0xef,0xf1,0x80,0x00,0x81,0xd1,0x03,0x01,0x01,0x00,0xf0,0x07,0x4b,
0xc0,0x00,0x00,0x5c,0xff,0xb0,0x00,0x6e,0xff,0xff,0x40,0x0d,0xff,0xff,0xfc,0x00,
0x06,0x88,0xcf,0xf5,0x00,0x02,0x02,0x00,0x05,0x00,0x53,0x60,0x00,0x00,0x00,0x5d,
0x2a,0x00,0x9b,0xff,0xf8,0xb0,0xff,0xf8,0xfb,0xff,0xfc,0x88,0x11,0x03,0xf0,0x0d,
0x00,0x04,0x77,0x40,0x00,0x09,0xff,0xcc,0xff,0x90,0xcd,0x40,0x00,0x04,0xdc,0x20,
0x4b,0xff,0xb4,0x02,0x01,0xfa,0x55,0xaf,0x10,0x00,0x00,0x21,0x38,0x00,0x10,0xee,
0x05,0x00,0x20,0x87,0x00,0x31,0x04,0xc0,0x44,0x40,0xfb,0xbb,0xbb,0xbb,0xda,0xf7,
0xee,0xee,0xee,0x5f,0x4e,0x01,0xb9,0x2f,0xf5,0x66,0x66,0x66,0xab,0x8b,0xbb,0xbb,
0xbb,0xb3,0x1e,0x00,0x10,0x70,0x1e,0x00,0x10,0x80,0x1e,0x00,0x1e,0x54,0x1e,0x00,
0xcd,0xe0,0x00,0x5f,0xf8,0xff,0xf0,0x00,0x2f,0xf5,0x66,0x64,0x44,0x1e,0x00,0xcc,
0xe7,0x00,0x00,0x5f,0xf8,0xf8,0x00,0x00,0x2f,0xf5,0x65,0x44,0x1e,0x00,0x60,0xd8,
0xf0,0x00,0x00,0x00,0x5f,0x05,0x00,0x61,0x2f,0xf4,0x44,0x44,0x44,0xad,0x1e,0x00,
0x04,0x2c,0x02,0x10,0xd8,0x05,0x00,0xf0,0x04,0x36,0x40,0x00,0x09,0xb1,0x91,0x11,
0x17,0x20,0xef,0x88,0xd8,0x88,0xd9,0x02,0x20,0x06,0x48,0x70,0x18,0x03,0x13,0xec,
0x25,0x00,0xf3,0x1e,0x06,0xdd,0xc3,0x04,0xff,0x3e,0xd0,0x9c,0xb5,0x5f,0x2b,0xf7,
0x1a,0xf4,0xbf,0x81,0xbf,0x39,0xc9,0x64,0xf2,0x4f,0xf3,0xde,0x00,0x6d,0xed,0x30,
0x78,0xdf,0xd8,0x77,0x88,0x88,0x87,0x8f,0xff,0xff,0x88,0xcc,0x8c,0xc8,0x8c,0xc8,
0xcc,0x07,0x00,0x30,0x85,0xff,0xff,0x4f,0x01,0xf4,0x10,0x7e,0x30,0x00,0x00,0x4b,
0xfe,0x00,0x00,0x8f,0x9b,0x70,0x00,0x8f,0xff,0x40,0x00,0x8f,0xff,0x80,0x00,0x7f,
0xff,0x80,0x00,0x0e,0xff,0x80,0x00,0x00,0xee,0x70,0x8e,0x01,0x10,0xaf,0x1e,0x11,
0x82,0xff,0x9c,0xc9,0xff,0xaf,0xff,0xc1,0x1c,0x05,0x00,0x01,0x0f,0x00,0x01,0x19,
0x00,0xf3,0x02,0x07,0xff,0xfe,0x17,0xb6,0x27,0xc3,0xfe,0xb9,0xbe,0x3f,0xff,0xff,
0xf3,0xff,0xff,0xff,0x07,0x00,0x50,0x3c,0xff,0xff,0xe1,0x00,0xcd,0x02,0xc0,0x23,
0x00,0x02,0xf0,0x2e,0x92,0x22,0x5f,0x0d,0xff,0xff,0xff,0x09,0x00,0x35,0x21,0x00,
0x23,0xeb,0x17,0x4f,0xf9,0x00,0xfe,0x00,0x01,0x00,0x24,0x2f,0xf7,0x00,0x01,0x00,
0x26,0x14,0xf9,0x43,0x00,0x25,0xf7,0xfb,0x14,0x00,0x2f,0xfe,0xfe,0x8a,0x00,0x16,
0x18,0xf2,0x44,0x00,0x0f,0x01,0x00,0x1d,0x15,0xfb,0x7c,0x00,0x1e,0xf7,0x16,0x00,
0x0f,0x01,0x00,0x0e,0x2f,0xfe,0xf0,0xfb,0x00,0x2c,0x0f,0xec,0x00,0x1d,0x08,0x36,
0x00,0x70,0xf2,0xf9,0x00,0xf2,0xf2,0xf7,0xfe,0x02,0x01,0x20,0xf2,0xf2,0xb3,0x00,
0x4f,0xfb,0xfb,0x00,0xf9,0x08,0x01,0x16,0x62,0xf4,0xf9,0x00,0xfb,0xfb,0xf7,0xbf,
0x00,0x01,0xf7,0x01,0x10,0xfb,0x42,0x00,0x0f,0xb3,0x01,0x16,0x52,0xfe,0x00,0xfe,
0xfe,0xfb,0x2b,0x01,0x12,0xfe,0xc4,0x00,0x00,0x53,0x19,0x0f,0x36,0x01,0x15,0x43,
0xf4,0x00,0xf9,0xf8,0x7c,0x00,0x5f,0xf4,0x00,0xfb,0xf7,0xf4,0xb8,0x00,0x18,0x0c,
0x4c,0x00,0x0f,0x6d,0x02,0x25,0x0f,0xe6,0x02,0x5e,0x0f,0x01,0x00,0x07,0xd2,0x04,
0x00,0xff,0x03,0x00,0xfd,0xff,0xfd,0xf6,0xfa,0xfc,0x00,0xf6,0xfc,0x08,0x08,0x01,
0x00,0x2d,0xfd,0xff,0x13,0x00,0x08,0x1e,0x00,0x01,0x78,0x01,0x88,0xff,0x00,0xff,
0xfa,0xfd,0xff,0xfd,0xfa,0x83,0x01,0x15,0xff,0x21,0x00,0x0f,0x01,0x00,0x07,0xf7,
0x00,0xfc,0xfd,0xfd,0xfc,0xff,0x00,0xfc,0x00,0xfc,0xf7,0xfc,0xfc,0xfa,0xfa,0xfc,
0x37,0x00,0x02,0x08,0x00,0x00,0x50,0x06,0x5f,0xfc,0x00,0xff,0x00,0xf0,0x0e,0x01,
0x03,0x82,0xf7,0x00,0xfd,0xf9,0xfd,0xf9,0x00,0xfa,0x4c,0x00,0x30,0xf9,0x00,0xf9,
0x13,0x00,0x00,0x63,0x01,0x52,0xf9,0xf9,0xf9,0xf7,0xf9,0x2f,0x01,0x1f,0xf9,0x34,
0x01,0x0f,0x46,0x01,0xfd,0x00,0xfc,0x0d,0x01,0x02,0x13,0x00,0x01,0xac,0x04,0x0f,
0x01,0x00,0x0b,0x0f,0xda,0x00,0x09,0x0f,0x8c,0x02,0x0f,0x10,0xff,0x41,0x00,0x34,
0xff,0x01,0x03,0x6e,0x00,0x06,0x4b,0x02,0x1f,0xff,0x40,0x00,0x10,0x00,0x72,0x01,
0x10,0x00,0x75,0x08,0x3f,0x00,0xfd,0xff,0xf2,0x01,0x1f,0x12,0xff,0x40,0x00,0x2f,
0x01,0xfc,0x38,0x02,0x2a,0x15,0xff,0xbb,0x00,0x09,0x4d,0x01,0x0f,0x3e,0x00,0x15,
0x00,0x81,0x00,0x09,0x31,0x00,0x11,0x01,0x02,0x00,0x0f,0xfb,0x00,0x08,0x53,0xfd,
0xfd,0xfd,0x00,0xff,0x7b,0x01,0x37,0xfa,0xfd,0xfd,0x84,0x01,0x19,0xff,0x94,0x00,
0x10,0xe8,0x2b,0x00,0x1e,0x00,0x2e,0x02,0x51,0xff,0xfd,0xf9,0xff,0xfd,0xaa,0x02,
0x30,0xfa,0x00,0xfd,0xfc,0x00,0x24,0xf6,0xfa,0x1d,0x00,0x05,0x09,0x00,0x0f,0x13,
0x01,0x05,0x00,0x7b,0x00,0x10,0xfc,0x92,0x08,0x53,0xfc,0xfc,0x00,0xf9,0xfc,0xb5,
0x00,0x1e,0x03,0x11,0x01,0x1f,0xf2,0xe8,0x02,0x03,0x63,0xfc,0x01,0xff,0xfd,0x00,
0xfa,0x61,0x00,0x20,0xfd,0xfa,0x0b,0x00,0x10,0xf9,0x76,0x00,0x90,0xfa,0xfa,0xfa,
0x00,0xf6,0xf9,0xf9,0x00,0xf9,0x0c,0x00,0x3f,0xf9,0x00,0xef,0xba,0x00,0x03,0x01,
0xaf,0x00,0x14,0xfc,0x3e,0x00,0xf2,0x02,0x00,0xfd,0xf9,0xfa,0xf6,0xf7,0xfc,0xf9,
0xfa,0xfc,0xfa,0xf7,0xfa,0xfa,0xf7,0xfa,0xf7,0xc0,0x00,0x1f,0xf7,0xba,0x00,0x05,
0x13,0xfc,0xd6,0x00,0x32,0xf9,0xfa,0x00,0xf7,0x00,0x0f,0xec,0x00,0x0d,0x0e,0xe8,
0x02,0x01,0x7e,0x00,0x1e,0xfc,0x02,0x02,0x0f,0xe0,0x03,0x0d,0x0b,0x29,0x03,0x1f,
0x03,0x70,0x02,0x2a,0x0e,0x5a,0x02,0x0f,0x50,0x00,0x0a,0x00,0x5b,0x04,0xbf,0xfc,
0xfd,0xfd,0x00,0xfd,0xf3,0x00,0x00,0xfa,0xf6,0xfa,0x6d,0x00,0x1c,0x50,0xfc,0xfa,
0xfd,0x00,0xfa,0xa5,0x02,0x00,0xa7,0x01,0x18,0xfc,0x24,0x02,0x2f,0xfa,0xff,0x31,
0x03,0x2a,0x03,0x54,0x05,0x0f,0x39,0x01,0x12,0x06,0x3f,0x01,0x12,0xfa,0x0e,0x0b,
0x10,0xfa,0x05,0x00,0x00,0xf4,0x03,0x2f,0xfc,0xfc,0x40,0x00,0x15,0x21,0xff,0xff,
0xa0,0x0c,0x01,0xab,0x01,0x02,0x35,0x04,0x21,0xfd,0xff,0xda,0x00,0x1f,0xf0,0x7c,
0x00,0x16,0x14,0xfd,0xe9,0x01,0x1d,0xfd,0x70,0x03,0x0f,0xe5,0x04,0x12,0x15,0xfd,
0x6c,0x02,0x2a,0xfc,0xff,0x82,0x02,0x0f,0xf1,0x01,0x1c,0x0e,0x1e,0x04,0x0f,0x7c,
0x00,0x0c,0x00,0xf1,0x00,0x04,0xef,0x04,0x00,0x0a,0x01,0x0f,0x7c,0x00,0x16,0x23,
0x03,0x03,0x91,0x04,0x00,0x75,0x00,0x00,0x09,0x00,0x2f,0x01,0x01,0xb8,0x02,0x2d,
0x1f,0xfd,0x28,0x02,0x1c,0x1f,0xff,0x54,0x05,0x1f,0x06,0xb6,0x01,0x16,0xff,0x9b,
0x03,0x10,0xfd,0xf4,0x01,0x0f,0x3e,0x00,0x1b,0x01,0x7c,0x00,0x17,0xfc,0x3e,0x00,
0x1f,0xff,0xa8,0x03,0x21,0x1e,0x01,0x16,0x05,0x0f,0xf7,0x00,0x0e,0x35,0xfc,0xff,
0x04,0x83,0x00,0x14,0xff,0x42,0x00,0x1f,0xf3,0x3e,0x00,0x12,0x10,0x01,0x3e,0x00,
0x13,0x01,0xb4,0x00,0x11,0xfe,0xf7,0x02,0x0f,0xaa,0x02,0x1d,0x07,0xa8,0x01,0x12,
0xfd,0xbb,0x02,0x0f,0x64,0x03,0x17,0x01,0xb1,0x00,0x04,0xda,0x06,0x00,0x0c,0x00,
0x0f,0x74,0x01,0x1a,0x09,0x3e,0x00,0x0f,0x5a,0x04,0x28,0x1f,0xff,0x2e,0x02,0x20,
0x09,0x01,0x00,0x1f,0xf6,0x66,0x0a,0x1d,0x03,0x25,0x01,0x24,0xfd,0xff,0xb8,0x01,
0x1f,0xfd,0x83,0x00,0x01,0x1e,0x02,0xba,0x05,0x04,0x6c,0x09,0x10,0x05,0xb5,0x0e,
0x60,0x00,0x07,0x00,0x08,0x00,0x09,0x65,0x1e,0x07,0x01,0x00,0x16,0x0c,0x0c,0x00,
0x00,0x41,0x10,0x5f,0x00,0x0e,0x0d,0x00,0x0e,0x89,0x00,0x07,0xff,0x2a,0x0f,0x10,
0x11,0x12,0x13,0x14,0x15,0x16,0x00,0x00,0x17,0x18,0x19,0x00,0x1a,0x00,0x1b,0x1c,
0x1d,0x1e,0x1f,0x20,0x21,0x00,0x00,0x22,0x23,0x24,0x00,0x25,0x26,0x27,0x28,0x00,
0x29,0x2a,0x2b,0x00,0x00,0x2c,0x2d,0x2e,0x00,0x2f,0x00,0x30,0x31,0x32,0x33,0x34,
0x35,0x36,0x00,0x00,0x37,0x38,0x39,0x43,0x0b,0x30,0x08,0xf0,0x00,0x00,0x9f,0x26,
0x03,0x47,0x0a,0x00,0xde,0x00,0x12,0x06,0xbb,0x0f,0x09,0x2f,0x00,0x11,0x08,0x85,
0x14,0x55,0x00,0x0a,0x0b,0x00,0x09,0xeb,0x00,0x62,0x0d,0x00,0x0e,0x0f,0x00,0x00,
0xf3,0x13,0x60,0x0e,0x11,0x12,0x13,0x0d,0x00,0xcc,0x00,0x1f,0x17,0x74,0x00,0x07,
0xf1,0x04,0x18,0x00,0x00,0x00,0x19,0x00,0x1a,0x1b,0x00,0x00,0x00,0x1c,0x1d,0x00,
0x1e,0x1f,0x00,0x20,0x21,0xea,0x00,0x01,0x29,0x16,0x92,0x27,0x28,0x29,0x2a,0x2b,
0x2c,0x2d,0x2e,0x2f,0xe9,0x00,0xef,0x31,0x36,0x37,0x38,0x39,0x3a,0x3b,0x2a,0x3c,
0x2a,0x31,0x3d,0x2f,0x3e,0xea,0x00,0x29,0x50,0x00,0x00,0x00,0x00,0x00,
};

static const etxFontCmap cmaps[] = {
{ .range_start = 32, .range_length = 95, .glyph_id_start = 1, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 128, .range_length = 4, .glyph_id_start = 96, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 136, .range_length = 13, .glyph_id_start = 100, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 176, .range_length = 856, .glyph_id_start = 113, .list_length = 4, .type = 3, .unicode_list = 1920, .glyph_id_ofs_list = 0 },
{ .range_start = 1040, .range_length = 26, .glyph_id_start = 117, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 1068, .range_length = 1, .glyph_id_start = 143, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 1070, .range_length = 28, .glyph_id_start = 144, .list_length = 0, .type = 2, .unicode_list = 0, .glyph_id_ofs_list = 0 },
{ .range_start = 1100, .range_length = 62551, .glyph_id_start = 172, .list_length = 68, .type = 3, .unicode_list = 1928, .glyph_id_ofs_list = 0 },
};

static uint8_t etxUncompBuf[10533] __SDRAMFONTS;

const etxLz4Font lv_font_arimo_ua_XXS_s = {
.uncomp_size = 10141,
.comp_size = 6142,
.line_height = 10,
.base_line = 2,
.subpx = 0,
.underline_position = -1,
.underline_thickness = 1,
.kern_scale = 16,
.cmap_num = 8,
.bpp = 4,
.kern_classes = 1,
.bitmap_format = 0,
.left_class_cnt = 57,
.right_class_cnt = 62,
.glyph_bitmap = 2064,
.class_pair_values = 6127,
.left_class_mapping = 9661,
.right_class_mapping = 9901,
.cmaps = cmaps,
.compressed = lz4FontData,
.lvglFontBuf = etxUncompBuf,
.lvglFontBufSize = 10533,
};
