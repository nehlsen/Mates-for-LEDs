#include "PixelMap.h"
#include "Point.h"

bool Point::operator<(const Point &other) const
{
    return x == other.x ? y < other.y : x < other.x;
}