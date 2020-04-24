#ifndef MATRIX_POINT_H
#define MATRIX_POINT_H

#include <stdint.h>

struct Point {
    const int16_t x;
    const int16_t y;

    bool operator<(const Point& other) const;
};

#endif //MATRIX_POINT_H
