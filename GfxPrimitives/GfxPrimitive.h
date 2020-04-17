#ifndef LEDWALL_GFXPRIMITIVE_H
#define LEDWALL_GFXPRIMITIVE_H

#include "Pixel.h"

class GfxPrimitive
{
public:
    virtual Pixels pixels() const;

    // add another primitive to this one, second overwrites first
    GfxPrimitive& add(const GfxPrimitive& other);
    // add another primitive to this one, matching pixels are blended together
    GfxPrimitive& blend(const GfxPrimitive& other);

//    void render(Matrix *matrix);

protected:
    Pixels m_pixels;
};

#endif //LEDWALL_GFXPRIMITIVE_H
