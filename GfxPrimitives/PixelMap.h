#ifndef MATRIX_PIXELMAP_H
#define MATRIX_PIXELMAP_H

#include <map>
#include "Pixel.h"
#include "Point.h"
#include "Size.h"

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

    // find the lowest, left most pixel
//    Point bottomLeft() const;
    // find the relative size starting from bottomLeft
    // atw: starting at 0,0, e.g. the highest, right most pixel. the pixel has not be be actually set
    Size visualSize() const;

protected:
    static Point point(const Pixel& pixel);
};

#endif //MATRIX_PIXELMAP_H
