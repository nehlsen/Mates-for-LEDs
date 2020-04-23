#ifndef MATRIX_COLOR_UTILS_H
#define MATRIX_COLOR_UTILS_H

#include <stdint.h>

// https://github.com/marcmerlin/Framebuffer_GFX

// 16 bit to 24 bit or rgb565 to rgb888
uint32_t color16to24(uint16_t color);

// 24 bit to 16 bit or rgb888 to rgb565
uint16_t color24to16(uint8_t r, uint8_t g, uint8_t b);

#endif //MATRIX_COLOR_UTILS_H
