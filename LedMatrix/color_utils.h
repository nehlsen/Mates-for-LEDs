#ifndef MATRIX_COLOR_UTILS_H
#define MATRIX_COLOR_UTILS_H

#include <cstdint>

// https://github.com/marcmerlin/Framebuffer_GFX

// 16 bit to 24 bit or rgb565 to rgb888
uint32_t color16to24(uint16_t color);

// 24 bit to 16 bit or rgb888 to rgb565
uint16_t color24to16(uint8_t r, uint8_t g, uint8_t b);

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

#endif //MATRIX_COLOR_UTILS_H
