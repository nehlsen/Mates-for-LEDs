#include "LedMatrix.h"

LedMatrix::LedMatrix(CFastLED &fastLed, uint8_t width, uint8_t height, uint8_t options) :
    m_fastLed(fastLed), m_pixelLocator(width, height, options),
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
    if (index >= m_fastLed.size()) {
        return m_outOfBounds;
    }

    return m_fastLed.leds()[index];
}

void LedMatrix::drawPixel(uint8_t x, uint8_t y, const CRGB &color)
{
    pixel(x, y) = color;
}

void LedMatrix::fade(uint8_t scaledown)
{
    for (int i = 0; i < m_fastLed.size(); i++) {
        m_fastLed.leds()[i].nscale8(scaledown);
    }
}

void LedMatrix::show()
{
    m_fastLed.show();
}

void LedMatrix::clear(bool forceWrite)
{
    m_fastLed.clear(forceWrite);
    if (forceWrite) m_fastLed.delay(1);
}
