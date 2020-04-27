#include "Pixel.h"

Pixel::Pixel(int16_t x, int16_t y, const CRGB &color):
    m_x(x), m_y(y), m_color(color)
{}

Pixel::Pixel(const Point &location, const CRGB &color):
    Pixel(location.x, location.y, color)
{}

int16_t Pixel::getX() const
{
    return m_x;
}

Pixel& Pixel::setX(int16_t x)
{
    m_x = x;
    return *this;
}

int16_t Pixel::getY() const
{
    return m_y;
}

Pixel& Pixel::setY(int16_t y)
{
    m_y = y;
    return *this;
}

const Point &Pixel::getLocation() const
{
    return Point({getX(), getY()});
}

Pixel& Pixel::setLocation(const Point &location)
{
    return setX(location.x).setY(location.y);
}

void Pixel::transform(int16_t x, int16_t y)
{
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
