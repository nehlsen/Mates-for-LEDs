#include "PixelMap.h"

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

PixelMap& PixelMap::add(const Pixel &pixel)
{
    if (has(pixel)) {
        erase(point(pixel));
    }

    insert({point(pixel), pixel});

    // FIXME erase BLACK Pixels

    return *this;
}

PixelMap& PixelMap::add(const Pixels &pixels)
{
    for (const auto& pixel : pixels) {
        add(pixel);
    }

    return *this;
}

bool PixelMap::has(const Pixel &pixel) const
{
    return find(point(pixel)) != end();
}

const Pixel &PixelMap::at(const Pixel &pixel) const
{
    return map::at(point(pixel));
}

Size PixelMap::visualSize() const
{
    Size size = {0, 0};
    for (auto it = begin(); it != end(); ++it) {
        if (it->first.x+1 > size.width) {
            size.width = it->first.x+1;
        }
        if (it->first.y+1 > size.height) {
            size.height = it->first.y+1;
        }
    }

    return size;
}

Point PixelMap::point(const Pixel& pixel)
{
    return {pixel.getX(), pixel.getY()};
}
