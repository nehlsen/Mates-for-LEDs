#include "unity.h"
#include <GfxPrimitive.h>
#include <GfxCanvas.h>
#include <Rect.h>
#include <Line.h>
#include "helper.h"

TEST_CASE("GfxCanvas: setCanvas 1 - x/y", "[Matrix]")
{
    const Rect testRect(0, 0, 2, 2, CRGB::Red);

    // canvas: x+1 y+0
    auto bottomLeftRect = GfxCanvas(testRect);
    bottomLeftRect.setCanvas(1, 0);
//    primitiveHasPixels(4, {
//            {0, 0},
//            {0, 1},
//            {1, 0},
//            {1, 1}
//    }, bottomLeftRect, false);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels(), false));

    // canvas: x+0 y+1
    bottomLeftRect = GfxCanvas(testRect);
    bottomLeftRect.setCanvas(0, 1);
//    primitiveHasPixels(4, {
//            {0, 0},
//            {0, 1},
//            {1, 0},
//            {1, 1}
//    }, bottomLeftRect, false);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels(), false));

    // canvas: x-1 y+0
    bottomLeftRect = GfxCanvas(testRect);
    bottomLeftRect.setCanvas(-1, 0);
//    primitiveHasPixels(4, {
//            {0, 0},
//            {0, 1},
//            {1, 0},
//            {1, 1}
//    }, bottomLeftRect, false);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({-1, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({-1, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));

    // canvas: x+0 y-1
    bottomLeftRect = GfxCanvas(testRect);
    bottomLeftRect.setCanvas(0, -1);
//    primitiveHasPixels(4, {
//            {0, 0},
//            {0, 1},
//            {1, 0},
//            {1, 1}
//    }, bottomLeftRect, false);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, -1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, -1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));

    // canvas: x+5 y-9
    bottomLeftRect = GfxCanvas(testRect);
    bottomLeftRect.setCanvas(5, -9);
//    primitiveHasPixels(4, {
//            {0, 0},
//            {0, 1},
//            {1, 0},
//            {1, 1}
//    }, bottomLeftRect, false);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({5, -9}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({5, -8}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({6, -9}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({6, -8}, bottomLeftRect.mappedPixels(), false));
}

TEST_CASE("GfxCanvas: setCanvas 2 - clipping", "[Matrix]")
{
    const Rect testRect(0, 0, 2, 2, CRGB::Red);

    // 2x2 canvas, 2x2 rect transform x+1
    auto bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 2, 2, GfxCanvas::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(1, 0);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));

    // 2x2 canvas, 2x2 rect transform y+1
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 2, 2, GfxCanvas::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(0, 1);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));

    // 2x2 canvas, 2x2 rect transform x-1
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 2, 2, GfxCanvas::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(-1, 0);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));

    // 2x2 canvas, 2x2 rect transform y-1
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 2, 2, GfxCanvas::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(0, -1);
    TEST_ASSERT_EQUAL(2, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));

    // 2x2 canvas, 2x2 rect transform x-1,y-1
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 2, 2, GfxCanvas::CanvasClipping);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(-1, -1);
    TEST_ASSERT_EQUAL(1, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
}

TEST_CASE("GfxCanvas: setCanvas 3 - wrap around", "[Matrix]")
{
    const Rect testRect(0, 0, 2, 2, CRGB::Red);

    // 3x3 canvas, 2x2 rect transform x+2
    auto bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 3, 3, GfxCanvas::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(2, 0);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));

    // 3x3 canvas, 2x2 rect transform y+2
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 3, 3, GfxCanvas::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(0, 2);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels(), false));

    // 3x3 canvas, 2x2 rect transform x-2
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 3, 3, GfxCanvas::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(-2, 0);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({1, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 1}, bottomLeftRect.mappedPixels(), false));

    // 3x3 canvas, 2x2 rect transform y-2
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 3, 3, GfxCanvas::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(0, -2);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({0, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 1}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({1, 2}, bottomLeftRect.mappedPixels(), false));

    // 3x3 canvas, 2x2 rect transform x-1,y-1
    bottomLeftRect = GfxCanvas(testRect);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);

    bottomLeftRect.setCanvas(0, 0, 3, 3, GfxCanvas::CanvasWrapAround);
    primitiveHasPixels(4, {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1}
    }, bottomLeftRect, false);
    bottomLeftRect.transform(-1, -1);
    TEST_ASSERT_EQUAL(4, bottomLeftRect.mappedPixels().size());
    TEST_ASSERT(pointInListOfPixels({2, 2}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({2, 0}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 2}, bottomLeftRect.mappedPixels(), false));
    TEST_ASSERT(pointInListOfPixels({0, 0}, bottomLeftRect.mappedPixels(), false));
}
