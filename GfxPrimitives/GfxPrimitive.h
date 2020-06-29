#ifndef MATRIX_GFXPRIMITIVE_H
#define MATRIX_GFXPRIMITIVE_H

#include "LedMatrix.h"
#include "Pixel.h"
#include "Renderable.h"

class GfxPrimitive : public Renderable
{
public:
    virtual Pixels pixels() const;

    // add another primitive to this one, second overwrites first
    GfxPrimitive& merge(const GfxPrimitive& other);
    GfxPrimitive& merge(const Pixel& pixel);
    GfxPrimitive& merge(const Pixels &pixels);

    // create new primitive from this and other
    GfxPrimitive merged(const GfxPrimitive& other) const;
    GfxPrimitive merged(const Pixel& pixel) const;

    // add another primitive to this one, matching pixels are blended together
    GfxPrimitive& blend(const GfxPrimitive& other);

    // create new primitive from this and other
    GfxPrimitive blended(const GfxPrimitive& other) const;

    // change all pixels of primitive to be moved in x/y direction
    GfxPrimitive& transform(int16_t x, int16_t y);
    GfxPrimitive transformed(int16_t x, int16_t y) const;

protected:
    const Pixels &getPixelsToRender() const override;

    Pixels m_pixels;
};

#endif //MATRIX_GFXPRIMITIVE_H
