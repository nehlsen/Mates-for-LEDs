#ifndef LEDWALL_LEDMATRIX_H
#define LEDWALL_LEDMATRIX_H

#include <FastLED.h>
#include "PixelLocator.h"
#include "MatrixOptions.h"

class LedMatrix
{
public:
    LedMatrix(CLEDController& fastLedController, uint8_t width, uint8_t height, uint8_t options= MatrixOptions::DefaultOptions);

    uint8_t getWidth() const;
    uint8_t getHeight() const;

    CRGB& pixel(uint8_t x, uint8_t y);

    void drawPixel(uint8_t x, uint8_t y, const CRGB& color);

    static void show();

protected:
    CLEDController &m_fastLedController;
    const PixelLocator m_pixelLocator;
    const uint8_t m_width;
    const uint8_t m_height;

    CRGB m_outOfBounds;
};

#endif //LEDWALL_LEDMATRIX_H
