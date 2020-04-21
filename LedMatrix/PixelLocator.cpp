#include <esp_log.h>
#include "PixelLocator.h"
#include <algorithm>

// most of the X/Y Code from Marcmerlin - FramebufferGFX
// TODO add proper attribution

PixelLocator::PixelLocator(uint8_t width, uint8_t height, uint8_t options):
    m_physicalWidth(width), m_physicalHeight(height), m_options(options)
{
}

uint16_t PixelLocator::xyToIndex(uint8_t x, uint8_t y) const
{
    // WIDTH / HEIGHT              ->  physical
    // _width / _height            ->  visual / rotation applied
    // matrixWidth / matrixHeight  ->  seems to be a copy of WIDTH / HEIGHT

    if (x >= visualWidth() || y >= visualHeight()) {
        return m_physicalWidth * m_physicalHeight;
    }

    applyRotation(&x, &y);

    // Find pixel number within tile
    uint16_t minor = x; // Presume row major to start (will swap later if needed)
    uint16_t major = y;

    // Determine corner of entry, flip axes if needed
    if (hasOption(MatrixInvertHorizontal)) {
        minor = m_physicalWidth  - 1 - minor;
    }
    if (hasOption(MatrixInvertVertical)) {
        major = m_physicalHeight - 1 - major;
    }

    // Determine actual major axis of matrix
    uint16_t majorScale;
    if (hasOption(MatrixVertical)) {
        std::swap(major, minor);
        majorScale = m_physicalHeight;
    } else {
        majorScale = m_physicalWidth;
    }

    // Determine pixel number within tile/matrix
    int pixelOffset;
    if(hasOption(MatrixStraight)) {
        // All lines in same order
        pixelOffset = major * majorScale + minor;
    } else {
        // Zigzag; alternate rows change direction.
        if(major & 1) pixelOffset = (major + 1) * majorScale - 1 - minor;
        else          pixelOffset =  major      * majorScale     + minor;
    }

    ESP_LOGD("LedMatrix", "PixelLocator::xyToIndex(%d, %d) -> %d", x, y, pixelOffset);

    return pixelOffset;
}

uint8_t PixelLocator::visualWidth() const
{
    if (hasOption(MatrixRotate_90) || hasOption(MatrixRotate_270)) {
        return m_physicalHeight;
    }

    // rotate 0 or 180
    return m_physicalWidth;
}

uint8_t PixelLocator::visualHeight() const
{
    if (hasOption(MatrixRotate_90) || hasOption(MatrixRotate_270)) {
        return m_physicalWidth;
    }

    // rotate 0 or 180
    return m_physicalHeight;
}

void PixelLocator::applyRotation(uint8_t *x, uint8_t *y) const
{
    uint8_t tmp;

    if (hasOption(MatrixRotate_90)) {
        tmp = *x;
        *x = m_physicalWidth  - 1 - *y;
        *y = tmp;
    }
    if (hasOption(MatrixRotate_180)) {
        *x = m_physicalWidth  - 1 - *x;
        *y = m_physicalHeight - 1 - *y;
    }
    if (hasOption(MatrixRotate_270)) {
        tmp = *x;
        *x = *y;
        *y = m_physicalHeight - 1 - tmp;
    }
}

bool PixelLocator::hasOption(MatrixOptions option) const
{
    return m_options & option;
}
