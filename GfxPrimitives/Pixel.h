#ifndef MATRIXTEST_PIXEL_H
#define MATRIXTEST_PIXEL_H

#include "LedMatrix.h"

class Pixel // extend GfxPrimitive ??
{
public:
    Pixel(uint8_t x, uint8_t y, const CRGB& color);

    uint8_t getX() const;
    void setX(uint8_t x);

    uint8_t getY() const;
    void setY(uint8_t y);

    const CRGB &getColor() const;
    void setColor(const CRGB &color);

    void render(LedMatrix& matrix) const;

protected:
    uint8_t m_x;
    uint8_t m_y;
    CRGB m_color;
};

#include <vector>
// a dumb list of pixels. multiple pixels at same coordinates are possible. behaviour undefined
typedef std::vector<Pixel> Pixels;

#endif //MATRIXTEST_PIXEL_H
