#include "unity.h"
#include <Pixel.h>

TEST_CASE("Pixel: ctor/getter/setter", "[Matrix]")
{
    auto pixel = Pixel(3, 7, CRGB(0));
    TEST_ASSERT_EQUAL(3, pixel.getX());
    TEST_ASSERT_EQUAL(7, pixel.getY());
    TEST_ASSERT_EQUAL(0, pixel.getColor());

    pixel.setX(21);
    TEST_ASSERT_EQUAL(21, pixel.getX());
    TEST_ASSERT_EQUAL(7, pixel.getY());

    pixel.setY(42);
    TEST_ASSERT_EQUAL(21, pixel.getX());
    TEST_ASSERT_EQUAL(42, pixel.getY());

    pixel.setX(-3);
    TEST_ASSERT_EQUAL(-3, pixel.getX());
    TEST_ASSERT_EQUAL(42, pixel.getY());

    pixel.setY(-7);
    TEST_ASSERT_EQUAL(-3, pixel.getX());
    TEST_ASSERT_EQUAL(-7, pixel.getY());

    auto pointedPixel = Pixel({9,8}, CRGB(0));
    TEST_ASSERT_EQUAL(9, pointedPixel.getX());
    TEST_ASSERT_EQUAL(8, pointedPixel.getY());
    TEST_ASSERT_EQUAL(9, pointedPixel.getLocation().x);
    TEST_ASSERT_EQUAL(8, pointedPixel.getLocation().y);

    auto someLocation = Point({-3, 14});
    pointedPixel.setLocation(someLocation);
    TEST_ASSERT_EQUAL(someLocation.x, pointedPixel.getX());
    TEST_ASSERT_EQUAL(someLocation.y, pointedPixel.getY());
    TEST_ASSERT_EQUAL(someLocation.x, pointedPixel.getLocation().x);
    TEST_ASSERT_EQUAL(someLocation.y, pointedPixel.getLocation().y);
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

    pixel.transform(-5, -5);
    TEST_ASSERT_EQUAL(-2, pixel.getX());
    TEST_ASSERT_EQUAL(-2, pixel.getY());
}
