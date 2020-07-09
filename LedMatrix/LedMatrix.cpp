#include "LedMatrix.h"
#include <controller.h>

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

    uint16_t offset = 0;
    for (int controllerIndex = 0; controllerIndex < m_fastLed.count(); ++controllerIndex) {
        if ((index-offset) < m_fastLed[controllerIndex].size()) {
//            ESP_LOGW("LedMatrix", "pixel(%d,%d) -> index: %d, controllerIndex:%d -> offset:%d => %d", x, y, index, controllerIndex, offset, (index-offset));
            return m_fastLed[controllerIndex].leds()[(index-offset)];
        }

        offset += m_fastLed[controllerIndex].size();
    }

//    if (x < getWidth() && y < getHeight())
//        ESP_LOGW("LedMatrix", "pixel(%d,%d) -> index: %d => out of bounds", x, y, index);

    return m_outOfBounds;
}

void LedMatrix::drawPixel(uint8_t x, uint8_t y, const CRGB &color)
{
    pixel(x, y) = color;
}

void LedMatrix::setBrightness(uint8_t scale)
{
    m_fastLed.setBrightness(scale);
}

uint8_t LedMatrix::getBrightness()
{
    return m_fastLed.getBrightness();
}

void LedMatrix::fade(uint8_t scaledown)
{
    for (int controllerIndex = 0; controllerIndex < m_fastLed.count(); ++controllerIndex) {
        for (int i = 0; i < m_fastLed[controllerIndex].size(); i++) {
            m_fastLed[controllerIndex].leds()[i].nscale8(scaledown);
        }
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
