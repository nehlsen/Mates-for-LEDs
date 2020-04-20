#include "Rect.h"

Rect::Rect():
    m_x0(0), m_y0(0), m_x1(0), m_y1(0)
{}

Rect::Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1):
    m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1)
{
    update();
}

Rect::Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color):
    m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1), m_color(color)
{
    update();
}

uint8_t Rect::getX0() const
{
    return m_x0;
}

uint8_t Rect::getY0() const
{
    return m_y0;
}

Rect& Rect::setStart(uint8_t x, uint8_t y)
{
    m_x0 = x;
    m_y0 = y;
    update();

    return *this;
}

uint8_t Rect::getX1() const
{
    return m_x1;
}

uint8_t Rect::getY1() const
{
    return m_y1;
}

Rect& Rect::setEnd(uint8_t x, uint8_t y)
{
    m_x1 = x;
    m_y1 = y;
    update();

    return *this;
}

uint8_t Rect::getWidth() const
{
    return abs(getX0() - getX1());
}

Rect& Rect::setWidth(uint8_t width)
{
    m_x1 = m_x0 + width;
    return *this;
}

uint8_t Rect::getHeight() const
{
    return abs(getY0() - getY1());
}

Rect& Rect::setHeight(uint8_t height)
{
    m_y1 = m_y0 + height;
    return *this;
}

Rect& Rect::setSize(uint8_t width, uint8_t height)
{
    return setWidth(width).setHeight(height);
}

const CRGB & Rect::getColor() const
{
    return m_color;
}

Rect& Rect::setColor(const CRGB &color)
{
    m_color = color;
    update();

    return *this;
}

void Rect::update()
{
    // TODO
}
