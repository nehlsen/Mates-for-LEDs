#include "Size.h"

bool Size::operator<(const Size &other) const
{
    return width*height < other.width*other.height;
}
