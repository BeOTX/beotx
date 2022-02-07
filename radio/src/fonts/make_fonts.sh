#!/bin/bash

function make_font() {
  local name=$1
  local ttf=$2
  local size=$3
  lv_font_conv --no-prefilter --bpp 4 --size ${size} --font ${ttf} -r 0x20-0x7F,0xB0,0x2022,0xDF,0xE4,0xF6,0xFC,0xC4,0xD6,0xDC --font EdgeTX_extra.ttf -r 0x80-0x94 --font ../thirdparty/lvgl/scripts/built_in_font/FontAwesome5-Solid+Brands+Regular.woff -r 61441,61448,61451,61452,61452,61453,61457,61459,61461,61465,61468,61473,61478,61479,61480,61502,61507,61512,61515,61516,61517,61521,61522,61523,61524,61543,61544,61550,61552,61553,61556,61559,61560,61561,61563,61587,61589,61636,61637,61639,61641,61664,61671,61674,61683,61724,61732,61787,61931,62016,62017,62018,62019,62020,62087,62099,62212,62189,62810,63426,63650 --format lvgl -o lv_font_${name}_${size}.c --force-fast-kern-format --lv-include ../thirdparty/lvgl/src/lvgl.h
}

make_font "roboto" "Roboto/Roboto-Regular.ttf" 9 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 13 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 14 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 15  
make_font "roboto" "Roboto/Roboto-Regular.ttf" 16 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 17 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 24 
make_font "roboto" "Roboto/Roboto-Regular.ttf" 64 
make_font "roboto_bold" "Roboto/Roboto-Bold.ttf" 16 
make_font "roboto_bold" "Roboto/Roboto-Bold.ttf" 17 
make_font "roboto_bold" "Roboto/Roboto-Bold.ttf" 16 
make_font "roboto_bold" "Roboto/Roboto-Bold.ttf" 32 
make_font "roboto_bold" "Roboto/Roboto-Bold.ttf" 64 

