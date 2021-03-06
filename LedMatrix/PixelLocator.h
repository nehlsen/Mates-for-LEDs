#ifndef MATRIX_PIXELLOCATOR_H
#define MATRIX_PIXELLOCATOR_H

#include <cstdint>
#include "MatrixOptions.h"

class PixelLocator
{
public:
    PixelLocator(uint8_t width, uint8_t height, uint8_t options);

    uint16_t xyToIndex(uint8_t x, uint8_t y) const;

protected:
    const uint8_t m_physicalWidth;
    const uint8_t m_physicalHeight;
    const uint8_t m_options;

    uint8_t visualWidth() const;
    uint8_t visualHeight() const;

    // applies rotation option from m_options to provided x and y. x and y are both input as well as output
    void applyRotation(uint8_t* x, uint8_t* y) const;
    bool hasOption(MatrixOptions option) const;
};

#endif //MATRIX_PIXELLOCATOR_H
