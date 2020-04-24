#ifndef MATRIX_SIZE_H
#define MATRIX_SIZE_H

#include <stdint.h>

struct Size {
    int16_t width;
    int16_t height;

    bool operator<(const Size& other) const;
};

#endif //MATRIX_SIZE_H
