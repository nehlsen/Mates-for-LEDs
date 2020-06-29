#ifndef MATES_RENDERABLE_H
#define MATES_RENDERABLE_H

#include <LedMatrix.h>
#include <Point.h>
#include <Pixel.h>

class Renderable
{
public:
    enum RenderMode {
        RenderModeOverwrite, // overwrite pixels on matrix
        RenderModeAdd,       // blend pixels with pixels on matrix (using ADD)
        RenderModeAverage,   // blend pixels with pixels on matrix (using average)
    };

    virtual void render(LedMatrix& matrix) const;
    virtual void render(LedMatrix& matrix, const Point &origin) const;
    virtual void render(LedMatrix& matrix, const Point &origin, RenderMode renderMode) const;

protected:
    virtual const Pixels& getPixelsToRender() const = 0;
};

#endif //MATES_RENDERABLE_H
