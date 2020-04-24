#include "Pixel.h"

Pixel::Pixel(uint8_t x, uint8_t y, const CRGB &color):
    m_x(x), m_y(y), m_color(color)
{}

uint8_t Pixel::getX() const
{
    return m_x;
}

void Pixel::setX(uint8_t x)
{
    m_x = x;
}

uint8_t Pixel::getY() const
{
    return m_y;
}

void Pixel::setY(uint8_t y)
{
    m_y = y;
}

void Pixel::transform(int8_t x, int8_t y)
{
    if (x < 0 && abs(x) > m_x) {
        // FIXME
        x = -1 * m_x;
    }
    if (y < 0 && abs(y) > m_y) {
        // FIXME
        y = -1 * m_y;
    }

    m_x += x;
    m_y += y;
}

const CRGB &Pixel::getColor() const
{
    return m_color;
}

void Pixel::setColor(const CRGB &color)
{
    m_color = color;
}

void Pixel::render(LedMatrix &matrix) const
{
    matrix.pixel(getX(), getY()) = getColor();
}
