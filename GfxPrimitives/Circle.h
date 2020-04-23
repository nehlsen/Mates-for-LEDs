#ifndef MATRIX_CIRCLE_H
#define MATRIX_CIRCLE_H

#include "GfxPrimitive.h"

class Circle : public GfxPrimitive
{
public:
    Circle();
    Circle(uint8_t x, uint8_t y, uint8_t radius);
    Circle(uint8_t x, uint8_t y, uint8_t radius, const CRGB &color);

    uint8_t getX() const;
    uint8_t getY() const;
    Circle& setCenter(uint8_t x, uint8_t y);

    uint8_t getRadius() const;
    Circle& setRadius(uint8_t radius);

    enum Quarters {
        QuarterTopRight = 0x4,
        QuarterBottomRight = 0x2,
        QuarterBottomLeft = 0x1,
        QuarterTopLeft = 0x8,

        QuartersTop = QuarterTopLeft | QuarterTopRight,
        QuartersBottom = QuarterBottomLeft | QuarterBottomRight,
        QuartersRight = QuarterTopRight | QuarterBottomRight,
        QuartersLeft = QuarterBottomLeft | QuarterTopLeft,

        QuartersAll = QuarterTopRight | QuarterBottomRight | QuarterBottomLeft | QuarterTopLeft,
    };

    uint8_t getQuarters() const;
    Circle& setQuarters(uint8_t quarters);

    const CRGB &getBorderColor() const;
    Circle& setBorderColor(const CRGB &color);

    const CRGB &getFillColor() const;
    Circle& setFillColor(const CRGB &color); // fill with black will clear all pixels
    Circle& unsetFillColor(); // no fill color will leave pixels intact

protected:
    uint8_t m_x;
    uint8_t m_y;
    uint8_t m_radius;
    uint8_t m_quarters;

    CRGB m_borderColor;
    CRGB m_fillColor;
    bool m_fillWithColor = false;

    void update();
    void drawBorder();
    void drawBackground();
    void addNewPixel(int16_t x, int16_t y, const CRGB& color);
    void drawVLine(uint8_t x, uint8_t y, uint8_t height, const CRGB& color); // FIXME duplicated from Rect
};

#endif //MATRIX_CIRCLE_H
