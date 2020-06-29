#include "Renderable.h"

void Renderable::render(LedMatrix &matrix) const
{
    render(matrix, {0, 0}, RenderModeOverwrite);
}

void Renderable::render(LedMatrix &matrix, const Point &origin) const
{
    render(matrix, origin, RenderModeOverwrite);
}

void Renderable::render(LedMatrix &matrix, const Point &origin, Renderable::RenderMode renderMode) const
{
    for (const auto& pixel : getPixelsToRender()) {
        const int16_t x = pixel.getX() + origin.x;
        const int16_t y = pixel.getY() + origin.y;

        switch (renderMode) {
            default:
            case RenderModeOverwrite:
                matrix.pixel(x, y) = pixel.getColor();
                break;
            case RenderModeAdd:
                matrix.pixel(x, y) += pixel.getColor();
                break;
            case RenderModeAverage:
                matrix.pixel(x, y) = matrix.pixel(x, y).lerp8(pixel.getColor(), 128);
                break;
        }
    }
}
