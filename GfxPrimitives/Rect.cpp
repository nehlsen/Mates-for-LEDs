#include "Rect.h"

#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))

Rect::Rect():
    m_x(0), m_y(0), m_width(0), m_height(0)
{}

Rect::Rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height):
    m_x(x), m_y(y), m_width(width), m_height(height)
{
    update();
}

Rect::Rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const CRGB &color):
    m_x(x), m_y(y), m_width(width), m_height(height), m_borderColor(color)
{
    update();
}

uint8_t Rect::getX0() const
{
    return m_x;
}

uint8_t Rect::getY0() const
{
    return m_y;
}

Rect& Rect::setStart(uint8_t x, uint8_t y)
{
    m_x = x;
    m_y = y;
    update();

    return *this;
}

uint8_t Rect::getX1() const
{
    return getWidth() == 0 ? getX0() : getX0() + getWidth() - 1;
}

uint8_t Rect::getY1() const
{
    return getHeight() == 0 ? getY0() : getY0() + getHeight() - 1;
}

Rect& Rect::setEnd(uint8_t x, uint8_t y)
{
    if (x < m_x) {
        int8_t tmp = m_x;
        m_x = x;
        x = tmp;
    }
    m_width = x - m_x + 1;

    if (y < m_y) {
        int8_t tmp = m_y;
        m_y = y;
        y = tmp;
    }
    m_height = y - m_y + 1;

    update();
    return *this;
}

uint8_t Rect::getWidth() const
{
    return m_width;
}

Rect& Rect::setWidth(uint8_t width)
{
    m_width = width;
    update();
    return *this;
}

uint8_t Rect::getHeight() const
{
    return m_height;
}

Rect& Rect::setHeight(uint8_t height)
{
    m_height = height;
    update();
    return *this;
}

Rect& Rect::setSize(uint8_t width, uint8_t height)
{
    m_width = width;
    m_height = height;
    update();
    return *this;
}

const CRGB & Rect::getBorderColor() const
{
    return m_borderColor;
}

Rect& Rect::setBorderColor(const CRGB &color)
{
    m_borderColor = color;
    update();

    return *this;
}

const CRGB & Rect::getFillColor() const
{
    return m_fillColor;
}

Rect& Rect::setFillColor(const CRGB &color)
{
    m_fillColor = color;
    m_fillWithColor = true;
    update();

    return *this;
}

Rect & Rect::unsetFillColor()
{
    m_fillWithColor = false;
    update();

    return *this;
}

void Rect::update()
{
    m_newPixels.clear();

    drawBorder();
    drawBackground();

    m_pixels = m_newPixels;
}

void Rect::drawBorder()
{
    drawHLine(getX0(), getY0(), getWidth(), m_borderColor);
    if (getHeight() > 1) drawHLine(getX0(), getY1(), getWidth(), m_borderColor);

    if (getHeight() > 2) drawVLine(getX0(), getY0(), getHeight(), m_borderColor);
    if (getHeight() > 2 && getWidth() > 1) drawVLine(getX1(), getY0(), getHeight(), m_borderColor);
}

void Rect::drawBackground()
{
    if (!m_fillWithColor) {
        return;
    }

    if (getWidth() <= 2 || getHeight() <= 2) {
        return;
    }

    // this could be optimized...
    for (int y = getY0()+1; y < getY0() + getHeight() - 1; ++y) {
        drawHLine(getX0()+1, y, getWidth()-2, m_fillColor);
    }
}

void Rect::drawHLine(uint8_t x, uint8_t y, uint8_t width, const CRGB& color)
{
    for (int n = 0; n < width; ++n) {
        m_newPixels.push_back(Pixel(x + n, y, color));
    }
}

void Rect::drawVLine(uint8_t x, uint8_t y, uint8_t height, const CRGB& color)
{
    for (int n = 0; n < height; ++n) {
        m_newPixels.push_back(Pixel(x, y + n, color));
    }
}
