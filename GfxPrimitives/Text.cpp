#include "Text.h"
#include "fonts/font5x7.h"
#include "../LedMatrix/color_utils.h"

Text::Text():
    Text(0, 0, "", CRGB::Black)
{}

Text::Text(const std::string &text, const CRGB &color):
    Text(0, 0, text, color)
{
}

Text::Text(uint8_t x, uint8_t y, const std::string &text, const CRGB &color):
    m_x(x), m_y(y), m_size({0, 0}), m_backgroundColor(CRGB::Black), m_color(color)
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

const CRGB &Text::getColor() const
{
    return m_color;
}

Text& Text::setColor(const CRGB &color)
{
    m_color = color;
    m_useGradient = false;
    update();

    return *this;
}

const CRGBPalette16 & Text::getGradient() const
{
    return m_gradient;
}

Text & Text::setGradient(const CRGBPalette16 &gradient, GradientMode gradientMode)
{
    m_gradient = gradient;
    m_useGradient = true;
    setGradientMode(gradientMode);
    update();

    return *this;
}

Text::GradientMode Text::getGradientMode() const
{
    return m_gradientMode;
}

Text& Text::setGradientMode(Text::GradientMode gradientMode)
{
    m_gradientMode = gradientMode;

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

    for (int charIndex = 0; charIndex < m_text.size(); ++charIndex) {
        auto charAtIndex = m_text.at(charIndex);

        if (charAtIndex == '\r') {
            continue;
        }

        // FIXME auto Line Feed - we do not know the display width ...
        if (charAtIndex == '\n') {
            cursor_x = m_x;
            transform(0, fontSize().height); // "scroll" canvas to next line
            continue;
        }
        drawChar(cursor_x, m_y, charIndex, charAtIndex);
        cursor_x += fontSize().width;
        // TODO letter spacing
    }
}

void Text::drawChar(uint8_t x, uint8_t y, int charIndex, unsigned char c)
{
    if (c >= 176) { // FIXME no idea what this is for...
        c++; // Handle 'classic' charset behavior
    }

    auto colorAtX = [this, charIndex](uint8_t x) {
        if (!m_useGradient) {
            return m_color;
        }

        switch (m_gradientMode) {
            default:
            case GradientModePerLetter:
                return ColorFromPalette(m_gradient, map(charIndex, 0, m_text.size(), 0, 255));

            case GradientModeOverlay:
                return ColorFromPalette(m_gradient, map(x, 0, m_size.width, 0, 255));
        }
    };
        
    for (int8_t i = 0; i < 5; i++) { // 5 columns
        uint8_t line = font[c * 5 + i];
        for (int8_t j = 6; j >= 0; j--, line >>= 1) { // 7 rows
            if (line & 1) {
                addNewPixel(x + i, y + j, colorAtX(x+i));
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
