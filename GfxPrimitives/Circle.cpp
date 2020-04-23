#include "Circle.h"

Circle::Circle():
    m_x(0), m_y(0), m_radius(0), m_quarters(QuartersAll)
{}

Circle::Circle(uint8_t x, uint8_t y, uint8_t radius):
    m_x(x), m_y(y), m_radius(radius), m_quarters(QuartersAll)
{
    update();
}

Circle::Circle(uint8_t x, uint8_t y, uint8_t radius, const CRGB &color):
        m_x(x), m_y(y), m_radius(radius), m_quarters(QuartersAll), m_borderColor(color)
{
    update();
}

uint8_t Circle::getX() const
{
    return m_x;
}

uint8_t Circle::getY() const
{
    return m_y;
}

Circle &Circle::setCenter(uint8_t x, uint8_t y)
{
    m_x = x;
    m_y = y;
    update();

    return *this;
}

uint8_t Circle::getRadius() const
{
    return m_radius;
}

Circle &Circle::setRadius(uint8_t radius)
{
    m_radius = radius;
    update();

    return *this;
}

uint8_t Circle::getQuarters() const
{
    return m_quarters;
}

Circle& Circle::setQuarters(uint8_t quarters)
{
    m_quarters = quarters;
    update();

    return *this;
}

const CRGB &Circle::getBorderColor() const
{
    return m_borderColor;
}

Circle &Circle::setBorderColor(const CRGB &color)
{
    m_borderColor = color;
    update();

    return *this;
}

const CRGB & Circle::getFillColor() const
{
    return m_fillColor;
}

Circle& Circle::setFillColor(const CRGB &color)
{
    m_fillColor = color;
    m_fillWithColor = true;
    update();

    return *this;
}

Circle & Circle::unsetFillColor()
{
    m_fillWithColor = false;
    update();

    return *this;
}

void Circle::update()
{
    m_pixels.clear();

    drawBorder();
    drawBackground();
}

void Circle::drawBorder()
{
    if (m_radius < 1) {
        return;
    }

    if (m_quarters & QuartersTop) {
        addNewPixel(m_x, m_y + m_radius, m_borderColor);
    }
    if (m_quarters & QuartersRight) {
        addNewPixel(m_x + m_radius, m_y, m_borderColor);
    }
    if (m_quarters & QuartersBottom) {
        addNewPixel(m_x, m_y - m_radius, m_borderColor);
    }
    if (m_quarters & QuartersLeft) {
        addNewPixel(m_x - m_radius, m_y, m_borderColor);
    }

    int16_t f = 1 - m_radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * m_radius;
    int16_t x = 0;
    int16_t y = m_radius;

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;
        if (m_quarters & QuarterTopRight) {
            addNewPixel(m_x + x, m_y + y, m_borderColor);
            addNewPixel(m_x + y, m_y + x, m_borderColor);
        }
        if (m_quarters & QuarterBottomRight) {
            addNewPixel(m_x + x, m_y - y, m_borderColor);
            addNewPixel(m_x + y, m_y - x, m_borderColor);
        }
        if (m_quarters & QuarterTopLeft) {
            addNewPixel(m_x - y, m_y + x, m_borderColor);
            addNewPixel(m_x - x, m_y + y, m_borderColor);
        }
        if (m_quarters & QuarterBottomLeft) {
            addNewPixel(m_x - y, m_y - x, m_borderColor);
            addNewPixel(m_x - x, m_y - y, m_borderColor);
        }
    }
}

void Circle::drawBackground()
{
    if (!m_fillWithColor) {
        return;
    }

    int16_t f = 1 - m_radius;
    int16_t ddF_x = 1;
    int16_t ddF_y = -2 * m_radius;
    int16_t x = 0;
    int16_t y = m_radius;

    if (m_quarters & QuartersTop) {
        drawVLine(m_x, m_y, m_radius, m_fillColor);
    }
    if (m_quarters & QuartersBottom) {
        drawVLine(m_x, m_y - m_radius + 1, m_radius, m_fillColor);
    }

    while (x < y) {
        if (f >= 0) {
            y--;
            ddF_y += 2;
            f += ddF_y;
        }
        x++;
        ddF_x += 2;
        f += ddF_x;

        if (x < (y + 1)) {
            if (m_quarters & QuarterTopRight) {
                drawVLine(m_x + x, m_y, y, m_fillColor);
                if (y < m_radius) drawVLine(m_x + y, m_y, x, m_fillColor);
            }
            if (m_quarters & QuarterTopLeft) {
                drawVLine(m_x - x, m_y, y, m_fillColor);
                if (y < m_radius) drawVLine(m_x - y, m_y, x, m_fillColor);
            }
            if (m_quarters & QuarterBottomLeft) {
                drawVLine(m_x - x, m_y - y + 1, y, m_fillColor);
                if (y < m_radius) drawVLine(m_x - y, m_y - x + 1, x, m_fillColor);
            }
            if (m_quarters & QuarterBottomRight) {
                drawVLine(m_x + x, m_y - y + 1, y, m_fillColor);
                if (y < m_radius) drawVLine(m_x + y, m_y - x + 1, x, m_fillColor);
            }
        }
    }
}

void Circle::addNewPixel(int16_t x, int16_t y, const CRGB& color)
{
    if (x < 0 || y < 0) {
        return;
    }

    m_pixels.push_back(Pixel(x, y, color));
}

void Circle::drawVLine(uint8_t x, uint8_t y, uint8_t height, const CRGB &color)
{
    for (int n = 0; n < height; ++n) {
        m_pixels.push_back(Pixel(x, y + n, color));
    }
}
