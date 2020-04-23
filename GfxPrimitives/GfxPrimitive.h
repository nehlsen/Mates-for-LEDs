#ifndef MATRIX_GFXPRIMITIVE_H
#define MATRIX_GFXPRIMITIVE_H

#include "Pixel.h"

class GfxPrimitive
{
public:
    virtual Pixels pixels() const;

    // add another primitive to this one, second overwrites first
    GfxPrimitive& merge(const GfxPrimitive& other);
    GfxPrimitive& merge(const Pixel& pixel);

    // create new primitive from this and other
    GfxPrimitive merged(const GfxPrimitive& other) const;
    GfxPrimitive merged(const Pixel& pixel) const;

    // add another primitive to this one, matching pixels are blended together
    GfxPrimitive& blend(const GfxPrimitive& other);

    // create new primitive from this and other
    GfxPrimitive blended(const GfxPrimitive& other) const;

    void render(LedMatrix& matrix) const;

protected:
    Pixels m_pixels;
};

#endif //MATRIX_GFXPRIMITIVE_H
