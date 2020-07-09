#ifndef MATRIX_LINE_H
#define MATRIX_LINE_H

#include "GfxPrimitive.h"

class Line : public GfxPrimitive
{
public:
    Line();
    Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1);
    Line(int16_t x0, int16_t y0, int16_t x1, int16_t y1, const CRGB &color);
    Line(Point p0, Point p1);

    int16_t getX0() const;
    int16_t getY0() const;
    Line& setStart(int16_t x, int16_t y);

    int16_t getX1() const;
    int16_t getY1() const;
    Line& setEnd(int16_t x, int16_t y);

    const CRGB &getColor() const;
    Line& setColor(const CRGB &color);

    const CRGBPalette16 &getGradient() const;
    Line& setGradient(const CRGBPalette16 &gradient);

protected:
    int16_t m_x0;
    int16_t m_y0;
    int16_t m_x1;
    int16_t m_y1;

    CRGB m_color;

    bool m_useGradient = false;
    CRGBPalette16 m_gradient;

    void update();
};

#endif //MATRIX_LINE_H
