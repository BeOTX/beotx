/*******************************************************************************
 * Size: 16 px
 * Bpp: 2
 * Opts: --no-prefilter --bpp 2 --size 16 --font ../Roboto/Roboto-Regular.ttf -r 0x20-0x7F --font ../../thirdparty/libopenui/thirdparty/lvgl/scripts/built_in_font/FontAwesome5-Solid+Brands+Regular.woff -r 61671,63650,63426,61453,61787,61452,61931 --format lvgl -o lv_font_roboto_bl_16.c --force-fast-kern-format
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LV_FONT_ROBOTO_BL_16
#define LV_FONT_ROBOTO_BL_16 1
#endif

#if LV_FONT_ROBOTO_BL_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */

    /* U+0021 "!" */
    0xbb, 0xbb, 0xbb, 0xac, 0xa0, 0x2a, 0xc0,

    /* U+0022 "\"" */
    0xcd, 0xcc, 0xcc, 0xcc, 0x38,

    /* U+0023 "#" */
    0xd, 0x25, 0x3, 0xb0, 0x48, 0x76, 0xc, 0x27,
    0xfe, 0x82, 0xa0, 0xe1, 0xd2, 0x50, 0x3b, 0x4,
    0x85, 0xff, 0x82, 0x70, 0x61, 0xcc, 0xc, 0x3a,
    0x83, 0x7, 0x49, 0x40, 0x80,

    /* U+0024 "$" */
    0xf, 0xfe, 0xe, 0x87, 0xda, 0x1d, 0x7e, 0x9,
    0xd1, 0xe0, 0x58, 0x56, 0xb, 0xc, 0x85, 0xe0,
    0xfd, 0xf2, 0x1f, 0x5c, 0x1f, 0x58, 0x34, 0x27,
    0x7, 0x82, 0xf0, 0x5f, 0xc8, 0x67, 0x43, 0xec,
    0x30,

    /* U+0025 "%" */
    0x1f, 0x41, 0xfb, 0x6, 0x81, 0xd, 0x82, 0x4a,
    0x6, 0xc1, 0xa6, 0x1c, 0xfa, 0x24, 0x3f, 0x9c,
    0x3f, 0xd9, 0x78, 0x3d, 0x47, 0x1c, 0x3b, 0x24,
    0x18, 0x6d, 0x24, 0x18, 0x68, 0xe, 0x38, 0x7e,
    0xbc, 0x0,

    /* U+0026 "&" */
    0xb, 0xe4, 0x3b, 0xcd, 0x87, 0x61, 0x61, 0xda,
    0x38, 0x75, 0xda, 0x1e, 0xf0, 0x7d, 0xf4, 0x4,
    0x1e, 0x1d, 0x30, 0x68, 0x2e, 0xc1, 0xa1, 0x79,
    0x5, 0xa3, 0xe8, 0x2b, 0xe9, 0xe0,

    /* U+0027 "'" */
    0x33, 0x33,

    /* U+0028 "(" */
    0xf, 0xd8, 0x5a, 0xa, 0x5, 0xa0, 0x70, 0xa8,
    0x17, 0x5, 0xc1, 0x68, 0x5c, 0x15, 0x2, 0xb0,
    0xd8, 0x6d, 0x9, 0xc3, 0x58, 0x68,

    /* U+0029 ")" */
    0xe, 0xa0, 0x6d, 0x9, 0xc3, 0x70, 0x4e, 0x13,
    0x86, 0xd0, 0xb4, 0x2d, 0xb, 0x42, 0xc2, 0x70,
    0xa8, 0x16, 0x82, 0xc0, 0xe1, 0x21, 0x80,

    /* U+002A "*" */
    0xb, 0xf, 0x61, 0x51, 0xd9, 0x2f, 0xa0, 0xbd,
    0x5, 0x66, 0x81, 0x2, 0x80,

    /* U+002B "+" */
    0xd, 0x7, 0xec, 0x3f, 0x61, 0xf3, 0xa1, 0x3f,
    0xf2, 0x2d, 0xac, 0x1d, 0x87, 0xec, 0x3f, 0x61,
    0x80,

    /* U+002C "," */
    0x34, 0xd5, 0x94, 0xc,

    /* U+002D "-" */
    0xe, 0xbe, 0xf, 0x0,

    /* U+002E "." */
    0xac,

    /* U+002F "/" */
    0xc, 0xe1, 0xd4, 0xe, 0xc3, 0x9c, 0x3b, 0x43,
    0xb0, 0xe7, 0xe, 0xd0, 0xec, 0x3a, 0x81, 0xda,
    0x19, 0xc3, 0xa8, 0x1c,

    /* U+0030 "0" */
    0x3, 0xf2, 0x13, 0xcd, 0xa0, 0xe0, 0xac, 0x1a,
    0x13, 0x83, 0x42, 0x70, 0x68, 0x4e, 0xd, 0x9,
    0xc1, 0xa1, 0x38, 0x34, 0x27, 0x7, 0x5, 0xc0,
    0x79, 0xb4, 0x27, 0xe4, 0x0,

    /* U+0031 "1" */
    0xa, 0x8f, 0xd5, 0x1c, 0x17, 0x5, 0xc1, 0x70,
    0x5c, 0x17, 0x5, 0xc1, 0x70, 0x5c, 0x17, 0x0,

    /* U+0032 "2" */
    0x3, 0xf2, 0x15, 0xaa, 0xd0, 0x68, 0x5e, 0x4,
    0x1a, 0xc3, 0xee, 0xf, 0x38, 0x79, 0xd0, 0xf7,
    0x7, 0xb8, 0x3d, 0xe0, 0xf5, 0xa1, 0xef, 0xf9,

    /* U+0033 "3" */
    0x5, 0xf2, 0xb, 0x55, 0xa6, 0x85, 0xc1, 0xee,
    0xe, 0x74, 0x2f, 0x90, 0xe6, 0xd0, 0xf5, 0x88,
    0x6b, 0x34, 0x2b, 0x2d, 0x56, 0x82, 0xf9, 0x0,

    /* U+0034 "4" */
    0xe, 0xf0, 0x79, 0xf0, 0x7b, 0xe0, 0xeb, 0x70,
    0xec, 0x70, 0xdc, 0x38, 0x4e, 0x7, 0xb, 0x40,
    0xe0, 0xbf, 0xe8, 0x3a, 0xc3, 0xe7, 0xf, 0x9c,
    0x0,

    /* U+0035 "5" */
    0x3f, 0xc0, 0xe5, 0xc0, 0xd0, 0xf6, 0x1e, 0x7f,
    0x40, 0x79, 0x5c, 0x1e, 0x70, 0xfb, 0x50, 0x76,
    0xd8, 0x4e, 0xe, 0x57, 0x5, 0xf4, 0x0,

    /* U+0036 "6" */
    0xa, 0xe0, 0x9e, 0x43, 0x70, 0x75, 0x87, 0xba,
    0x7a, 0x7, 0xa5, 0x71, 0xc1, 0x59, 0xc1, 0x39,
    0xc1, 0x39, 0x61, 0x58, 0x3c, 0xad, 0xb, 0xe8,
    0x0,

    /* U+0037 "7" */
    0x7f, 0xe4, 0x3d, 0x61, 0xf7, 0x7, 0xd8, 0x7d,
    0x40, 0xfb, 0x43, 0xd6, 0x1f, 0x68, 0x79, 0xc3,
    0xee, 0xf, 0x38, 0x7d, 0x61, 0xc0,

    /* U+0038 "8" */
    0x3, 0xf2, 0x13, 0xcd, 0xa0, 0xe0, 0xa8, 0xe,
    0xa, 0xc0, 0xe8, 0xe8, 0x57, 0xd0, 0x4e, 0xb6,
    0x83, 0x82, 0xb0, 0x68, 0x4e, 0xe, 0xa, 0xc1,
    0x6b, 0x68, 0x4f, 0xc8, 0x0,

    /* U+0039 "9" */
    0x3, 0xf0, 0x4f, 0x3e, 0x7, 0x5, 0xc6, 0x85,
    0x66, 0x85, 0x66, 0x85, 0x65, 0xa3, 0xe0, 0x7e,
    0xb0, 0xf7, 0x7, 0x38, 0x66, 0xd0, 0xae, 0x40,

    /* U+003A ":" */
    0xa9, 0xf, 0xf4, 0xd0,

    /* U+003B ";" */
    0x34, 0x90, 0xff, 0xe2, 0x49, 0xa6, 0xac, 0x30,

    /* U+003C "<" */
    0xe, 0x60, 0x9f, 0x87, 0xd2, 0x3c, 0x1d, 0xe8,
    0x39, 0xbc, 0x87, 0x58, 0x7c,

    /* U+003D "=" */
    0xf, 0xbf, 0xd0, 0xbc, 0x1f, 0xbf, 0xd0, 0x7c,

    /* U+003E ">" */
    0x90, 0xeb, 0xc8, 0x75, 0xe4, 0x39, 0xe0, 0xaf,
    0x2b, 0xe4, 0x1c, 0x87, 0xfc,

    /* U+003F "?" */
    0x5, 0xe8, 0x1e, 0x57, 0x38, 0x56, 0x1d, 0x61,
    0xdc, 0x1b, 0xc1, 0xac, 0x3b, 0x43, 0xa0, 0xff,
    0xe0, 0xc1, 0xed, 0x0,

    /* U+0040 "@" */
    0xe, 0xbe, 0x90, 0xf3, 0xc1, 0x3c, 0x19, 0xc3,
    0xed, 0xb, 0x40, 0xf9, 0x6, 0x6, 0x5, 0x8e,
    0xc, 0x1a, 0xc, 0xe, 0x9, 0x30, 0x38, 0x18,
    0xc, 0x60, 0xa0, 0x18, 0xc, 0x60, 0xa0, 0x28,
    0x9, 0x30, 0x50, 0x14, 0x6, 0xd, 0x1c, 0x7c,
    0x38, 0x1c, 0x17, 0x1e, 0x83, 0x68, 0x7f, 0xf0,
    0x79, 0x9, 0xf, 0xcf, 0xe4, 0x30,

    /* U+0041 "A" */
    0xd, 0x61, 0xfd, 0xe4, 0x3e, 0x7b, 0xf, 0xa8,
    0xe1, 0xf6, 0x9c, 0x1c, 0xe0, 0xb0, 0xef, 0x1,
    0xc3, 0xb4, 0x2e, 0xa, 0xff, 0x82, 0xf0, 0x67,
    0x41, 0xa1, 0xdc, 0x58, 0x7a, 0xc0,

    /* U+0042 "B" */
    0xbf, 0x90, 0x5a, 0xd6, 0x96, 0x1b, 0x8b, 0xd,
    0xc5, 0x84, 0xe9, 0x7f, 0x40, 0xb0, 0x36, 0x96,
    0x1a, 0xcb, 0xc, 0xe5, 0x86, 0xb2, 0xd6, 0xb4,
    0xbf, 0x90, 0x0,

    /* U+0043 "C" */
    0xa, 0xfa, 0xd, 0xe5, 0xb8, 0xe, 0x19, 0xd3,
    0x83, 0xb8, 0xe0, 0xfd, 0xa1, 0xfb, 0x43, 0xf7,
    0x7, 0xee, 0xe, 0xd1, 0xc3, 0x3a, 0xf, 0x2d,
    0xc1, 0xaf, 0x90, 0x0,

    /* U+0044 "D" */
    0xbf, 0x41, 0x5a, 0xde, 0x5, 0x86, 0xf1, 0x61,
    0x9c, 0xb0, 0xed, 0xb0, 0xee, 0x98, 0x77, 0x4c,
    0x3b, 0x6c, 0x33, 0x96, 0x1b, 0xc5, 0xad, 0xe0,
    0x5f, 0xa0, 0x80,

    /* U+0045 "E" */
    0xbf, 0xcd, 0xaf, 0x16, 0x1e, 0xb0, 0xf5, 0x87,
    0xaf, 0xf1, 0x61, 0xeb, 0xf, 0x58, 0x7a, 0xc3,
    0xd6, 0xbc, 0x5f, 0xe8,

    /* U+0046 "F" */
    0xbf, 0xcd, 0xaf, 0x16, 0x1e, 0xb0, 0xf5, 0x87,
    0xac, 0x3d, 0x7f, 0x45, 0x87, 0xac, 0x3d, 0x61,
    0xeb, 0xf, 0x58, 0x78,

    /* U+0047 "G" */
    0xa, 0xfa, 0xd, 0xe5, 0xbc, 0x7, 0xe, 0xd3,
    0xc1, 0xca, 0x38, 0x3f, 0x68, 0x7e, 0xd0, 0x3f,
    0x47, 0x7, 0x71, 0x61, 0xdc, 0x3a, 0x1b, 0x81,
    0x72, 0xad, 0x9, 0xfc, 0x80,

    /* U+0048 "H" */
    0xb0, 0xe7, 0x2c, 0x39, 0xcb, 0xe, 0x72, 0xc3,
    0x9c, 0xb0, 0xe7, 0x2f, 0xfc, 0x58, 0x75, 0x96,
    0x1c, 0xe5, 0x87, 0x39, 0x61, 0xce, 0x58, 0x73,
    0x96, 0x1c, 0xe0,

    /* U+0049 "I" */
    0xbb, 0xbb, 0xbb, 0xbb, 0xbb, 0xbb,

    /* U+004A "J" */
    0xf, 0x70, 0x7b, 0x83, 0xdc, 0x1e, 0xe0, 0xf7,
    0x7, 0xb8, 0x3d, 0xc1, 0xee, 0x10, 0xdc, 0xe1,
    0xb4, 0xf2, 0xbc, 0x15, 0xe8, 0x0,

    /* U+004B "K" */
    0xb0, 0xd6, 0x96, 0x13, 0xa0, 0xb0, 0x3c, 0x15,
    0x83, 0x83, 0x59, 0xe0, 0xeb, 0xe4, 0x3a, 0xfc,
    0x1d, 0x69, 0xe0, 0xd6, 0x7, 0x82, 0xb0, 0xad,
    0x5, 0x86, 0xf0, 0x2c, 0x3b, 0x80,

    /* U+004C "L" */
    0xb0, 0xf5, 0x87, 0xac, 0x3d, 0x61, 0xeb, 0xf,
    0x58, 0x7a, 0xc3, 0xd6, 0x1e, 0xb0, 0xf5, 0x87,
    0xad, 0x78, 0xbf, 0xc0,

    /* U+004D "M" */
    0xb4, 0x3c, 0xf4, 0xf0, 0x7b, 0xd4, 0xf0, 0x7b,
    0xd5, 0x70, 0x6b, 0xd5, 0x38, 0x6d, 0xe9, 0x9a,
    0x7, 0x3a, 0x65, 0x1, 0xc7, 0x4c, 0x70, 0x69,
    0xd3, 0x6, 0xd8, 0x3a, 0x60, 0xbd, 0x3, 0xa6,
    0x17, 0x82, 0xe9, 0x85, 0xc1, 0x70,

    /* U+004E "N" */
    0xb0, 0xe7, 0x2f, 0x6, 0x72, 0xf2, 0x13, 0x97,
    0x61, 0x39, 0x67, 0x1, 0xcb, 0x1c, 0xe, 0x58,
    0x3c, 0x39, 0x61, 0x6a, 0xcb, 0xa, 0xec, 0xb0,
    0xdf, 0x16, 0x19, 0xf1, 0x61, 0xd6, 0x0,

    /* U+004F "O" */
    0x9, 0xf9, 0xe, 0xb9, 0xb8, 0x27, 0x42, 0x74,
    0x1e, 0xe, 0xf0, 0x38, 0x3a, 0xc1, 0xa1, 0xce,
    0xd, 0xe, 0x70, 0x70, 0x75, 0x83, 0xc1, 0xd6,
    0x7, 0x43, 0x68, 0x57, 0x37, 0x83, 0x9f, 0xa0,
    0x80,

    /* U+0050 "P" */
    0xbf, 0xa0, 0x5a, 0xef, 0x16, 0x19, 0xdb, 0xe,
    0xdb, 0xe, 0xdb, 0xd, 0xe2, 0xff, 0x2, 0xc3,
    0xeb, 0xf, 0xac, 0x3e, 0xb0, 0xfa, 0xc3, 0xe0,

    /* U+0051 "Q" */
    0xa, 0xf9, 0xe, 0xf4, 0xdc, 0x13, 0x86, 0x74,
    0x1c, 0x1d, 0xc0, 0xd0, 0xeb, 0x6, 0x87, 0x58,
    0x34, 0x3a, 0xc1, 0xa1, 0xd6, 0xe, 0xe, 0xe0,
    0x38, 0x67, 0x42, 0xf2, 0xae, 0xe, 0xbf, 0x21,
    0xfd, 0x70, 0x7f, 0x28,

    /* U+0052 "R" */
    0xbf, 0x90, 0x5a, 0xd6, 0x96, 0x1a, 0xcb, 0xc,
    0xe5, 0x86, 0xb2, 0xc2, 0x78, 0xbf, 0xa0, 0x58,
    0x1c, 0x2b, 0xb, 0x81, 0x61, 0x3a, 0x58, 0x6f,
    0x16, 0x19, 0xd0,

    /* U+0053 "S" */
    0x3, 0xf4, 0x13, 0xca, 0xf0, 0x38, 0x37, 0x1c,
    0x19, 0x45, 0xa1, 0xf5, 0xe8, 0x3e, 0xbd, 0x7,
    0xcf, 0x10, 0x75, 0x9a, 0x1b, 0xc5, 0xca, 0xb4,
    0xf, 0xe4,

    /* U+0054 "T" */
    0xbf, 0xf0, 0x16, 0xe5, 0x83, 0xb8, 0x3f, 0x70,
    0x7e, 0xe0, 0xfd, 0xc1, 0xfb, 0x83, 0xf7, 0x7,
    0xee, 0xf, 0xdc, 0x1f, 0xb8, 0x3f, 0x70, 0x60,

    /* U+0055 "U" */
    0xe0, 0xed, 0xe0, 0xed, 0xe0, 0xed, 0xe0, 0xed,
    0xe0, 0xed, 0xe0, 0xed, 0xe0, 0xed, 0xe0, 0xed,
    0xe0, 0xed, 0xb0, 0xd6, 0xf, 0x2a, 0xe0, 0xaf,
    0x90, 0x0,

    /* U+0056 "V" */
    0xb0, 0xf7, 0x9d, 0xe, 0xd3, 0x83, 0x38, 0x2c,
    0x37, 0x82, 0xd0, 0xb4, 0x2e, 0x3, 0x86, 0x70,
    0x70, 0x76, 0x9a, 0x1d, 0xce, 0x1e, 0x7d, 0x7,
    0xde, 0x43, 0xeb, 0xc,

    /* U+0057 "W" */
    0x70, 0xd6, 0x1b, 0x8d, 0xb, 0xc1, 0xb8, 0xe0,
    0xbc, 0x85, 0xa5, 0x0, 0xf4, 0x3, 0x81, 0xc1,
    0x47, 0x5, 0x81, 0xc1, 0xa6, 0x9c, 0x16, 0x98,
    0x28, 0x68, 0x5c, 0xe0, 0x77, 0xd, 0x74, 0xb,
    0xb0, 0xcf, 0x90, 0xbd, 0x7, 0x78, 0x35, 0xa1,
    0xdc, 0x19, 0xc2,

    /* U+0058 "X" */
    0x38, 0x35, 0x82, 0xc3, 0x70, 0x5e, 0x5, 0x86,
    0x75, 0x68, 0x75, 0xf0, 0x7d, 0xe0, 0xfd, 0xe4,
    0x3d, 0xf8, 0x39, 0xd5, 0xa1, 0xb8, 0x16, 0x15,
    0x86, 0xe0, 0x70, 0x67, 0x40,

    /* U+0059 "Y" */
    0xb0, 0xe7, 0x7, 0x6, 0xe0, 0x58, 0x4e, 0x1b,
    0x81, 0xc1, 0xac, 0x70, 0xf7, 0x70, 0x79, 0xf0,
    0x7e, 0xe0, 0xfd, 0xc1, 0xfb, 0x83, 0xf7, 0x7,
    0xee, 0xc,

    /* U+005A "Z" */
    0x3f, 0xe8, 0x5e, 0xb4, 0x3d, 0xe0, 0xf5, 0x87,
    0xdc, 0x1e, 0xf0, 0x79, 0xc3, 0xee, 0xf, 0x78,
    0x3c, 0xe8, 0x7b, 0xcb, 0xf7, 0xfe,

    /* U+005B "[" */
    0xd, 0xf1, 0xc0, 0xe0, 0x70, 0x38, 0x1c, 0xe,
    0x7, 0x3, 0x81, 0xc0, 0xe0, 0x70, 0x38, 0x1c,
    0xe, 0x7, 0xc1, 0xc0,

    /* U+005C "\\" */
    0xb0, 0xf6, 0x1e, 0xe0, 0xe7, 0xf, 0x68, 0x75,
    0x3, 0x9c, 0x3d, 0xa1, 0xd6, 0x1e, 0xc3, 0xdc,
    0x1c, 0xe1, 0xed,

    /* U+005D "]" */
    0xd, 0xf0, 0x2c, 0xe, 0x7, 0x3, 0x81, 0xc0,
    0xe0, 0x70, 0x38, 0x1c, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe7, 0xc1, 0xc0,

    /* U+005E "^" */
    0x3, 0x87, 0x5a, 0x1b, 0xb0, 0xac, 0xc2, 0xd2,
    0x83, 0x81, 0xc0,

    /* U+005F "_" */
    0xf, 0xdf, 0xf0, 0x7f, 0x0,

    /* U+0060 "`" */
    0x20, 0xac, 0x2d,

    /* U+0061 "a" */
    0x5, 0xf2, 0xb, 0x55, 0x81, 0xd, 0xa0, 0x7f,
    0x45, 0xa0, 0xe3, 0x42, 0xe3, 0x42, 0xe3, 0xca,
    0xf4, 0xb, 0xcd, 0x0,

    /* U+0062 "b" */
    0xe0, 0xf7, 0x7, 0xb8, 0x3d, 0xd3, 0xd0, 0x3d,
    0x37, 0x1c, 0x15, 0x9c, 0x13, 0x9c, 0x1b, 0x38,
    0x27, 0x38, 0x2b, 0x3d, 0x36, 0x9d, 0x3d, 0x0,

    /* U+0063 "c" */
    0x3, 0xf2, 0x7, 0x9b, 0x4e, 0xa, 0x86, 0x87,
    0x38, 0x7d, 0xa1, 0xee, 0xa, 0x83, 0xaa, 0xd0,
    0x3f, 0x20,

    /* U+0064 "d" */
    0xf, 0x58, 0x7a, 0xc3, 0xd6, 0xb, 0xd4, 0xc7,
    0x9b, 0xc7, 0x5, 0x66, 0x85, 0x66, 0x1a, 0xcd,
    0xa, 0xce, 0xa, 0xc7, 0x47, 0xc0, 0xbd, 0x4c,

    /* U+0065 "e" */
    0x3, 0xf2, 0x7, 0x9b, 0x7, 0x5, 0xc6, 0x85,
    0x6f, 0xfc, 0x68, 0x7b, 0x83, 0xcf, 0x2b, 0x80,
    0xfd, 0x0,

    /* U+0066 "f" */
    0xf, 0xef, 0x40, 0xf2, 0x16, 0x86, 0xd0, 0x5f,
    0x80, 0xe8, 0x6d, 0xd, 0xa1, 0xb4, 0x36, 0x86,
    0xd0, 0xda, 0x1b, 0x40,

    /* U+0067 "g" */
    0x5, 0xea, 0x63, 0xcd, 0xe3, 0x82, 0xb3, 0x42,
    0xb3, 0xd, 0x66, 0x85, 0x67, 0x5, 0x63, 0xcd,
    0xe0, 0x5e, 0xa6, 0x1e, 0xe2, 0xd5, 0x68, 0x2f,
    0x90,

    /* U+0068 "h" */
    0xe0, 0xee, 0xe, 0xe0, 0xee, 0x9e, 0x8f, 0x4d,
    0xbc, 0x17, 0x70, 0x54, 0xe0, 0xaf, 0x41, 0x5e,
    0x82, 0xbd, 0x5, 0x7a, 0xa, 0xc0,

    /* U+0069 "i" */
    0xa2, 0x81, 0xdd, 0xdd, 0xdd, 0xdd, 0xc0,

    /* U+006A "j" */
    0x7, 0x2, 0x43, 0xdc, 0xe, 0x7, 0x3, 0x81,
    0xc0, 0xe0, 0x70, 0x38, 0x1c, 0xe, 0x1d, 0x5c,
    0x0,

    /* U+006B "k" */
    0xe0, 0xf7, 0x7, 0xb8, 0x3d, 0xc0, 0x74, 0xe1,
    0xd0, 0x73, 0xc1, 0x77, 0x6, 0xfc, 0x1b, 0xc7,
    0x5, 0xc3, 0xa0, 0xe0, 0x58, 0x38, 0x2e, 0x0,

    /* U+006C "l" */
    0xee, 0xee, 0xee, 0xee, 0xee, 0xee,

    /* U+006D "m" */
    0xe9, 0xe8, 0xbd, 0x1e, 0x9b, 0xd2, 0xbb, 0x82,
    0xf0, 0x57, 0xa0, 0xa8, 0x15, 0xe8, 0x2a, 0x5,
    0x7a, 0xa, 0x81, 0x5e, 0x82, 0xa0, 0x57, 0xa0,
    0xa8, 0x15, 0xe8, 0x2a, 0x5, 0x60,

    /* U+006E "n" */
    0xe9, 0xe8, 0xf4, 0xdb, 0xc1, 0x77, 0x5, 0x4e,
    0xa, 0xf4, 0x15, 0xe8, 0x2b, 0xd0, 0x57, 0xa0,
    0xac,

    /* U+006F "o" */
    0x3, 0xf2, 0x13, 0xcd, 0xc0, 0xe0, 0xac, 0x1a,
    0x1b, 0x56, 0x1d, 0xa6, 0x86, 0xd3, 0x82, 0xb0,
    0x3c, 0xae, 0x9, 0xf9, 0x0,

    /* U+0070 "p" */
    0xe9, 0xe8, 0x1e, 0x47, 0x4e, 0xa, 0xce, 0x9,
    0xce, 0xd, 0x9c, 0x13, 0x9c, 0x15, 0x9e, 0x55,
    0xa7, 0x4f, 0x40, 0xe0, 0xf7, 0x7, 0xb8, 0x3c,

    /* U+0071 "q" */
    0x5, 0xea, 0x63, 0xcd, 0xe3, 0x82, 0xb3, 0x42,
    0xb3, 0xd, 0x66, 0x85, 0x67, 0x5, 0x63, 0xcd,
    0xe0, 0x5e, 0xa6, 0x1e, 0xb0, 0xf5, 0x87, 0xac,

    /* U+0072 "r" */
    0xe, 0xef, 0x1e, 0x93, 0x82, 0xe0, 0xb8, 0x2e,
    0xb, 0x82, 0xe0, 0xb8, 0x20,

    /* U+0073 "s" */
    0x5, 0xe8, 0x2b, 0x57, 0x81, 0xc1, 0x40, 0xb4,
    0x3d, 0x7c, 0x87, 0xac, 0x1a, 0x16, 0x9e, 0x55,
    0x85, 0x7c, 0x80,

    /* U+0074 "t" */
    0x1c, 0x27, 0x7, 0xe8, 0x70, 0x9c, 0x27, 0x9,
    0xc2, 0x70, 0x9c, 0x27, 0x42, 0xb8,

    /* U+0075 "u" */
    0xe0, 0xa9, 0xc1, 0x53, 0x82, 0xa7, 0x5, 0x4e,
    0xa, 0x9c, 0x15, 0x38, 0x2e, 0x9a, 0xae, 0x2f,
    0x54,

    /* U+0076 "v" */
    0xb0, 0xda, 0x61, 0x38, 0x38, 0x1c, 0xb, 0x6,
    0x85, 0x8e, 0x1b, 0x68, 0x1a, 0xf2, 0x1d, 0xe0,
    0xf7, 0x4,

    /* U+0077 "w" */
    0xb0, 0xa8, 0x17, 0x38, 0x5e, 0xb, 0x6, 0x8f,
    0x91, 0xc1, 0x42, 0xb1, 0x40, 0x39, 0xab, 0x34,
    0x2d, 0xc1, 0xb8, 0x6f, 0x40, 0xbc, 0x1a, 0xd0,
    0x3c, 0x19, 0xc3, 0x68, 0x0,

    /* U+0078 "x" */
    0x74, 0xe, 0xb, 0x7, 0x5, 0xd3, 0xc, 0xf9,
    0xe, 0xf0, 0x73, 0xe4, 0x36, 0xd8, 0x56, 0xe,
    0x1d, 0x3, 0xa0,

    /* U+0079 "y" */
    0xb0, 0x9c, 0x70, 0xac, 0x1c, 0xe, 0x5, 0x83,
    0xd, 0x96, 0x1b, 0xb4, 0x35, 0xe0, 0xf7, 0x83,
    0xda, 0x1e, 0xc3, 0x9e, 0xc, 0xf0, 0x70,

    /* U+007A "z" */
    0x3f, 0xc0, 0x5d, 0xe0, 0xeb, 0xf, 0x68, 0x77,
    0x7, 0x58, 0x73, 0xa1, 0xde, 0xe, 0x7f, 0xc8,

    /* U+007B "{" */
    0xf, 0xeb, 0x9, 0xc3, 0x50, 0x37, 0x6, 0xe0,
    0xdc, 0x13, 0xa0, 0xb8, 0x35, 0x87, 0x70, 0x6e,
    0xd, 0xc1, 0xb8, 0x35, 0x87, 0x78, 0x39, 0x0,

    /* U+007C "|" */
    0xaf, 0xfe, 0x80,

    /* U+007D "}" */
    0xe, 0xb0, 0xd6, 0x13, 0x86, 0xc3, 0x61, 0xb4,
    0x2e, 0xd, 0xe0, 0x78, 0x2d, 0xb, 0xd, 0x84,
    0xe1, 0x58, 0x1d, 0x2, 0x18,

    /* U+007E "~" */
    0xf, 0xf5, 0xe0, 0x9e, 0xdb, 0x4e, 0xd0, 0x5f,
    0x7, 0xf8,

    /* U+F00C "" */
    0xf, 0xfe, 0xd, 0x3, 0xff, 0x83, 0x7c, 0x1f,
    0xf5, 0xf4, 0x1f, 0xeb, 0xf0, 0x28, 0x1e, 0xbf,
    0x3, 0xe8, 0x35, 0xf8, 0x2b, 0xe8, 0x17, 0xe0,
    0xef, 0xd4, 0xfc, 0x1f, 0x7f, 0xd0, 0x7f, 0x7f,
    0x41, 0xff, 0x5e, 0x83, 0xff, 0x83, 0x40, 0xfe,

    /* U+F00D "" */
    0xf, 0xfa, 0xf0, 0x77, 0xaf, 0xc1, 0x7e, 0x7f,
    0x1f, 0x91, 0xff, 0x90, 0x9f, 0xe4, 0x3b, 0xf8,
    0x3b, 0xfe, 0xb, 0xf5, 0xf8, 0xfc, 0x8f, 0xfc,
    0x84, 0xfc, 0x48, 0x73, 0x0,

    /* U+F0E7 "" */
    0x7, 0xf8, 0x3d, 0xfe, 0xf, 0x7f, 0x21, 0xcf,
    0xf0, 0x7a, 0xfe, 0xf, 0x5f, 0xfc, 0xf, 0xfe,
    0x81, 0xff, 0xc1, 0x7f, 0xe8, 0x3e, 0xbe, 0xf,
    0xdf, 0x21, 0xfb, 0xe0, 0xfc, 0xf8, 0x3f, 0xae,
    0xf, 0xef, 0x7, 0xfb, 0x43, 0xc0,

    /* U+F15B "" */
    0xff, 0x8c, 0x2f, 0xf8, 0xf0, 0x3f, 0xe3, 0xe3,
    0xfe, 0x3f, 0xfe, 0xe, 0xff, 0xff, 0xff, 0xff,
    0xfb, 0x40,

    /* U+F1EB "" */
    0xf, 0xfe, 0x6b, 0x7f, 0xa4, 0x3f, 0x3f, 0xff,
    0xc0, 0x43, 0x3f, 0xea, 0xdf, 0xe4, 0x7f, 0x21,
    0xf9, 0xfc, 0xfc, 0x87, 0xff, 0x1, 0xf8, 0x83,
    0x37, 0xe9, 0xd, 0x7, 0x3f, 0xfe, 0x43, 0xe7,
    0xf5, 0x6f, 0xc8, 0x7d, 0xe4, 0x3c, 0xf8, 0x3f,
    0xfa, 0x8f, 0x90, 0xff, 0xe2, 0x7e, 0xf, 0xfe,
    0x27, 0xe0, 0xff, 0xe2, 0x3e, 0x43, 0xf0,

    /* U+F7C2 "" */
    0xa, 0xff, 0x90, 0x5f, 0xfc, 0x5c, 0x64, 0x9e,
    0xbd, 0x19, 0x27, 0xf4, 0x64, 0x9f, 0xff, 0xff,
    0xff, 0xff, 0x1b, 0xff, 0xe4,

    /* U+F8A2 "" */
    0xf, 0xfe, 0xa6, 0x1f, 0xfc, 0x3f, 0x6, 0xb0,
    0xfc, 0xf8, 0x2f, 0x83, 0xf3, 0xe0, 0x7e, 0x5f,
    0xd7, 0x8f, 0xff, 0xe2, 0xf, 0xff, 0xf0, 0xc0,
    0xfc, 0x1f, 0xfc, 0x27, 0xc1, 0xff, 0xc3, 0x60,
    0xff, 0xe0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 63, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 0, .adv_w = 66, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 82, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 12, .adv_w = 158, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 144, .box_w = 9, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 74, .adv_w = 188, .box_w = 12, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 159, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 45, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 8},
    {.bitmap_index = 140, .adv_w = 88, .box_w = 5, .box_h = 18, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 162, .adv_w = 89, .box_w = 5, .box_h = 18, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 185, .adv_w = 110, .box_w = 7, .box_h = 7, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 198, .adv_w = 145, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 215, .adv_w = 50, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 219, .adv_w = 71, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 223, .adv_w = 67, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 106, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 244, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 144, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 289, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 313, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 337, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 362, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 385, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 410, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 144, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 461, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 485, .adv_w = 62, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 54, .box_w = 3, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 497, .adv_w = 130, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 510, .adv_w = 141, .box_w = 7, .box_h = 6, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 518, .adv_w = 134, .box_w = 7, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 531, .adv_w = 121, .box_w = 7, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 551, .adv_w = 230, .box_w = 14, .box_h = 15, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 605, .adv_w = 167, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 635, .adv_w = 159, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 167, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 690, .adv_w = 168, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 717, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 737, .adv_w = 142, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 757, .adv_w = 174, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 786, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 813, .adv_w = 70, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 819, .adv_w = 141, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 841, .adv_w = 161, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 871, .adv_w = 138, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 891, .adv_w = 224, .box_w = 12, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 929, .adv_w = 183, .box_w = 10, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 960, .adv_w = 176, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 993, .adv_w = 162, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1017, .adv_w = 176, .box_w = 11, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1053, .adv_w = 158, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1080, .adv_w = 152, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1106, .adv_w = 153, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1130, .adv_w = 166, .box_w = 9, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1156, .adv_w = 163, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1184, .adv_w = 227, .box_w = 14, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1227, .adv_w = 161, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1256, .adv_w = 154, .box_w = 10, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1282, .adv_w = 153, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1304, .adv_w = 68, .box_w = 4, .box_h = 18, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1324, .adv_w = 105, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 1343, .adv_w = 68, .box_w = 4, .box_h = 18, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1363, .adv_w = 107, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 1374, .adv_w = 116, .box_w = 8, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 1379, .adv_w = 79, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 10},
    {.bitmap_index = 1382, .adv_w = 139, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1402, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1426, .adv_w = 134, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1444, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1468, .adv_w = 136, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1486, .adv_w = 89, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1506, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1531, .adv_w = 141, .box_w = 7, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1553, .adv_w = 62, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1560, .adv_w = 61, .box_w = 4, .box_h = 15, .ofs_x = -1, .ofs_y = -3},
    {.bitmap_index = 1577, .adv_w = 130, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1601, .adv_w = 62, .box_w = 2, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1607, .adv_w = 224, .box_w = 12, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1637, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1654, .adv_w = 146, .box_w = 9, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1675, .adv_w = 144, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 1699, .adv_w = 146, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1723, .adv_w = 87, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1736, .adv_w = 132, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1755, .adv_w = 84, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1769, .adv_w = 141, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1786, .adv_w = 124, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1804, .adv_w = 192, .box_w = 12, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1833, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1852, .adv_w = 121, .box_w = 8, .box_h = 12, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1875, .adv_w = 127, .box_w = 8, .box_h = 9, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1891, .adv_w = 87, .box_w = 6, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1915, .adv_w = 62, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 1918, .adv_w = 87, .box_w = 5, .box_h = 17, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 1939, .adv_w = 174, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 1949, .adv_w = 256, .box_w = 16, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1989, .adv_w = 176, .box_w = 11, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2018, .adv_w = 160, .box_w = 12, .box_h = 16, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 2056, .adv_w = 192, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2074, .adv_w = 320, .box_w = 20, .box_h = 15, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 2129, .adv_w = 192, .box_w = 12, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 2150, .adv_w = 258, .box_w = 17, .box_h = 11, .ofs_x = 0, .ofs_y = 1}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_1[] = {
    0x0, 0x1, 0xdb, 0x14f, 0x1df, 0x7b6, 0x896
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 61452, .range_length = 2199, .glyph_id_start = 96,
        .unicode_list = unicode_list_1, .glyph_id_ofs_list = NULL, .list_length = 7, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 0,
    2, 3, 0, 0, 0, 4, 0, 4,
    5, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 6, 7, 8, 9, 10, 11,
    0, 12, 12, 13, 14, 15, 12, 12,
    9, 16, 17, 18, 0, 19, 13, 20,
    21, 22, 23, 24, 25, 0, 0, 0,
    0, 0, 26, 27, 28, 0, 29, 30,
    0, 31, 0, 0, 32, 0, 31, 31,
    33, 27, 0, 34, 0, 35, 0, 36,
    37, 38, 36, 39, 40, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 1, 0, 2, 0, 0, 0, 3,
    2, 0, 4, 5, 0, 6, 7, 6,
    8, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    9, 0, 10, 0, 11, 0, 0, 0,
    11, 0, 0, 12, 0, 0, 0, 0,
    11, 0, 11, 0, 13, 14, 15, 16,
    17, 18, 19, 20, 0, 0, 21, 0,
    0, 0, 22, 0, 23, 23, 23, 24,
    23, 0, 0, 0, 0, 0, 25, 25,
    26, 25, 23, 27, 28, 29, 30, 31,
    32, 33, 31, 34, 0, 0, 35, 0,
    0, 0, 0, 0, 0, 0, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -13, 0, 0, 0,
    0, 0, 0, 0, -15, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -6, -7, 0, -2, -8, 0, -10, 0,
    0, 0, 1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 3, 2, 0,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -21, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -28, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -15, 0, 0, 0, 0, 0, 0, -8,
    0, -1, 0, 0, -16, -2, -11, -9,
    0, -12, 0, 0, 0, 0, 0, 0,
    -1, 0, 0, -2, -1, -6, -4, 0,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -3,
    0, -3, 0, 0, -7, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -3, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -4, 0, 0, 0, 0, 0,
    0, -1, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, -13, 0, 0,
    0, -3, 0, 0, 0, -3, 0, -3,
    0, -3, -5, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    3, 0, 0, 0, 0, 0, 0, 0,
    0, -2, -2, 0, -2, 0, 0, 0,
    -2, -3, -3, 0, 0, 0, 0, 0,
    0, 0, 0, -29, 0, 0, 0, -21,
    0, -33, 0, 3, 0, 0, 0, 0,
    0, 0, 0, -4, -3, 0, 0, -3,
    -3, 0, 0, -3, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, -4, 0,
    0, 0, 2, -3, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -8, 0, 0,
    0, -4, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -3, 0, -3,
    -3, 0, 0, 0, -3, -5, -8, 0,
    0, 0, 0, -42, 0, 0, 0, 0,
    0, 0, 0, 2, -8, 0, 0, -34,
    -7, -22, -18, 0, -30, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -5,
    -17, -11, 0, 0, 0, 0, 0, 0,
    0, 0, -40, 0, 0, 0, -17, 0,
    -25, 0, 0, 0, 0, 0, -4, 0,
    -3, 0, -1, -2, 0, 0, -2, 0,
    0, 2, 0, 2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -5, 0, -3,
    -2, 0, -4, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -10, 0, -2, 0, 0, -6, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -5, 0,
    0, 0, 0, -27, -29, 0, 0, -10,
    -3, -30, -2, 2, 0, 2, 2, 0,
    2, 0, 0, -14, -12, 0, -14, -12,
    -9, -14, 0, -12, -9, -7, -10, -7,
    0, 0, 0, 0, 3, 0, -28, -5,
    0, 0, -9, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 2, -6, -5,
    0, 0, -6, -4, 0, 0, -3, -1,
    0, 0, 0, 2, 0, 0, 0, 2,
    0, -15, -7, 0, 0, -5, 0, 0,
    0, 2, 0, 0, 0, 0, 0, 0,
    2, -4, -4, 0, 0, -4, -3, 0,
    0, -2, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, -6, 0, 0,
    0, -3, 0, 0, 0, 0, 2, 0,
    0, 0, 0, 0, 0, -3, 0, 0,
    -3, 0, 0, 0, -3, -4, 0, 0,
    0, 0, 0, 0, -4, 3, -6, -26,
    -6, 0, 0, -12, -4, -12, -2, 2,
    -12, 2, 2, 2, 2, 0, 2, -9,
    -8, -3, -5, -8, -5, -7, -3, -5,
    -2, 0, -3, -4, 2, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 2, -3,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -3, 0, 0, -3, 0,
    0, 0, -2, -3, -3, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, -2, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -8, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -2, 0, 0, 0, 0, 0, -4,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, -1, 0, -2, -2,
    0, 0, -1, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, -2, 0, 0, 0, 0, 0,
    2, 0, 3, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 2, 0, -3, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 2, 0, -13, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -17, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, 0,
    -3, -2, 0, 0, 2, 0, 0, 0,
    -15, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -5, -2, 2, 0, -2, 0, 0, 6,
    0, 2, 2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, -2,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 2, 0, 0, 0, -13, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, -2, -2,
    2, 0, -2, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, -15, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, -2, 0, 0,
    -2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    -2, 0, 0, -2, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 40,
    .right_class_cnt     = 35,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 2,
    .bpp = 2,
    .kern_classes = 1,
    .bitmap_format = 2,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_font_roboto_bl_16 = {
#else
lv_font_t lv_font_roboto_bl_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 19,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_FONT_ROBOTO_BL_16*/

