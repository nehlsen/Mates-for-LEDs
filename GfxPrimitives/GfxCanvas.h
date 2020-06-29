#ifndef MATES_GFXCANVAS_H
#define MATES_GFXCANVAS_H

#include "GfxPrimitive.h"
#include "Size.h"

// TODO remove x/y transformation [DELXY]
class GfxCanvas : public GfxPrimitive
{
public:
    GfxCanvas();
    GfxCanvas(const GfxCanvas &other);
    explicit GfxCanvas(const GfxPrimitive &other);

    Pixels originalPixels() const;
    Pixels pixels() const override;

    // set canvas size AND position ON MATRIX
    //    0, 0 == canvas and matrix are same
    //   10,10 == canvas 0,0 -> matrix 10,10
    //   -5,-5 == canvas 0,0 -> matrix -5,-5 = OutOfBounds/Offscreen
    //            canvas 5,5 -> matrix  0, 0
    // set options ?
    //    wrap around OR clip ?
    //     moving to the side, out of the "canvas" wraps around OR drops pixels ?

    enum CanvasOptions {
        CanvasClipping,
        CanvasWrapAround,
    };
    struct Canvas {
        int16_t x; // TODO [DELXY]
        int16_t y; // TODO [DELXY]
        int16_t width;
        int16_t height;
        CanvasOptions options;

        bool transforms() const { return x != 0 || y != 0; } // TODO [DELXY]
        bool clipsOrWraps() const { return width != 0 || height != 0; }
    };
    // this will not change any pixels! options are applied in GfxPrimitive::render()
    // if width AND height are 0: width, height and options have no effect and will be ignored
    GfxCanvas& setCanvas(int16_t x, int16_t y); // TODO [DELXY]
    GfxCanvas& setCanvas(int16_t x, int16_t y, int16_t width, int16_t height, CanvasOptions options);
    GfxCanvas& setCanvas(Canvas canvas);
    Canvas getCanvas() const;
    // get a list of pixels with canvas options applied
    Pixels mappedPixels() const;

protected:
    Canvas m_canvas = {0, 0, 0, 0, CanvasClipping};
    void canvasTransformPixels(Pixels& pixels) const; // TODO [DELXY]
    // only checks for width and height, canvas x/y transformation has to be already applied
    void canvasClipPixels(Pixels& pixels) const;
    void canvasWrapPixels(Pixels& pixels) const;
};

#endif //MATES_GFXCANVAS_H
