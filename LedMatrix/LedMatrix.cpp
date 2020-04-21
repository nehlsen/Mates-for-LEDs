#include "LedMatrix.h"

LedMatrix::LedMatrix(CLEDController &fastLedController, uint8_t width, uint8_t height, uint8_t options) :
    m_fastLedController(fastLedController), m_pixelLocator(width, height, options),
    m_width(width), m_height(height)
{
}

uint8_t LedMatrix::getWidth() const
{
    return m_width;
}

uint8_t LedMatrix::getHeight() const
{
    return m_height;
}

CRGB& LedMatrix::pixel(uint8_t x, uint8_t y)
{
    uint16_t index = m_pixelLocator.xyToIndex(x, y);
    if (index >= m_fastLedController.size()) {
        return m_outOfBounds;
    }

    return m_fastLedController[index];
}

void LedMatrix::drawPixel(uint8_t x, uint8_t y, const CRGB &color)
{
    pixel(x, y) = color;
}

void LedMatrix::show()
{
    FastLED.show();
}
