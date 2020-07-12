#ifndef MATRIX_RECT_H
#define MATRIX_RECT_H

#include "GfxPrimitive.h"

class Rect : public GfxPrimitive
{
public:
    Rect();
    Rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height);
    Rect(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const CRGB &borderColor);
    
    uint8_t getX0() const;
    uint8_t getY0() const;
    Rect& setStart(uint8_t x, uint8_t y);

    uint8_t getX1() const;
    uint8_t getY1() const;
    Rect& setEnd(uint8_t x, uint8_t y); // keeps width & height might change start

    uint8_t getWidth() const;
    Rect& setWidth(uint8_t width);

    uint8_t getHeight() const;
    Rect& setHeight(uint8_t height);

    Rect& setSize(uint8_t width, uint8_t height);

    const CRGB &getBorderColor() const;
    Rect& setBorderColor(const CRGB &color);

    const CRGB &getFillColor() const;
    Rect& setFillColor(const CRGB &color); // fill with black will clear all pixels
    Rect& unsetFillColor(); // no fill color will leave pixels intact

protected:
    uint8_t m_x;
    uint8_t m_y;
    uint8_t m_width;
    uint8_t m_height;

    CRGB m_borderColor;
    CRGB m_fillColor;
    bool m_fillWithColor = false;

    void update();
    Pixels m_newPixels;
    void drawBorder();
    void drawBackground();
    void drawHLine(uint8_t x, uint8_t y, uint8_t width, const CRGB& color);
    void drawVLine(uint8_t x, uint8_t y, uint8_t height, const CRGB& color);
};

#endif //MATRIX_RECT_H
