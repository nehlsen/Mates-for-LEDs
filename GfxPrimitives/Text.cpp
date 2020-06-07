#include "Text.h"

#include "fonts/font5x7.h"

Text::Text():
    m_x(0), m_y(0), m_size({0, 0}), m_color(0, 0, 0), m_backgroundColor(0, 0, 0)
{}

Text::Text(const std::string &text, const CRGB &color):
    Text(0, 0, text, color)
{
}

Text::Text(uint8_t x, uint8_t y, const std::string &text, const CRGB &color):
    m_x(x), m_y(y), m_size({0, 0}), m_color(color), m_backgroundColor(0, 0, 0)
{
    setText(text);
}

uint8_t Text::getX() const
{
    return m_x;
}

Text& Text::setX(uint8_t x)
{
    m_x = x;
    update();

    return *this;
}

uint8_t Text::getY() const
{
    return m_y;
}

Text& Text::setY(uint8_t y)
{
    m_y = y;
    update();

    return *this;
}

Text &Text::setTopLeft(uint8_t x, uint8_t y)
{
    m_x = x;
    m_y = getSize().height == 0 ? y : y - getSize().height + 1;
    update();

    return *this;
}

Text &Text::setTopLeft(Point topLeft)
{
    return setTopLeft(topLeft.x, topLeft.y);
}

Point Text::getTopLeft() const
{
    return Point({m_x, int16_t(m_y + (getSize().height == 0 ? 0 : getSize().height - 1))});
}

Size Text::getSize() const
{
    return m_size;
}

const std::string &Text::getText() const
{
    return m_text;
}

Text& Text::setText(const std::string &text)
{
    m_text = text;
    updateSize();
    update();

    return *this;
}

const CRGB &Text::getColor() const
{
    return m_color;
}

Text& Text::setColor(const CRGB &color)
{
    m_color = color;
    update();

    return *this;
}

const CRGB &Text::getBackgroundColor() const
{
    return m_backgroundColor;
}

Text& Text::setBackgroundColor(const CRGB &color)
{
    m_backgroundColor = color;
    update();

    return *this;
}

Size Text::fontSize() const
{
    // FIXME
    return Size({5, 7});
}

void Text::updateSize()
{
    if (m_text.empty()) {
        m_size = Size({0, 0});
        return;
    }

    int lineCount = 1;
    int longestLine = 0;
    int currentLineLength = 0;
    for (auto it = m_text.cbegin(); it != m_text.cend(); ++it) {
        if (*it == '\r') {
            continue;
        }

        if (*it == '\n') {
            lineCount++;
            currentLineLength = 0;
            continue;
        }

        currentLineLength++;
        longestLine = longestLine > currentLineLength ? longestLine : currentLineLength;
    }

    m_size = fontSize();
    m_size.width *= longestLine;
    m_size.height *= lineCount;
}

void Text::update()
{
    m_pixels.clear();

    uint8_t cursor_x = m_x;

    for (auto it = m_text.cbegin(); it != m_text.cend(); ++it) {
        if (*it == '\r') {
            continue;
        }

        // FIXME auto Line Feed - we do not know the display width ...
        if (*it == '\n') {
            cursor_x = m_x;
            transform(0, fontSize().height); // "scroll" canvas to next line
            continue;
        }
        drawChar(cursor_x, m_y, *it);
        cursor_x += fontSize().width;
    }
}

void Text::drawChar(uint8_t x, uint8_t y, unsigned char c)
{
    if (c >= 176) // FIXME no idea what this is for...
        c++; // Handle 'classic' charset behavior

    for (int8_t i = 0; i < 5; i++) { // 5 columns
        uint8_t line = font[c * 5 + i];
        for (int8_t j = 6; j >= 0; j--, line >>= 1) { // 7 rows
            if (line & 1) {
                addNewPixel(x + i, y + j, m_color);
            } else {
                addNewPixel(x + i, y + j, m_backgroundColor);
            }
        }
    }
}

void Text::addNewPixel(int16_t x, int16_t y, const CRGB& color)
{
    if (x < 0 || y < 0) {
        return;
    }

    m_pixels.push_back(Pixel(x, y, color));
}
