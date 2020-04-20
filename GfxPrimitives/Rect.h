#ifndef MATRIXTEST_TEST_RECT_H
#define MATRIXTEST_TEST_RECT_H

#include "GfxPrimitive.h"

/**
 * setWidth, setHeight and setSize all leave `start` as is
 */
class Rect : public GfxPrimitive
{
public:
    Rect();
    Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    Rect(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color);
    
    uint8_t getX0() const;
    uint8_t getY0() const;
    Rect& setStart(uint8_t x, uint8_t y);

    uint8_t getX1() const;
    uint8_t getY1() const;
    Rect& setEnd(uint8_t x, uint8_t y);

    uint8_t getWidth() const;
    Rect& setWidth(uint8_t width); // overwrites end

    uint8_t getHeight() const;
    Rect& setHeight(uint8_t height); // overwrites end

    Rect& setSize(uint8_t width, uint8_t height); // overwrites end

    const CRGB &getColor() const;
    Rect& setColor(const CRGB &color);

protected:
    uint8_t m_x0;
    uint8_t m_y0;
    uint8_t m_x1;
    uint8_t m_y1;
    CRGB m_color;

    void update();
};

#endif //MATRIXTEST_TEST_RECT_H
