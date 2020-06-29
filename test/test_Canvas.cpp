#include "unity.h"
#include <Line.h>
#include <Canvas.h>
#include "helper.h"

TEST_CASE("Canvas: rotate", "[Matrix][Canvas]")
{
    const Line testLine(0, 0, 2, 0, CRGB::Red);

    auto testCanvas = Canvas(testLine.pixels());
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels());
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    // rotate 90 degrees counter-clockwise
    testCanvas.setPixels(testLine.pixels()).setMatrixTransform(0, -1, 1, 0).applyTransformation();
    expectPixels(3, {{0, 0}, {0, 1}, {0, 2}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(90).applyTransformation();
    expectPixels(3, {{0, 0}, {0, -1}, {0, -2}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(270).applyTransformation();
    expectPixels(3, {{0, 0}, {0, 1}, {0, 2}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(-90).applyTransformation();
    expectPixels(3, {{0, 0}, {0, 1}, {0, 2}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(0).applyTransformation();
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(360).applyTransformation();
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(30).applyTransformation();
    expectPixels(3/* one pixel is doubled */, {{0, 0}, {1, -1}}, testCanvas.pixels(), false);
}

TEST_CASE("Canvas: rotate - origin", "[Matrix][Canvas]")
{
    const Line testLine(0, 0, 2, 0, CRGB::Red);

    Canvas testCanvas;

    testCanvas.setPixels(testLine.pixels()).setRotation(90, {1, 0}).applyTransformation();
    expectPixels(3, {{1, 1}, {1, 0}, {1, -1}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(270, {1, 0}).applyTransformation();
    expectPixels(3, {{1, 1}, {1, 0}, {1, -1}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(-90, {1, 0}).applyTransformation();
    expectPixels(3, {{1, 1}, {1, 0}, {1, -1}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(0, {1, 0}).applyTransformation();
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(360, {1, 0}).applyTransformation();
    expectPixels(3, {{0, 0}, {1, 0}, {2, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(30, {1, 0}).applyTransformation();
    expectPixels(3, {{1, 0}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(45, {1, 0}).applyTransformation();
    expectPixels(3, {{0, 1}, {1, 0}, {2, -1}}, testCanvas.pixels(), false);


    testCanvas.setPixels(testLine.pixels()).setRotation(90, {2, 0}).applyTransformation();
    expectPixels(3, {{2, 0}, {2, 1}, {2, 2}}, testCanvas.pixels(), false);

    testCanvas.setPixels(testLine.pixels()).setRotation(90, {2, 2}).applyTransformation();
    expectPixels(3, {{0, 2}, {0, 3}, {0, 4}}, testCanvas.pixels(), false);
}
