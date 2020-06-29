#ifndef MATRIX_LEDMATRIX_H
#define MATRIX_LEDMATRIX_H

#include <FastLED.h>
#include "PixelLocator.h"
#include "MatrixOptions.h"

class LedMatrix
{
public:
    LedMatrix(CFastLED &fastLed, uint8_t width, uint8_t height, uint8_t options= MatrixOptions::DefaultOptions);

    uint8_t getWidth() const;
    uint8_t getHeight() const;

    CRGB& pixel(uint8_t x, uint8_t y);
    void drawPixel(uint8_t x, uint8_t y, const CRGB& color);

//    operator=(Pixels) render mode: overwrite
//    operator+=(Pixels) render mode: add
//    operator/=(Pixels) render mode: average

    void setBrightness(uint8_t scale);
    uint8_t getBrightness();

    void fade(uint8_t scaledown);
    void show();
    void clear(bool forceWrite = true);

protected:
    CFastLED &m_fastLed;
    const PixelLocator m_pixelLocator;
    const uint8_t m_width;
    const uint8_t m_height;

    CRGB m_outOfBounds;
};

#endif //MATRIX_LEDMATRIX_H
