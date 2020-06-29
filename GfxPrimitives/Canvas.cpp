#include "Canvas.h"
//#include <QtCore/QDebug>

bool MatrixTransform::isIdentityMatrix() const
{
    return a == 1 && b == 0 && c == 0 && d == 1;
}

void MatrixTransform::reset()
{
    a = 1;
    b = 0;
    c = 0;
    d = 1;

    origin = {0, 0};
}

/* ****************************************************************************************************************** */

Canvas::Canvas():
    Canvas(Pixels())
{
}

Canvas::Canvas(const Pixels &pixels):
    m_matrixTransform(),
    m_pixels(pixels)
{

}

Canvas& Canvas::setPixels(const Pixels &pixels)
{
    m_pixels = pixels;

    return *this;
}

Pixels Canvas::pixels() const
{
    return m_pixels;
}

Canvas &Canvas::resetParameters()
{
    m_matrixTransform.reset();

    return *this;
}

Canvas &Canvas::applyTransformation(bool reset)
{
//    ESP_LOGI("Canvas", "applyTransformation: %.2f,%.2f,%.2f,%.2f (%d/%d)", m_matrixTransform.a, m_matrixTransform.b, m_matrixTransform.c, m_matrixTransform.d, m_matrixTransform.origin.x, m_matrixTransform.origin.y);

    for (auto & pixel : m_pixels) {
        int16_t x = std::round(m_matrixTransform.a * (pixel.getX() - m_matrixTransform.origin.x) + m_matrixTransform.b * (pixel.getY() - m_matrixTransform.origin.y));
        int16_t y = std::round(m_matrixTransform.c * (pixel.getX() - m_matrixTransform.origin.x) + m_matrixTransform.d * (pixel.getY() - m_matrixTransform.origin.y));

        pixel.setX(x + m_matrixTransform.origin.x);
        pixel.setY(y + m_matrixTransform.origin.y);
    }
    
    if (reset) {
        resetParameters();
    }
    
    return *this;
}

Canvas &Canvas::setRotation(int16_t degrees)
{
//    ESP_LOGI("GfxCanvas", "setRotation %d", degrees);

    degrees = degrees % 360;
    if (degrees < 0) degrees = 360 + degrees;
    degrees = 360 - degrees; // convert to clock wise

//    ESP_LOGI("GfxCanvas", "degrees %d", degrees);

    const double cRad2deg = 180.0/std::acos(-1);
    auto rad2deg = [cRad2deg](double rad) {
//        ESP_LOGI("GfxCanvas", "rad2deg %.2f * %.2f = %.2f", rad, cRad2deg, rad * cRad2deg);
        return rad * cRad2deg;
    };

    const double cDeg2rad = std::acos(-1)/180.0;
    auto deg2rad = [cDeg2rad](double rad) {
//        ESP_LOGI("GfxCanvas", "deg2rad %.2f * %.2f = %.2f", rad, cDeg2rad, rad * cDeg2rad);
        return rad * cDeg2rad;
    };

    const double degreesRadians = deg2rad(degrees);
    const double cosDegrees = /*rad2deg*/(std::cos(degreesRadians));
    const double sinDegrees = /*rad2deg*/(std::sin(degreesRadians));
//    ESP_LOGI("GfxCanvas", "cos %.2f, sin %.2f", cosDegrees, sinDegrees);

    return setMatrixTransform(
            cosDegrees,
            -sinDegrees,
            sinDegrees,
            cosDegrees
    );
}

Canvas &Canvas::setRotation(int16_t degrees, const Point &origin)
{
    setRotation(degrees);
    m_matrixTransform.origin = origin;

//    qDebug() << "setRotation" << degrees << origin.x << origin.y
//             << "bl" << getBottomLeft().x << getBottomLeft().y
//             << "rs" << getRelativeSize().width << getRelativeSize().height;

    return *this;
}

Canvas &Canvas::setMatrixTransform(double a, double b, double c, double d)
{
    m_matrixTransform.a = a;
    m_matrixTransform.b = b;
    m_matrixTransform.c = c;
    m_matrixTransform.d = d;
    
    return *this;
}

Canvas &Canvas::setMatrixTransform(double a, double b, double c, double d, const Point &origin)
{
    setMatrixTransform(a, b, c, d);
    m_matrixTransform.origin = origin;
    
    return *this;
}

Canvas &Canvas::setMatrixTransform(const MatrixTransform &matrixTransform)
{
    m_matrixTransform = matrixTransform;
    
    return *this;
}

MatrixTransform &Canvas::getMatrixTransform()
{
    return m_matrixTransform;
}

MatrixTransform Canvas::getMatrixTransform() const
{
    return m_matrixTransform;
}

Point Canvas::getBottomLeft() const
{
    if (pixels().empty()) {
        // FIXME this should be able to return an invalid point if this canvas has no pixels
        return {0, 0};
    }

    int16_t x = pixels().front().getX();
    int16_t y = pixels().front().getY();
    for (const Pixel &pixel : pixels()) {
        x = std::min(pixel.getX(), x);
        y = std::min(pixel.getY(), y);
    }

    return {x, y};
}

Point Canvas::getTopRight() const
{
    if (pixels().empty()) {
        // FIXME this should be able to return an invalid point if this canvas has no pixels
        return {0, 0};
    }

    int16_t x = pixels().front().getX();
    int16_t y = pixels().front().getY();
    for (const Pixel &pixel : pixels()) {
        x = std::max(pixel.getX(), x);
        y = std::max(pixel.getY(), y);
    }

    return {x, y};
}

Point Canvas::getCenter() const
{
    const Point &bl = getBottomLeft();
    const Size &rs = getRelativeSize();

    const int16_t x = bl.x + rs.width / 2;
    const int16_t y = bl.y + rs.height / 2;
    
    return {x, y};
}

Size Canvas::getRelativeSize() const
{
    // FIXME this should be able to return an invalid point if this canvas has no pixels

    const Point &tr = getTopRight();
    const Point &bl = getBottomLeft();
    int16_t w = tr.x - bl.x + 1;
    int16_t h = tr.y - bl.y + 1;

    return {w, h};
}

void Canvas::renderCentered(LedMatrix &matrix) const
{
    const Size &rs = getRelativeSize();

    // FIXME this seems broken
    //   especially if the canvas contains pixels with negative x/y

    Point renderBottomLeft = {
            int16_t((matrix.getWidth() - rs.width)/2 + 1),
            int16_t((matrix.getHeight() - rs.height)/2 + 1)
    };
//    qDebug() << "rs" << rs.width << rs.height << "rbl" << renderBottomLeft.x << renderBottomLeft.y;

    render(matrix, renderBottomLeft);
}

const Pixels& Canvas::getPixelsToRender() const
{
    return m_pixels;
}
