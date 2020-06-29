#include "Line.h"
#include "../LedMatrix/color_utils.h"

// line calc code adapted from AdafruitGfxLib
// TODO add proper attribution

Line::Line():
    Line(0, 0, 0, 0, CRGB(0, 0, 0))
{}

Line::Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1):
    Line(x0, y0, x1, y1, CRGB(0, 0, 0))
{}

Line::Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color):
    m_x0(x0), m_y0(y0), m_x1(x1), m_y1(y1), m_color(color), m_gradient(CRGB(0, 0, 0))
{
    update();
}

Line::Line(Point p0, Point p1):
    Line(p0.x, p0.y, p1.x, p1.y, CRGB(0, 0, 0))
{}

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
    m_useGradient = false;
    update();

    return *this;
}

const CRGBPalette16 & Line::getGradient() const
{
    return m_gradient;
}

Line & Line::setGradient(const CRGBPalette16 &gradient)
{
    m_gradient = gradient;
    m_useGradient = true;
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

    auto colorAtX = [this, x0, x1](uint8_t x) {
        if (!m_useGradient) {
            return m_color;
        }

        return ColorFromPalette(m_gradient, map(x, x0, x1, 0, 255));
    };

    Pixels newPixels;
    for (; x0 <= x1; x0++) {
        if (steep) {
            newPixels.push_back(Pixel(y0, x0, colorAtX(x0)));
        } else {
            newPixels.push_back(Pixel(x0, y0, colorAtX(x0)));
        }
        err -= dy;
        if (err < 0) {
            y0 += ystep;
            err += dx;
        }
    }

    m_pixels = newPixels;
}
