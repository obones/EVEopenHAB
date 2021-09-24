#ifndef RELOAD_COLOR_PNG
#define RELOAD_COLOR_PNG

#include <Arduino.h>
#include <EVE.h>

const uint8_t reload_color_png_width = 25;
const uint8_t reload_color_png_height = 25;
const uint8_t reload_color_png_format = EVE_RGB565;
const uint8_t reload_color_png_bytes_per_pixel = 2;
const uint32_t reload_color_png_byte_count = reload_color_png_bytes_per_pixel * reload_color_png_width * (uint32_t)reload_color_png_height;

const uint8_t reload_color_png[699] PROGMEM = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x19, 0x00, 0x00, 0x00, 0x19,
  0x08, 0x02, 0x00, 0x00, 0x00, 0x4b, 0x8b, 0x12, 0x34, 0x00, 0x00, 0x00,
  0x07, 0x74, 0x49, 0x4d, 0x45, 0x07, 0xe5, 0x09, 0x18, 0x0f, 0x27, 0x2f,
  0x68, 0xa8, 0xf5, 0x91, 0x00, 0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73,
  0x00, 0x00, 0x0b, 0x12, 0x00, 0x00, 0x0b, 0x12, 0x01, 0xd2, 0xdd, 0x7e,
  0xfc, 0x00, 0x00, 0x00, 0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1,
  0x8f, 0x0b, 0xfc, 0x61, 0x05, 0x00, 0x00, 0x02, 0x4a, 0x49, 0x44, 0x41,
  0x54, 0x78, 0xda, 0xad, 0x95, 0xcf, 0x8b, 0x52, 0x51, 0x14, 0xc7, 0x5d,
  0x8c, 0x8b, 0x16, 0x2d, 0xe6, 0x1f, 0x98, 0x5a, 0xf4, 0x17, 0xd4, 0x32,
  0x5a, 0xd5, 0xa6, 0xd0, 0x04, 0xc3, 0x45, 0x1b, 0x85, 0x5a, 0xcd, 0xa0,
  0x2d, 0xe6, 0x19, 0xe9, 0x42, 0x50, 0x70, 0x21, 0x54, 0x58, 0xe8, 0xd0,
  0x80, 0x43, 0xd0, 0xa6, 0x85, 0x93, 0x42, 0x2d, 0x52, 0x08, 0x0a, 0x34,
  0x94, 0x5c, 0x38, 0x90, 0x4a, 0x2e, 0x0a, 0xfc, 0xc1, 0x8c, 0x0e, 0x2a,
  0x4c, 0xce, 0x58, 0x8c, 0xe3, 0x7b, 0xd3, 0x27, 0x7b, 0xa8, 0xf3, 0xb0,
  0xe9, 0x26, 0x1e, 0x1e, 0x72, 0xef, 0x39, 0xdf, 0xf3, 0x79, 0xe7, 0x9e,
  0xfb, 0xee, 0x55, 0x77, 0x3c, 0x3f, 0xd3, 0x4d, 0xf5, 0xf6, 0xfb, 0xfd,
  0x6c, 0x36, 0x1b, 0x0e, 0x87, 0x25, 0x49, 0xba, 0x33, 0x34, 0x06, 0x4c,
  0x71, 0x12, 0x12, 0x65, 0xc9, 0xb2, 0x9c, 0x4c, 0x26, 0x6d, 0x36, 0x9b,
  0xd1, 0x68, 0xb4, 0x5a, 0xad, 0x7e, 0xbf, 0xff, 0xd9, 0xd0, 0x18, 0x30,
  0xc5, 0x49, 0x08, 0x01, 0xb2, 0x7f, 0xb0, 0xba, 0xdd, 0xae, 0xc7, 0xe3,
  0x31, 0x18, 0x0c, 0x5e, 0xaf, 0xb7, 0x50, 0x28, 0x28, 0x8a, 0x32, 0x19,
  0x65, 0x5a, 0x2c, 0x16, 0x09, 0x21, 0x40, 0x86, 0xf8, 0xaf, 0x2c, 0x62,
  0x76, 0xbb, 0xdd, 0x62, 0xb1, 0xa4, 0x52, 0x29, 0x0d, 0x45, 0x43, 0x44,
  0x80, 0x0c, 0xb1, 0x06, 0xa7, 0x1b, 0x2d, 0x8d, 0x57, 0xa1, 0x28, 0x97,
  0xcb, 0x22, 0x6d, 0x46, 0x86, 0x98, 0x94, 0xc9, 0xc5, 0xaa, 0xac, 0x44,
  0x22, 0x41, 0x2f, 0xd2, 0xe9, 0xb4, 0xf8, 0xae, 0x21, 0x26, 0x85, 0xc4,
  0x5c, 0x2e, 0xe7, 0x72, 0xb9, 0xa8, 0x57, 0xf7, 0x67, 0xd7, 0xe8, 0xa8,
  0xcf, 0xe7, 0x3b, 0x65, 0x69, 0x1a, 0xa3, 0x71, 0xf9, 0x7c, 0x9e, 0x14,
  0x12, 0xdd, 0x6e, 0xb7, 0xc3, 0xe1, 0x50, 0x59, 0x99, 0x4c, 0x86, 0x37,
  0x94, 0x4a, 0x25, 0xf1, 0xa2, 0x42, 0xa1, 0x10, 0x29, 0x20, 0xf8, 0x65,
  0x2b, 0xe2, 0xf1, 0xb8, 0xba, 0x46, 0x02, 0xe0, 0xc5, 0x8b, 0xc2, 0x06,
  0x83, 0x41, 0x2c, 0x16, 0x33, 0x9b, 0xcd, 0xb0, 0x4c, 0x26, 0x53, 0xa7,
  0xd3, 0x51, 0x59, 0xc1, 0x60, 0x90, 0xef, 0x50, 0x1c, 0x34, 0xb2, 0x5a,
  0xad, 0xe6, 0x74, 0x3a, 0x03, 0x81, 0xc0, 0xb8, 0xf7, 0xca, 0xd0, 0x66,
  0x60, 0x69, 0x72, 0xe7, 0xcd, 0xba, 0xfd, 0x62, 0xf7, 0xca, 0xd3, 0x9d,
  0x2f, 0xcd, 0xc3, 0x19, 0x58, 0x2b, 0xd1, 0xd6, 0xdd, 0x97, 0x2d, 0x95,
  0xd5, 0xf8, 0x7e, 0x74, 0xe6, 0x7e, 0x55, 0x2f, 0x55, 0xcf, 0x3e, 0xa8,
  0x3e, 0x7e, 0xbf, 0x37, 0x90, 0xff, 0xa3, 0x40, 0x2a, 0x3a, 0xe7, 0xab,
  0x2f, 0x47, 0xdb, 0x2a, 0x2b, 0xf8, 0x61, 0x6f, 0x41, 0xfa, 0xcd, 0xba,
  0xf4, 0x68, 0x5b, 0x2f, 0x55, 0x96, 0xa3, 0x2d, 0x71, 0xd6, 0xc7, 0x6f,
  0x3f, 0xc9, 0x7d, 0xfd, 0xf9, 0x40, 0x65, 0x81, 0xb8, 0xb6, 0xd6, 0x00,
  0x6f, 0x8a, 0x34, 0xdf, 0x95, 0x7b, 0x84, 0xc5, 0x8b, 0x22, 0x85, 0xc4,
  0xc3, 0x23, 0xf5, 0x18, 0xe9, 0xae, 0xae, 0x35, 0xde, 0x96, 0x7a, 0x91,
  0x4c, 0x97, 0xa2, 0x5e, 0x6d, 0xed, 0x8b, 0x17, 0x85, 0x58, 0xbf, 0x5a,
  0xd9, 0xc8, 0x8c, 0x8f, 0xf7, 0xe8, 0x6c, 0x2b, 0xd7, 0xd7, 0x9b, 0x8b,
  0xee, 0xda, 0xa7, 0x8a, 0x50, 0x5d, 0xc8, 0x10, 0x93, 0x22, 0x4f, 0xf4,
  0x77, 0x7c, 0xe7, 0x74, 0x7a, 0x83, 0x8b, 0x0f, 0xb7, 0x17, 0xdd, 0xd5,
  0xcd, 0xad, 0xfd, 0xd3, 0xef, 0x1c, 0x04, 0xc8, 0x10, 0x93, 0x32, 0x19,
  0x3a, 0x71, 0x17, 0x12, 0xbb, 0xb1, 0xde, 0x5c, 0x58, 0xad, 0xdc, 0x8c,
  0x34, 0xd3, 0x5f, 0x7f, 0xc8, 0x27, 0x89, 0x4c, 0x71, 0x12, 0x42, 0x40,
  0x45, 0x1a, 0xd0, 0xf1, 0xb4, 0x3b, 0x5a, 0xd9, 0xc8, 0x76, 0xcf, 0xfb,
  0xea, 0xec, 0xec, 0x92, 0xb7, 0x7e, 0xeb, 0xf9, 0xee, 0xbd, 0x58, 0x9b,
  0x87, 0xc1, 0x92, 0xb7, 0x86, 0x93, 0x10, 0x02, 0x79, 0xda, 0xa7, 0x33,
  0xfd, 0xbf, 0x83, 0xad, 0x79, 0x53, 0x38, 0x58, 0xd9, 0x6c, 0x5f, 0x7e,
  0xb2, 0x73, 0xc1, 0x5f, 0xe7, 0x61, 0xc0, 0x14, 0xe7, 0x68, 0xd7, 0x44,
  0x59, 0xb3, 0xd9, 0x3c, 0x59, 0xbf, 0x00, 0xc4, 0x73, 0x89, 0x3c, 0xd5,
  0x54, 0xe7, 0x00, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae,
  0x42, 0x60, 0x82
};

#endif