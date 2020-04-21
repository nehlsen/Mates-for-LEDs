#include "PixelMap.h"

bool Point::operator<(const Point &other) const
{
    return x == other.x ? y < other.y : x < other.x;
}

PixelMap PixelMap::fromPixels(const Pixels &pixels)
{
    auto pm = PixelMap();
    pm.add(pixels);

    return pm;
}

Pixels PixelMap::toPixels() const
{
    Pixels pixels;
    for (auto it = begin(); it != end(); ++it) {
        pixels.push_back(it->second);
    }

    return pixels;
}

void PixelMap::add(const Pixel &pixel)
{
    if (has(pixel)) {
        erase(point(pixel));
    }

    insert({point(pixel), pixel});
}

void PixelMap::add(const Pixels &pixels)
{
    for (const auto& pixel : pixels) {
        add(pixel);
    }
}

bool PixelMap::has(const Pixel &pixel) const
{
    return find(point(pixel)) != end();
}

const Pixel &PixelMap::at(const Pixel &pixel) const
{
    return map::at(point(pixel));
}

Point PixelMap::point(const Pixel& pixel)
{
    return {pixel.getX(), pixel.getY()};
}
