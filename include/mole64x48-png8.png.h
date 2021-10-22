#ifndef MOLE_PNG
#define MOLE_PNG

#include <Arduino.h>
#include <EVE.h>

const uint8_t mole_png_width = 64;
const uint8_t mole_png_height = 48;
const uint8_t mole_png_format = EVE_PALETTED4444;
const uint8_t mole_png_bytes_per_pixel = 1;

unsigned char mole_png[1730] PROGMEM = {
  0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a, 0x00, 0x00, 0x00, 0x0d,
  0x49, 0x48, 0x44, 0x52, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x30,
  0x08, 0x03, 0x00, 0x00, 0x00, 0x96, 0x95, 0x8c, 0x2d, 0x00, 0x00, 0x00,
  0x04, 0x67, 0x41, 0x4d, 0x41, 0x00, 0x00, 0xb1, 0x8f, 0x0b, 0xfc, 0x61,
  0x05, 0x00, 0x00, 0x00, 0x20, 0x63, 0x48, 0x52, 0x4d, 0x00, 0x00, 0x7a,
  0x26, 0x00, 0x00, 0x80, 0x84, 0x00, 0x00, 0xfa, 0x00, 0x00, 0x00, 0x80,
  0xe8, 0x00, 0x00, 0x75, 0x30, 0x00, 0x00, 0xea, 0x60, 0x00, 0x00, 0x3a,
  0x98, 0x00, 0x00, 0x17, 0x70, 0x9c, 0xba, 0x51, 0x3c, 0x00, 0x00, 0x01,
  0xb0, 0x50, 0x4c, 0x54, 0x45, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0x11,
  0x11, 0x11, 0x22, 0x22, 0x22, 0x33, 0x33, 0x33, 0x33, 0x22, 0x33, 0x88,
  0x55, 0x66, 0xff, 0x99, 0xbb, 0x44, 0x33, 0x33, 0x44, 0x44, 0x44, 0x66,
  0x44, 0x55, 0xee, 0x99, 0xbb, 0x44, 0x22, 0x33, 0xbb, 0x77, 0x99, 0xff,
  0x99, 0xcc, 0xbb, 0x66, 0x88, 0xcc, 0xcc, 0xcc, 0xff, 0xff, 0xff, 0xaa,
  0xaa, 0xaa, 0x77, 0x77, 0x77, 0xee, 0xee, 0xee, 0x55, 0x55, 0x55, 0x11,
  0x22, 0x22, 0xdd, 0x77, 0x99, 0xff, 0xaa, 0xcc, 0x77, 0x55, 0x66, 0xee,
  0x77, 0xaa, 0x66, 0x33, 0x44, 0x99, 0x99, 0x99, 0x66, 0x66, 0x66, 0x88,
  0x44, 0x66, 0xff, 0x88, 0xaa, 0xff, 0xaa, 0xbb, 0x55, 0x33, 0x44, 0x11,
  0x00, 0x11, 0xcc, 0x77, 0x99, 0xff, 0x88, 0xbb, 0x99, 0x44, 0x66, 0xbb,
  0xbb, 0xbb, 0xdd, 0xdd, 0xdd, 0x33, 0x22, 0x22, 0xdd, 0x66, 0x88, 0x77,
  0x44, 0x55, 0x55, 0x33, 0x33, 0x88, 0x88, 0x88, 0xdd, 0xee, 0xee, 0x22,
  0x33, 0x33, 0xcc, 0xaa, 0x88, 0x33, 0x33, 0x22, 0x77, 0x55, 0x44, 0x88,
  0x66, 0x55, 0xbb, 0x99, 0x77, 0xff, 0xee, 0xcc, 0xdd, 0xaa, 0x88, 0xff,
  0xcc, 0x99, 0x99, 0x77, 0x55, 0xff, 0xdd, 0xbb, 0xff, 0xcc, 0xaa, 0x88,
  0x77, 0x55, 0x44, 0x33, 0x22, 0xff, 0xbb, 0x99, 0xff, 0xdd, 0xaa, 0xaa,
  0x77, 0x55, 0x66, 0x55, 0x44, 0xee, 0xaa, 0x77, 0x55, 0x44, 0x33, 0xaa,
  0x88, 0x77, 0xaa, 0x77, 0x66, 0x33, 0x22, 0x11, 0x66, 0x44, 0x33, 0x22,
  0x11, 0x00, 0x55, 0x44, 0x44, 0x22, 0x11, 0x11, 0x66, 0x55, 0x33, 0x88,
  0x66, 0x44, 0x77, 0x55, 0x33, 0x55, 0x33, 0x22, 0xff, 0xbb, 0x88, 0x22,
  0x22, 0x11, 0x88, 0x99, 0x99, 0xaa, 0xbb, 0xbb, 0xff, 0xcc, 0x88, 0xdd,
  0x99, 0x66, 0x33, 0x33, 0x44, 0x77, 0x77, 0x88, 0x66, 0x66, 0x77, 0x44,
  0x44, 0x55, 0xcc, 0xcc, 0xdd, 0xaa, 0x88, 0x66, 0x77, 0x66, 0x55, 0xdd,
  0xaa, 0x77, 0xbb, 0x88, 0x55, 0x77, 0x88, 0x99, 0x55, 0x55, 0x66, 0x66,
  0x55, 0x55, 0x33, 0x22, 0x00, 0xaa, 0xaa, 0xbb, 0x55, 0x66, 0x66, 0x77,
  0x77, 0x66, 0x88, 0x77, 0x77, 0x88, 0x55, 0x33, 0x44, 0x55, 0x55, 0x88,
  0x88, 0x99, 0x55, 0x44, 0x55, 0x99, 0x77, 0x77, 0x99, 0x77, 0x66, 0xbb,
  0x88, 0x66, 0x99, 0x99, 0xaa, 0x55, 0x66, 0x77, 0x22, 0x11, 0x22, 0xcc,
  0x99, 0x77, 0x44, 0x22, 0x00, 0x99, 0x88, 0x88, 0x77, 0x77, 0x99, 0xff,
  0xbb, 0x77, 0xee, 0xbb, 0x88, 0xcc, 0x99, 0x66, 0x22, 0x22, 0x00, 0x11,
  0x00, 0x00, 0x66, 0x44, 0x11, 0x66, 0x44, 0x00, 0x77, 0x88, 0x88, 0x55,
  0x33, 0x11, 0x88, 0x44, 0x22, 0xbb, 0xbb, 0xcc, 0x77, 0x66, 0x33, 0x77,
  0x55, 0x11, 0x44, 0x33, 0x00, 0x99, 0x66, 0x55, 0x77, 0x55, 0x22, 0x66,
  0x44, 0x22, 0x88, 0x55, 0x44, 0x44, 0x33, 0x44, 0x77, 0x44, 0x11, 0x77,
  0x44, 0x00, 0x55, 0x33, 0x00, 0x77, 0x55, 0x00, 0x22, 0x22, 0x33, 0xaa,
  0x99, 0x88, 0x99, 0x88, 0x99, 0x99, 0x66, 0x44, 0xbb, 0x77, 0x44, 0x55,
  0x44, 0x00, 0x44, 0x33, 0x11, 0x94, 0x5d, 0x62, 0xf4, 0x00, 0x00, 0x00,
  0x01, 0x74, 0x52, 0x4e, 0x53, 0x00, 0x40, 0xe6, 0xd8, 0x66, 0x00, 0x00,
  0x00, 0x01, 0x62, 0x4b, 0x47, 0x44, 0x00, 0x88, 0x05, 0x1d, 0x48, 0x00,
  0x00, 0x00, 0x09, 0x70, 0x48, 0x59, 0x73, 0x00, 0x00, 0x0e, 0xc3, 0x00,
  0x00, 0x0e, 0xc3, 0x01, 0xc7, 0x6f, 0xa8, 0x64, 0x00, 0x00, 0x00, 0x07,
  0x74, 0x49, 0x4d, 0x45, 0x07, 0xe5, 0x0a, 0x05, 0x0f, 0x39, 0x32, 0x3a,
  0x3c, 0x53, 0x05, 0x00, 0x00, 0x03, 0xed, 0x49, 0x44, 0x41, 0x54, 0x48,
  0xc7, 0x9d, 0x94, 0x8d, 0x5f, 0xdb, 0x44, 0x18, 0xc7, 0x9b, 0xbb, 0xd3,
  0x11, 0xdf, 0xd6, 0x34, 0xe9, 0x7c, 0x6b, 0x7c, 0x5f, 0x83, 0xae, 0xdb,
  0x78, 0x19, 0x01, 0xd6, 0x41, 0xc1, 0x95, 0x30, 0x05, 0xa6, 0xd8, 0x17,
  0x98, 0x6e, 0x04, 0x75, 0x56, 0xa5, 0xca, 0xe9, 0x10, 0x39, 0x37, 0xf5,
  0x9c, 0xd3, 0x1e, 0xbe, 0x50, 0xff, 0x65, 0x9f, 0xbb, 0xa6, 0x69, 0x3a,
  0x56, 0x9a, 0xec, 0xf7, 0x69, 0x3f, 0x49, 0xdb, 0xfc, 0xbe, 0xf7, 0x3c,
  0xbf, 0x7b, 0x7a, 0xa9, 0xd4, 0x20, 0x69, 0x5d, 0xa5, 0x1e, 0x4b, 0x9a,
  0x86, 0x30, 0x26, 0x84, 0x60, 0x8c, 0xd1, 0x63, 0x30, 0x34, 0x4d, 0x9a,
  0x43, 0xa1, 0xf8, 0x84, 0xce, 0x62, 0x1a, 0x22, 0xfd, 0xc2, 0x5a, 0xef,
  0xc7, 0x93, 0x85, 0x9e, 0x80, 0xa7, 0x94, 0x1f, 0xa3, 0x4e, 0x11, 0x18,
  0xc9, 0x1b, 0x49, 0x80, 0xa6, 0x86, 0x12, 0xb4, 0x27, 0x4f, 0x8d, 0x40,
  0x6c, 0xb2, 0x68, 0xac, 0x63, 0xe8, 0x03, 0x6b, 0x48, 0x27, 0x12, 0x88,
  0x21, 0x94, 0xa7, 0x9e, 0x7e, 0x66, 0x28, 0xe0, 0xd9, 0xe7, 0x4e, 0xcb,
  0xa5, 0x11, 0x4e, 0x1b, 0x86, 0x91, 0x41, 0x48, 0x33, 0xe1, 0x6a, 0x65,
  0x81, 0x80, 0xce, 0x90, 0xe7, 0x5f, 0x78, 0x31, 0x46, 0x05, 0x2f, 0xbd,
  0x2c, 0xfd, 0x86, 0x52, 0x5a, 0xcb, 0x75, 0x6e, 0x6c, 0xd9, 0xc5, 0x2b,
  0xaf, 0xbe, 0xf6, 0xfa, 0xd0, 0x0c, 0xde, 0x78, 0xf3, 0xad, 0xb3, 0x98,
  0x68, 0x79, 0x23, 0x20, 0x04, 0x57, 0x87, 0x60, 0x32, 0xfa, 0xf6, 0xa9,
  0xd3, 0xc3, 0x53, 0xd4, 0xd0, 0x3b, 0x50, 0x00, 0x31, 0xfa, 0x65, 0x59,
  0x26, 0xc4, 0x71, 0xee, 0x6c, 0xac, 0xdd, 0x84, 0xe4, 0x34, 0x5b, 0xd9,
  0x72, 0x98, 0x58, 0x39, 0xa4, 0x2b, 0x40, 0x06, 0x7a, 0x88, 0x39, 0x4f,
  0x10, 0xb9, 0x4a, 0x0e, 0xca, 0xce, 0x6a, 0xba, 0xae, 0x6b, 0x05, 0xc3,
  0x72, 0xac, 0xbc, 0x04, 0xc4, 0xf2, 0xc3, 0x28, 0x10, 0xa4, 0x2a, 0x70,
  0x60, 0x84, 0x6d, 0x78, 0xe7, 0x0c, 0xc7, 0x91, 0x15, 0x0c, 0x1f, 0x82,
  0x10, 0x80, 0x75, 0x28, 0x1a, 0xca, 0x26, 0xa6, 0x91, 0xd7, 0x4d, 0xb8,
  0x73, 0x54, 0x06, 0xf1, 0x01, 0x04, 0x67, 0xc0, 0xe3, 0x58, 0x46, 0xda,
  0x2e, 0x58, 0x86, 0xbc, 0x73, 0xc2, 0x71, 0x8e, 0x13, 0x02, 0x3c, 0x4b,
  0x1c, 0x58, 0xd7, 0xc8, 0xc1, 0x50, 0x22, 0xe9, 0xb7, 0x6c, 0x9c, 0x0c,
  0x00, 0x84, 0x8c, 0x75, 0xbe, 0x80, 0xe4, 0x69, 0x40, 0xf2, 0x56, 0x3a,
  0x8b, 0x13, 0x56, 0x20, 0x8f, 0x81, 0x0b, 0xe4, 0xe2, 0x98, 0x04, 0x8c,
  0x4f, 0xe0, 0x33, 0x98, 0x24, 0x06, 0x10, 0x3c, 0x32, 0x79, 0x69, 0x42,
  0x02, 0xa6, 0xdc, 0xe9, 0x73, 0x38, 0xd1, 0xa1, 0xd0, 0xa9, 0x60, 0x72,
  0x66, 0x66, 0x76, 0xf6, 0xf2, 0x68, 0x71, 0xd2, 0xbd, 0xe2, 0xce, 0xcd,
  0xe3, 0xa4, 0x00, 0x5c, 0x9a, 0x91, 0x00, 0x10, 0xf8, 0xdd, 0xe9, 0x85,
  0x45, 0x9c, 0x04, 0x20, 0x13, 0x2f, 0x4d, 0xe2, 0x77, 0x67, 0xe7, 0x40,
  0xb3, 0x57, 0xae, 0x96, 0xcb, 0x0b, 0x4b, 0x12, 0xe0, 0x25, 0x01, 0x2c,
  0xcf, 0x5c, 0x1d, 0xbb, 0x56, 0x7c, 0xef, 0xfd, 0x95, 0xd5, 0x6b, 0xe5,
  0xf9, 0x35, 0x17, 0x00, 0x18, 0x5d, 0xbf, 0x9e, 0x00, 0xa0, 0x5f, 0xbc,
  0x34, 0x57, 0xfa, 0xa0, 0x40, 0xec, 0x0f, 0xed, 0x05, 0x77, 0xfd, 0xa3,
  0x51, 0x8c, 0x2b, 0x76, 0xb5, 0x56, 0x8f, 0x55, 0x86, 0x3c, 0xc8, 0xcc,
  0x0d, 0x7b, 0xd3, 0xbd, 0x61, 0x19, 0xa6, 0x63, 0x14, 0x3e, 0x5e, 0xfb,
  0x44, 0xbf, 0x59, 0xb9, 0x70, 0xab, 0x56, 0xd3, 0xb7, 0xf0, 0x8d, 0x55,
  0x3f, 0x06, 0x00, 0xeb, 0x1b, 0xe9, 0xed, 0x4f, 0xb7, 0x96, 0xcf, 0x1b,
  0x9f, 0xa5, 0x8d, 0xcf, 0x6f, 0x97, 0xbe, 0xa8, 0x36, 0x74, 0xf2, 0x65,
  0xfd, 0xab, 0xd2, 0xd7, 0xe3, 0x97, 0x77, 0xbc, 0xa1, 0x04, 0x00, 0x64,
  0x36, 0xf2, 0xb9, 0x66, 0xa3, 0xae, 0x2a, 0x30, 0xbf, 0x69, 0x36, 0xaa,
  0x8d, 0x5b, 0xdf, 0x92, 0x92, 0xbb, 0xbc, 0xbb, 0xb9, 0x33, 0xe5, 0x51,
  0xff, 0x24, 0x04, 0x92, 0x69, 0x65, 0x9d, 0xf4, 0x76, 0x23, 0xd7, 0xac,
  0xdb, 0xe6, 0xd8, 0xa2, 0x5d, 0x9c, 0xf8, 0xae, 0xf1, 0x7d, 0xb5, 0x51,
  0x5f, 0xbd, 0xb3, 0xb7, 0xb2, 0xbe, 0xf3, 0xc3, 0xde, 0xbe, 0x0f, 0x1a,
  0x94, 0xc4, 0x8f, 0xa4, 0x52, 0xab, 0x56, 0xb3, 0x95, 0xe6, 0x46, 0x33,
  0x07, 0x2a, 0x1c, 0x30, 0x06, 0x2f, 0xb6, 0x62, 0xde, 0x6c, 0xfc, 0x74,
  0x77, 0x6d, 0x93, 0xde, 0xd9, 0xb9, 0xb7, 0x56, 0xf6, 0xfd, 0xc1, 0x88,
  0x4d, 0x5c, 0xd2, 0xb7, 0x6a, 0x76, 0x85, 0xfc, 0x0c, 0x80, 0x66, 0xf3,
  0x17, 0xd6, 0x95, 0x69, 0xfe, 0xca, 0x7f, 0xbb, 0xcf, 0x7f, 0x7f, 0xe0,
  0xdf, 0xf5, 0xbb, 0x7a, 0x04, 0xa2, 0xb8, 0x57, 0x9c, 0x1a, 0xd9, 0xcd,
  0xd6, 0xff, 0x20, 0xdb, 0x60, 0x2f, 0x14, 0x42, 0x3f, 0xfb, 0xb3, 0xc5,
  0x5a, 0x54, 0x1c, 0x32, 0x7e, 0xc8, 0x42, 0x80, 0xbf, 0x7f, 0x0c, 0x30,
  0xee, 0x8e, 0xbb, 0x8b, 0x53, 0xbb, 0xe4, 0xaf, 0xf2, 0xdf, 0xcd, 0x7f,
  0x7a, 0xcb, 0x4b, 0xb5, 0x3a, 0x3a, 0x6c, 0xb5, 0x7c, 0x5f, 0x08, 0xde,
  0x21, 0xf4, 0xbb, 0x19, 0xe3, 0xd3, 0xeb, 0xff, 0xba, 0x47, 0xd3, 0xee,
  0x91, 0xc7, 0x0e, 0xee, 0x1f, 0x3c, 0xec, 0xed, 0x8a, 0x73, 0xc1, 0x39,
  0x55, 0x15, 0xec, 0x87, 0x5d, 0xf8, 0x34, 0x25, 0x18, 0xa3, 0xf3, 0x47,
  0x4b, 0xee, 0xbd, 0xa2, 0x7b, 0x5b, 0xf4, 0x2d, 0x2e, 0x40, 0x11, 0x0a,
  0x03, 0x7b, 0x00, 0xf0, 0xbc, 0x80, 0x20, 0x0d, 0xa2, 0xcd, 0x44, 0xd9,
  0xff, 0x6f, 0x89, 0xf2, 0x07, 0xfc, 0x61, 0x3b, 0xd4, 0x2c, 0x7a, 0x04,
  0xca, 0xb9, 0x6a, 0xc1, 0xf3, 0x82, 0x20, 0x85, 0x68, 0xcb, 0x67, 0xda,
  0x6d, 0x06, 0x0c, 0x30, 0xfb, 0xec, 0x38, 0x40, 0xf0, 0x60, 0x79, 0xe8,
  0xa8, 0xbb, 0x09, 0x14, 0x5a, 0xe1, 0x9e, 0xf4, 0x8b, 0x8e, 0x5f, 0x11,
  0x8e, 0x09, 0x16, 0xef, 0x01, 0xd4, 0x5d, 0x77, 0x0f, 0x44, 0xb0, 0x99,
  0xf2, 0x3b, 0xe8, 0x49, 0xb0, 0x76, 0xbb, 0xd7, 0x72, 0x1f, 0x41, 0x8a,
  0x85, 0x00, 0xda, 0xad, 0x20, 0xb8, 0xa6, 0xfc, 0xb6, 0xfa, 0x8e, 0x47,
  0x01, 0x51, 0x42, 0x2b, 0xb2, 0x13, 0x8c, 0x53, 0x1a, 0xce, 0x11, 0xed,
  0xed, 0xa5, 0xbc, 0xd2, 0xb6, 0xe8, 0x10, 0x54, 0x99, 0xc7, 0x3a, 0x09,
  0x08, 0x22, 0x32, 0x46, 0x7e, 0x64, 0x18, 0x54, 0x05, 0x20, 0x49, 0xe0,
  0x27, 0x01, 0x78, 0x0f, 0x10, 0xf4, 0xd0, 0x1b, 0x68, 0x1f, 0x9c, 0x4c,
  0xbe, 0xa0, 0x63, 0x31, 0x00, 0x10, 0x99, 0x63, 0x35, 0xca, 0x8f, 0xfa,
  0x47, 0x45, 0xbc, 0xd1, 0x2c, 0x5a, 0x2c, 0x1a, 0xa0, 0x9a, 0x82, 0x81,
  0x87, 0x1b, 0x0d, 0x6c, 0xf2, 0xf1, 0xb0, 0x97, 0x96, 0x32, 0x53, 0x5f,
  0x86, 0x48, 0xbd, 0xd4, 0xb0, 0x93, 0x91, 0x51, 0xf8, 0x6b, 0x28, 0x47,
  0x58, 0x80, 0x5a, 0x9c, 0x72, 0xc8, 0xcc, 0x8b, 0x77, 0xbc, 0x0b, 0x15,
  0x18, 0xed, 0x6e, 0xa4, 0x50, 0xfb, 0x17, 0xd3, 0xdb, 0x15, 0xc4, 0x2c,
  0x82, 0x51, 0xf6, 0xd4, 0xa7, 0x64, 0xf6, 0x20, 0x0f, 0xb9, 0x29, 0x27,
  0x9e, 0xc3, 0xff, 0x03, 0x90, 0xd7, 0xe7, 0x2d, 0xb0, 0xa9, 0x7c, 0xa7,
  0x00, 0x00, 0x00, 0x25, 0x74, 0x45, 0x58, 0x74, 0x64, 0x61, 0x74, 0x65,
  0x3a, 0x63, 0x72, 0x65, 0x61, 0x74, 0x65, 0x00, 0x32, 0x30, 0x32, 0x31,
  0x2d, 0x31, 0x30, 0x2d, 0x30, 0x35, 0x54, 0x31, 0x35, 0x3a, 0x35, 0x34,
  0x3a, 0x33, 0x37, 0x2b, 0x30, 0x30, 0x3a, 0x30, 0x30, 0xb7, 0x3e, 0x83,
  0x52, 0x00, 0x00, 0x00, 0x25, 0x74, 0x45, 0x58, 0x74, 0x64, 0x61, 0x74,
  0x65, 0x3a, 0x6d, 0x6f, 0x64, 0x69, 0x66, 0x79, 0x00, 0x32, 0x30, 0x32,
  0x31, 0x2d, 0x31, 0x30, 0x2d, 0x30, 0x35, 0x54, 0x31, 0x35, 0x3a, 0x35,
  0x32, 0x3a, 0x31, 0x31, 0x2b, 0x30, 0x30, 0x3a, 0x30, 0x30, 0xea, 0x88,
  0x79, 0xee, 0x00, 0x00, 0x00, 0x00, 0x49, 0x45, 0x4e, 0x44, 0xae, 0x42,
  0x60, 0x82
};

#endif