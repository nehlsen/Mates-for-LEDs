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

GfxPrimitive &GfxPrimitive::merge(const Pixel &pixel)
{
    m_pixels = PixelMap::fromPixels(pixels()).add(pixel).toPixels();

    return *this;
}

GfxPrimitive GfxPrimitive::merged(const GfxPrimitive &other) const
{
    return GfxPrimitive(*this).merge(other);
}

GfxPrimitive GfxPrimitive::merged(const Pixel &pixel) const
{
    return GfxPrimitive(*this).merge(pixel);
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

GfxPrimitive &GfxPrimitive::transform(int8_t x, int8_t y)
{
    for (auto& pixel : m_pixels) {
        pixel.transform(x, y);
    }

    return *this;
}

GfxPrimitive GfxPrimitive::transformed(int8_t x, int8_t y) const
{
    return GfxPrimitive(*this).transform(x, y);
}

void GfxPrimitive::render(LedMatrix &matrix) const
{
    for (const auto& pixel : pixels()) {
        matrix.pixel(pixel.getX(), pixel.getY()) = pixel.getColor();
    }
}
