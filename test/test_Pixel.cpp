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