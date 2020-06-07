#ifndef MATRIX_GFXPRIMITIVE_H
#define MATRIX_GFXPRIMITIVE_H

#include "LedMatrix.h"
#include "Pixel.h"

class GfxPrimitive// rename to canvas?
{
public:
    virtual Pixels pixels() const;

    // add another primitive to this one, second overwrites first
    GfxPrimitive& merge(const GfxPrimitive& other);
    GfxPrimitive& merge(const Pixel& pixel);
    GfxPrimitive& merge(const Pixels &pixels);

    // create new primitive from this and other
    GfxPrimitive merged(const GfxPrimitive& other) const;
    GfxPrimitive merged(const Pixel& pixel) const;

    // add another primitive to this one, matching pixels are blended together
    GfxPrimitive& blend(const GfxPrimitive& other);

    // create new primitive from this and other
    GfxPrimitive blended(const GfxPrimitive& other) const;

    // change all pixels of primitive to be moved in x/y direction
    GfxPrimitive& transform(int16_t x, int16_t y);
    GfxPrimitive transformed(int16_t x, int16_t y) const;

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
        int16_t x;
        int16_t y;
        int16_t width;
        int16_t height;
        CanvasOptions options;

        bool transforms() const { return x != 0 || y != 0; }
        bool clipsOrWraps() const { return width != 0 || height != 0; }
    };
    // this will not change any pixels! options are applied in GfxPrimitive::render()
    // if width AND height are 0: width, height and options have no effect and will be ignored
    GfxPrimitive& setCanvas(int16_t x, int16_t y);
    GfxPrimitive& setCanvas(int16_t x, int16_t y, int16_t width, int16_t height, CanvasOptions options);
    GfxPrimitive& setCanvas(Canvas canvas);
    Canvas getCanvas() const;
    // get a list of pixels with canvas options applied
    Pixels mappedPixels() const;

    enum RenderMode {
        RenderModeOverwrite, // overwrite pixels on matrix
        RenderModeAdd,       // blend pixels with pixels on matrix (using ADD)
        RenderModeAverage,   // blend pixels with pixels on matrix (using average)
    };
    virtual void render(LedMatrix& matrix) const;
    virtual void render(LedMatrix& matrix, RenderMode renderMode) const;

protected:
    Pixels m_pixels;

    Canvas m_canvas = {0, 0, 0, 0, CanvasClipping};
    void canvasTransformPixels(Pixels& pixels) const;
    // only checks for width and height, canvas x/y transformation has to be already applied
    void canvasClipPixels(Pixels& pixels) const;
    void canvasWrapPixels(Pixels& pixels) const;
};

#endif //MATRIX_GFXPRIMITIVE_H
