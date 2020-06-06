#include "Line.h"

// line calc code adapted from AdafruitGfxLib
// TODO add proper attribution

Line::Line():
    m_x0(0), m_y0(0), m_x1(0), m_y1(0)
{
}

Line::Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1):
    m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1)
{
    update();
}

Line::Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color):
    m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1), m_color(color)
{
    update();
}

Line::Line(Point p0, Point p1):
    m_x0(p0.x), m_y0(p0.y), m_x1(p1.x), m_y1(p1.y)
{
    update();
}

uint8_t Line::getX0() const
{
    return m_x0;
}

uint8_t Line::getY0() const
{
    return m_y0;
}

Line& Line::setStart(uint8_t x, uint8_t y)
{
    m_x0 = x;
    m_y0 = y;
    update();

    return *this;
}

uint8_t Line::getX1() const
{
    return m_x1;
}

uint8_t Line::getY1() const
{
    return m_y1;
}

Line& Line::setEnd(uint8_t x, uint8_t y)
{
    m_x1 = x;
    m_y1 = y;
    update();

    return *this;
}

const CRGB &Line::getColor() const
{
    return m_color;
}

Line& Line::setColor(const CRGB &color)
{
    m_color = color;
    update();

    return *this;
}

void Line::update()
{
    uint8_t x0 = m_x0;
    uint8_t y0 = m_y0;
    uint8_t x1= m_x1;
    uint8_t y1 = m_y1;

    int16_t steep = abs(y1 - y0) > abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }

    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int16_t dx, dy;
    dx = x1 - x0;
    dy = abs(y1 - y0);

    int16_t err = dx / 2;
    int16_t ystep;

    if (y0 < y1) {
        ystep = 1;
    } else {
        ystep = -1;
    }

    Pixels newPixels;
    for (; x0 <= x1; x0++) {
        if (steep) {
            newPixels.push_back(Pixel(y0, x0, m_color));
        } else {
            newPixels.push_back(Pixel(x0, y0, m_color));
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }

    m_pixels = newPixels;
}
