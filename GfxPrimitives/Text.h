#ifndef MATRIX_TEXT_H
#define MATRIX_TEXT_H

#include "GfxPrimitive.h"
#include "Point.h"
#include "Size.h"
#include <string>

class Text : public GfxPrimitive
{
public:
    Text();
    Text(uint8_t x, uint8_t y, const std::string& text, const CRGB &color);

    // x and y are bottom left
    uint8_t getX() const;
    Text& setX(uint8_t x);

    // x and y are bottom left
    uint8_t getY() const;
    Text& setY(uint8_t y);

    // setting top-left will use the actual size to set the lower-left x/y
    Text& setTopLeft(uint8_t x, uint8_t y);
    Text& setTopLeft(Point topLeft);
    // top-left will be calculated using the lower-left x/y plus the actual size
    Point getTopLeft() const;

    Size getSize() const;

    const std::string &getText() const;
    Text& setText(const std::string &text);

    // TODO color per char and even rainbow over all chars -> each char has multiple colors
    //      rainbow should work in hor&vert direction
    //      flame animation would be nice too :)
    const CRGB &getColor() const;
    Text& setColor(const CRGB &color);

    const CRGB &getBackgroundColor() const;
    Text& setBackgroundColor(const CRGB &color);

    // TODO setFont

protected:
    uint8_t m_x;
    uint8_t m_y;

    std::string m_text;

//    m_font
    Size fontSize() const;

    Size m_size;
    void updateSize();

    CRGB m_color;
    CRGB m_backgroundColor;
    bool drawBackground() const;

    void update();
    void drawChar(uint8_t x, uint8_t y, unsigned char c); // using 'the classic font'
    void addNewPixel(int16_t x, int16_t y, const CRGB& color); // FIXME copy from circle
};

#endif //MATRIX_TEXT_H
