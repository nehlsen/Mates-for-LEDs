#ifndef MATRIX_POINT_H
#define MATRIX_POINT_H

#include <stdint.h>

struct Point {
    int16_t x;
    int16_t y;

    bool operator<(const Point& other) const;
};

#endif //MATRIX_POINT_H
