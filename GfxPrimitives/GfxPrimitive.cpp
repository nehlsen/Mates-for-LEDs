#include "GfxPrimitive.h"
#include "PixelMap.h"

Pixels GfxPrimitive::pixels() const
{
    return m_pixels;
}

GfxPrimitive& GfxPrimitive::merge(const GfxPrimitive &other)
{
    return merge(other.pixels());
}

GfxPrimitive &GfxPrimitive::merge(const Pixel &pixel)
{
    m_pixels = PixelMap::fromPixels(pixels()).add(pixel).toPixels();

    return *this;
}

GfxPrimitive& GfxPrimitive::merge(const Pixels &pixelsToAdd)
{
    m_pixels = PixelMap::fromPixels(pixels()).add(pixelsToAdd).toPixels();

    return *this;
}

GfxPrimitive GfxPrimitive::merged(const GfxPrimitive &other) const
{
    return GfxPrimitive(*this).merge(other);
}

GfxPrimitive GfxPrimitive::merged(const Pixel &pixel) const
{
    return GfxPrimitive(*this).merge(pixel);
}

GfxPrimitive& GfxPrimitive::blend(const GfxPrimitive &other)
{
    auto thisPixels = PixelMap::fromPixels(pixels());
    auto otherPixels = PixelMap::fromPixels(other.pixels());

    for (auto it = otherPixels.begin(); it != otherPixels.end(); ++it) {
        if (thisPixels.has(it->second)) {
            Pixel thisPixel = thisPixels.at(it->second);
            thisPixels.erase(it->first);
            thisPixel.setColor(thisPixel.getColor().lerp8(it->second.getColor(), 128));
            thisPixels.add(thisPixel);
        } else {
            thisPixels.add(it->second);
        }
    }

    m_pixels = thisPixels.toPixels();

    return *this;
}

GfxPrimitive GfxPrimitive::blended(const GfxPrimitive &other) const
{
    return GfxPrimitive(*this).blend(other);
}

GfxPrimitive &GfxPrimitive::transform(int16_t x, int16_t y)
{
    for (auto& pixel : m_pixels) {
        pixel.transform(x, y);
    }

    return *this;
}

GfxPrimitive GfxPrimitive::transformed(int16_t x, int16_t y) const
{
    return GfxPrimitive(*this).transform(x, y);
}

GfxPrimitive &GfxPrimitive::setCanvas(int16_t x, int16_t y)
{
    return setCanvas(x, y, 0, 0, CanvasClipping);
}

GfxPrimitive& GfxPrimitive::setCanvas(int16_t x, int16_t y, int16_t width, int16_t height, GfxPrimitive::CanvasOptions options)
{
    return setCanvas({x, y, width, height, options});
}

GfxPrimitive &GfxPrimitive::setCanvas(GfxPrimitive::Canvas canvas)
{
    m_canvas = canvas;
    return *this;
}

GfxPrimitive::Canvas GfxPrimitive::getCanvas() const
{
    return m_canvas;
}

Pixels GfxPrimitive::mappedPixels() const
{
    // if canvas has no x AND no y -> no transform
    // if canvas has no w AND no h -> no clipping/wrapping
    if (!m_canvas.transforms() && !m_canvas.clipsOrWraps() && !m_canvas.matrixTransform.does()) {
        return pixels();
    }

    Pixels pixels_mapped = pixels();
    canvasTransformPixels(pixels_mapped);
    canvasClipPixels(pixels_mapped);
    canvasWrapPixels(pixels_mapped);

    applyMatrixTransformation(pixels_mapped);

    return pixels_mapped;
}

GfxPrimitive & GfxPrimitive::setRotation(int16_t degrees)
{
    return setMatrixTransform(
            std::cos(degrees),
            -std::sin(degrees),
            std::sin(degrees),
            std::cos(degrees)
            );
}

GfxPrimitive & GfxPrimitive::setMatrixTransform(int16_t a, int16_t b, int16_t c, int16_t d)
{
    m_canvas.matrixTransform.a = a;
    m_canvas.matrixTransform.b = b;
    m_canvas.matrixTransform.c = c;
    m_canvas.matrixTransform.d = d;

    return *this;
}

void GfxPrimitive::render(LedMatrix &matrix) const
{
    render(matrix, RenderModeOverwrite);
}

void GfxPrimitive::render(LedMatrix &matrix, RenderMode renderMode) const
{
    for (const auto& pixel : mappedPixels()) {
        switch (renderMode) {
            default:
            case RenderModeOverwrite:
                matrix.pixel(pixel.getX(), pixel.getY()) = pixel.getColor();
                break;
            case RenderModeAdd:
                matrix.pixel(pixel.getX(), pixel.getY()) += pixel.getColor();
                break;
            case RenderModeAverage:
                matrix.pixel(pixel.getX(), pixel.getY()) = matrix.pixel(pixel.getX(), pixel.getY()).lerp8(pixel.getColor(), 128);
                break;
        }
    }
}

void GfxPrimitive::canvasTransformPixels(Pixels& pixels) const
{
    if (!m_canvas.transforms()) {
        return;
    }

    for (auto& pixel : pixels) {
        pixel.transform(m_canvas.x, m_canvas.y);
    }
}

void GfxPrimitive::canvasClipPixels(Pixels &pixels) const
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

void GfxPrimitive::canvasWrapPixels(Pixels &pixels) const
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

void GfxPrimitive::applyMatrixTransformation(Pixels &pixels) const
{
    auto applyTransformation = [this](Pixel &pixel) {
        const int16_t x = m_canvas.matrixTransform.a * pixel.getX() + m_canvas.matrixTransform.b * pixel.getY();
        const int16_t y = m_canvas.matrixTransform.c * pixel.getX() + m_canvas.matrixTransform.d * pixel.getY();
        pixel.setX(x);
        pixel.setY(y);
    };

    for (auto & pixel : pixels) {
        applyTransformation(pixel);
    }
}
