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
