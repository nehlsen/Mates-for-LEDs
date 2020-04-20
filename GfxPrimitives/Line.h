#ifndef MATRIXTEST_TEST_LINE_H
#define MATRIXTEST_TEST_LINE_H

#include "GfxPrimitive.h"

class Line : public GfxPrimitive
{
public:
    Line();
    Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color);

    uint8_t getX0() const;
    uint8_t getY0() const;
    Line& setStart(uint8_t x, uint8_t y);

    uint8_t getX1() const;
    uint8_t getY1() const;
    Line& setEnd(uint8_t x, uint8_t y);

    const CRGB &getColor() const;
    Line& setColor(const CRGB &color);

protected:
    uint8_t m_x0;
    uint8_t m_y0;
    uint8_t m_x1;
    uint8_t m_y1;
    CRGB m_color;

    void update();
};

#endif //MATRIXTEST_TEST_LINE_H
