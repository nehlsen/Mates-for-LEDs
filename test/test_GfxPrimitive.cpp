#include "unity.h"
#include <GfxPrimitive.h>
#include <Line.h>
#include <Rect.h>
#include "helper.h"

TEST_CASE("GfxPrimitive: merge", "[Matrix]")
{
    auto greenLine = Line(0, 0, 0, 0, CRGB(0, 255, 0));
    TEST_ASSERT_EQUAL(1, greenLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(0, 255, 0), greenLine.pixels()[0].getColor());

    auto redLine = Line(0, 0, 0, 0, CRGB(255, 0, 0));
    TEST_ASSERT_EQUAL(1, redLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(255, 0, 0), redLine.pixels()[0].getColor());

    greenLine.merge(redLine);
    TEST_ASSERT_EQUAL(1, greenLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(255, 0, 0), greenLine.pixels()[0].getColor());
}

TEST_CASE("GfxPrimitive: blend", "[Matrix]")
{
    auto greenLine = Line(0, 0, 0, 0, CRGB(0, 255, 0));
    TEST_ASSERT_EQUAL(1, greenLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(0, 255, 0), greenLine.pixels()[0].getColor());

    auto redLine = Line(0, 0, 0, 0, CRGB(255, 0, 0));
    TEST_ASSERT_EQUAL(1, redLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(255, 0, 0), redLine.pixels()[0].getColor());

    greenLine.blend(redLine);
    TEST_ASSERT_EQUAL(1, greenLine.pixels().size());
    TEST_ASSERT_COLOR(CRGB(128, 127, 0), greenLine.pixels()[0].getColor());
}

TEST_CASE("GfxPrimitive: transform", "[Matrix]")
{
    // TODO test transform
    TEST_IGNORE_MESSAGE("TODO");
}

TEST_CASE("GfxPrimitive: setCanvas 1 - x/y", "[Matrix]")
{
    // canvas: x+1 y+0
    auto bottomLeftRect = Rect(0, 0, 2, 2);
    bottomLeftRect.setCanvas(1, 0);
    primitiveHasPixels(4, {
        {0, 0}, {0, 1}, {1, 0}, {1, 1}
        }, bottomLeftRect);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels()));

    // canvas: x+0 y+1
    bottomLeftRect = Rect(0, 0, 2, 2);
    bottomLeftRect.setCanvas(0, 1);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels()));

    // canvas: x-1 y+0
    bottomLeftRect = Rect(0, 0, 2, 2);
    bottomLeftRect.setCanvas(-1, 0);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({-1, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({-1, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));

    // canvas: x+0 y-1
    bottomLeftRect = Rect(0, 0, 2, 2);
    bottomLeftRect.setCanvas(0, -1);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, -1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, -1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));

    // canvas: x+5 y-9
    bottomLeftRect = Rect(0, 0, 2, 2);
    bottomLeftRect.setCanvas(5, -9);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({5, -9}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({5, -8}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({6, -9}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({6, -8}, bottomLeftRect.mappedPixels()));
}

TEST_CASE("GfxPrimitive: setCanvas 2 - clipping", "[Matrix]")
{
    // 2x2 canvas, 2x2 rect transform x+1
    auto bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 2, 2, Rect::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(1, 0);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));

    // 2x2 canvas, 2x2 rect transform y+1
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 2, 2, Rect::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(0, 1);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));

    // 2x2 canvas, 2x2 rect transform x-1
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 2, 2, Rect::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(-1, 0);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));

    // 2x2 canvas, 2x2 rect transform y-1
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 2, 2, Rect::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(0, -1);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));

    // 2x2 canvas, 2x2 rect transform x-1,y-1
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 2, 2, Rect::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(-1, -1);
    TEST_ASSERT_EQUAL(1, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
}

TEST_CASE("GfxPrimitive: setCanvas 3 - wrap around", "[Matrix]")
{
    // 3x3 canvas, 2x2 rect transform x+2
    auto bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 3, 3, Rect::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(2, 0);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));

    // 3x3 canvas, 2x2 rect transform y+2
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 3, 3, Rect::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(0, 2);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels()));

    // 3x3 canvas, 2x2 rect transform x-2
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 3, 3, Rect::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(-2, 0);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels()));

    // 3x3 canvas, 2x2 rect transform y-2
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 3, 3, Rect::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(0, -2);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels()));

    // 3x3 canvas, 2x2 rect transform x-1,y-1
    bottomLeftRect = Rect(0, 0, 2, 2);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);

    bottomLeftRect.setCanvas(0, 0, 3, 3, Rect::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0}, {0, 1}, {1, 0}, {1, 1}
    }, bottomLeftRect);
    bottomLeftRect.transform(-1, -1);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({2, 2}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels()));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels()));
}
