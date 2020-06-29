#include "GfxCanvas.h"

GfxCanvas::GfxCanvas()
{}

GfxCanvas::GfxCanvas(const GfxCanvas &other)
{
    m_pixels = other.m_pixels;
}

GfxCanvas::GfxCanvas(const GfxPrimitive &other)
{
    m_pixels = other.pixels();
}

Pixels GfxCanvas::originalPixels() const
{
    return GfxPrimitive::pixels();
}

Pixels GfxCanvas::pixels() const
{
    return mappedPixels();
}

GfxCanvas &GfxCanvas::setCanvas(int16_t x, int16_t y)
{
    return setCanvas(x, y, 0, 0, CanvasClipping);
}

GfxCanvas& GfxCanvas::setCanvas(int16_t x, int16_t y, int16_t width, int16_t height, GfxCanvas::CanvasOptions options)
{
    return setCanvas({x, y, width, height, options});
}

GfxCanvas &GfxCanvas::setCanvas(GfxCanvas::Canvas canvas)
{
    m_canvas = canvas;
    return *this;
}

GfxCanvas::Canvas GfxCanvas::getCanvas() const
{
    return m_canvas;
}

Pixels GfxCanvas::mappedPixels() const
{
    // if canvas has no x AND no y -> no transform
    // if canvas has no w AND no h -> no clipping/wrapping
    if (!m_canvas.transforms() && !m_canvas.clipsOrWraps()) {
        return originalPixels();
    }

    Pixels pixels_mapped = originalPixels();
    canvasTransformPixels(pixels_mapped);
    canvasClipPixels(pixels_mapped);
    canvasWrapPixels(pixels_mapped);

    return pixels_mapped;
}

void GfxCanvas::canvasTransformPixels(Pixels& pixels) const
{
    if (!m_canvas.transforms()) {
        return;
    }

    for (auto& pixel : pixels) {
        pixel.transform(m_canvas.x, m_canvas.y);
    }
}

void GfxCanvas::canvasClipPixels(Pixels &pixels) const
{
    if (!m_canvas.clipsOrWraps() || m_canvas.options != CanvasClipping) {
        return;
    }

    auto isOnCanvas = [this](const Pixel &pixel) {
        if (pixel.getX() < 0 || pixel.getX() - m_canvas.x >= m_canvas.width) {
            return false;
        }
        if (pixel.getY() < 0 || pixel.getY() - m_canvas.y >= m_canvas.height) {
            return false;
        }

        return true;
    };

    for (auto it = pixels.begin(); it != pixels.end(); ) {
        if (!isOnCanvas(*it)) {
            it = pixels.erase(it);
        } else {
            ++it;
        }
    }
}

void GfxCanvas::canvasWrapPixels(Pixels &pixels) const
{
    if (!m_canvas.clipsOrWraps() || m_canvas.options != CanvasWrapAround) {
        return;
    }

    auto wrapPixel = [this](Pixel &pixel) {
        bool transformed;
        do {
            transformed = false;
            if (pixel.getX() < 0) {
                pixel.transform(m_canvas.width, 0);
                transformed = true;
            }
            if (pixel.getY() < 0) {
                pixel.transform(0, m_canvas.height); // FIXME endless loop for height == 0
                transformed = true;
            }
            if (pixel.getX() >= m_canvas.width) {
                pixel.transform(-m_canvas.width, 0);
                transformed = true;
            }
            if (pixel.getY() >= m_canvas.height) {
                pixel.transform(0, -m_canvas.height);
                transformed = true;
            }
        } while (transformed);
    };

    for (auto & pixel : pixels) {
        wrapPixel(pixel);
    }
}
