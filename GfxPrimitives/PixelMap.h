#ifndef MATRIX_PIXELMAP_H
#define MATRIX_PIXELMAP_H

#include <map>
#include "Pixel.h"

struct Point {
    uint8_t x;
    uint8_t y;

    bool operator<(const Point& other) const;
};

// indexed list of pixels. each coordinate can hold exactly one pixel
class PixelMap : public std::map<Point, const Pixel>
{
public:
    static PixelMap fromPixels(const Pixels& pixels);
    Pixels toPixels() const;

    // add and replace
    PixelMap& add(const Pixel& pixel);
    PixelMap& add(const Pixels& pixels);

    bool has(const Pixel& pixel) const;

    const Pixel& at(const Pixel& pixel) const;

protected:
    static Point point(const Pixel& pixel);
};

#endif //MATRIX_PIXELMAP_H
