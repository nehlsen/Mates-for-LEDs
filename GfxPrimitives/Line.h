#ifndef MATRIX_LINE_H
#define MATRIX_LINE_H

#include "GfxPrimitive.h"

class Line : public GfxPrimitive
{
public:
    Line();
    Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1);
    Line(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1, const CRGB &color);
    Line(Point p0, Point p1);

    uint8_t getX0() const;
    uint8_t getY0() const;
    Line& setStart(uint8_t x, uint8_t y);

    uint8_t getX1() const;
    uint8_t getY1() const;
    Line& setEnd(uint8_t x, uint8_t y);

    const CRGB &getColor() const;
    Line& setColor(const CRGB &color);

    const CRGBPalette16 &getGradient() const;
    Line& setGradient(const CRGBPalette16 &gradient);

protected:
    uint8_t m_x0;
    uint8_t m_y0;
    uint8_t m_x1;
    uint8_t m_y1;

    CRGB m_color;
    bool hasGradient();
    CRGBPalette16 m_gradient;

    void update();
};

#endif //MATRIX_LINE_H
