#include "unity.h"
#include <Pixel.h>

TEST_CASE("Pixel: 1", "[Matrix]")
{
    auto pixel = Pixel(3, 7, CRGB(0));
    TEST_ASSERT_EQUAL(3, pixel.getX());
    TEST_ASSERT_EQUAL(7, pixel.getY());
    TEST_ASSERT_EQUAL(0, pixel.getColor());

    pixel.setX(21);
    TEST_ASSERT_EQUAL(21, pixel.getX());

    pixel.setY(42);
    TEST_ASSERT_EQUAL(42, pixel.getY());
}

TEST_CASE("Pixel: transform", "[Matrix]")
{
    auto pixel = Pixel(3, 7, CRGB(0));
    TEST_ASSERT_EQUAL(3, pixel.getX());
    TEST_ASSERT_EQUAL(7, pixel.getY());

    pixel.transform(1, 0);
    TEST_ASSERT_EQUAL(4, pixel.getX());
    TEST_ASSERT_EQUAL(7, pixel.getY());

    pixel.transform(0, 1);
    TEST_ASSERT_EQUAL(4, pixel.getX());
    TEST_ASSERT_EQUAL(8, pixel.getY());

    pixel.transform(2, 1);
    TEST_ASSERT_EQUAL(6, pixel.getX());
    TEST_ASSERT_EQUAL(9, pixel.getY());

    pixel.transform(-3, -6);
    TEST_ASSERT_EQUAL(3, pixel.getX());
    TEST_ASSERT_EQUAL(3, pixel.getY());

    // TODO transform below 0 ?!
    pixel.transform(-5, -5);
    TEST_ASSERT_EQUAL(0, pixel.getX());
    TEST_ASSERT_EQUAL(0, pixel.getY());
}
