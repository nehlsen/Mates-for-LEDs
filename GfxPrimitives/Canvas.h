#ifndef MATES_CANVAS_H
#define MATES_CANVAS_H

#include <LedMatrix.h>
#include "Point.h"
#include "Size.h"
#include "Pixel.h"
#include "Renderable.h"

struct MatrixTransform {
    double a = 1;
    double b = 0;
    double c = 0;
    double d = 1;

    Point origin = {0, 0};

    bool isIdentityMatrix() const;
    void reset();
};

class Canvas : public Renderable
{
public:
    Canvas();
    explicit Canvas(const Pixels &pixels);
//    Canvas(const GfxPrimitive& other);

    Canvas& setPixels(const Pixels &pixels);
    // current pixels
    //   if transformation has been applied this will be changed
    Pixels pixels() const;

    // reset transformation parameters to identity matrix, keeps pixels
    Canvas& resetParameters();
    // apply transformation (and optionally reset parameters)
    Canvas& applyTransformation(bool reset = true);

    Canvas& setRotation(int16_t degrees);
    Canvas& setRotation(int16_t degrees, const Point &origin);

    Canvas& setZoom(int16_t percent);
    Canvas& setZoom(int16_t percent, const Point &origin);

    Canvas& setMatrixTransform(double a, double b, double c, double d);
    Canvas& setMatrixTransform(double a, double b, double c, double d, const Point &origin);
    Canvas& setMatrixTransform(const MatrixTransform &matrixTransform);
    MatrixTransform& getMatrixTransform();
    MatrixTransform getMatrixTransform() const;

    Point getBottomLeft() const;
    Point getTopRight() const;
    Point getCenter() const;
    Size getRelativeSize() const;

    void renderCentered(LedMatrix& matrix) const;

protected:
    const Pixels &getPixelsToRender() const override;

    MatrixTransform m_matrixTransform;
    Pixels m_pixels;
};

#endif //MATES_CANVAS_H
