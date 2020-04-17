#include "GfxPrimitive.h"

Pixels GfxPrimitive::pixels() const
{
    return m_pixels;
}

GfxPrimitive& GfxPrimitive::add(const GfxPrimitive &other)
{
    for (auto pixel : other.pixels()) {
    }

    return *this;
}

GfxPrimitive& GfxPrimitive::blend(const GfxPrimitive &other)
{
    for (auto pixel : other.pixels()) {
    }

    return *this;
}
