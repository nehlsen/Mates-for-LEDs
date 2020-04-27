#ifndef MATRIX_PIXEL_H
#define MATRIX_PIXEL_H

#include "LedMatrix.h"
#include "Point.h"

class Pixel // extend GfxPrimitive ??
{
public:
    Pixel(int16_t x, int16_t y, const CRGB& color);
    Pixel(const Point &location, const CRGB& color);

    int16_t getX() const;
    Pixel& setX(int16_t x);

    int16_t getY() const;
    Pixel& setY(int16_t y);

    const Point &getLocation() const;
    Pixel& setLocation(const Point &location);

    // FIXME for this to work properly we need to be able to have negative m_x/m_y
    void transform(int16_t x, int16_t y);

    const CRGB &getColor() const;
    void setColor(const CRGB &color);

    void render(LedMatrix& matrix) const;

protected:
    int16_t m_x;
    int16_t m_y;
    CRGB m_color;
};

#include <vector>
// a dumb list of pixels. multiple pixels at same coordinates are possible. behaviour undefined
typedef std::vector<Pixel> Pixels;

#endif //MATRIX_PIXEL_H
