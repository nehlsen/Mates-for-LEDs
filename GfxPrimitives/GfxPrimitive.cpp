#include "GfxPrimitive.h"
#include "PixelMap.h"

Pixels GfxPrimitive::pixels() const
{
    return m_pixels;
}

GfxPrimitive& GfxPrimitive::merge(const GfxPrimitive &other)
{
    m_pixels = PixelMap::fromPixels(pixels()).add(other.pixels()).toPixels();

    return *this;
}

GfxPrimitive GfxPrimitive::merged(const GfxPrimitive &other) const
{
    return GfxPrimitive(*this).merge(other);
}

GfxPrimitive& GfxPrimitive::blend(const GfxPrimitive &other)
{
    auto thisPixels = PixelMap::fromPixels(pixels());
    auto otherPixels = PixelMap::fromPixels(other.pixels());

    for (auto it = otherPixels.begin(); it != otherPixels.end(); ++it) {
        if (thisPixels.has(it->second)) {
            Pixel thisPixel = thisPixels.at(it->second);
            thisPixels.erase(it->first);
            thisPixel.setColor(thisPixel.getColor().lerp8(it->second.getColor(), 128));
            thisPixels.add(thisPixel);
        } else {
            thisPixels.add(it->second);
        }
    }

    m_pixels = thisPixels.toPixels();

    return *this;
}

GfxPrimitive GfxPrimitive::blended(const GfxPrimitive &other) const
{
    return GfxPrimitive(*this).blend(other);
}
