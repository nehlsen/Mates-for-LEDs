#include "unity.h"
#include <Circle.h>
#include "helper.h"

TEST_CASE("Circle: ctor, setter, getter", "[Matrix]")
{
    auto circle = Circle();
    circle.setBorderColor(CRGB::Red);

    // zero circle
    circle.setCenter(3, 3).setRadius(0);
    TEST_ASSERT_EQUAL(3, circle.getX());
    TEST_ASSERT_EQUAL(3, circle.getY());
    TEST_ASSERT_EQUAL(0, circle.getRadius());
    primitiveHasPixels(0, {}, circle, false);

    // smallest circle
    circle.setCenter(3, 3).setRadius(1);
    TEST_ASSERT_EQUAL(3, circle.getX());
    TEST_ASSERT_EQUAL(3, circle.getY());
    TEST_ASSERT_EQUAL(1, circle.getRadius());
    primitiveHasPixels(12, {
            {4, 3},
            {3, 4},
            {3, 2},
            {2, 3}
    }, circle, false);

    // full circle
    circle.setCenter(5, 5).setRadius(3);
    TEST_ASSERT_EQUAL(5, circle.getX());
    TEST_ASSERT_EQUAL(5, circle.getY());
    TEST_ASSERT_EQUAL(3, circle.getRadius());
    primitiveHasPixels(20, {
            {6, 8},
            {8, 6},
            {6, 2},
            {2, 6},
            {8, 4},
            {4, 8},
            {2, 4},
            {4, 2},
            {7, 3},
            {3, 7},
            {7, 7},
            {3, 3},
            {8, 5},
            {5, 8},
            {5, 2},
            {2, 5}
    }, circle, false);

    // this circle is clipped at the edge
    circle.setCenter(1, 2).setRadius(3);
    TEST_ASSERT_EQUAL(1, circle.getX());
    TEST_ASSERT_EQUAL(2, circle.getY());
    TEST_ASSERT_EQUAL(3, circle.getRadius());
    primitiveHasPixels(10, {
            {2, 5},
            {4, 3},
            {4, 1},
            {0, 5},
            {3, 4},
            {3, 0},
            {1, 5},
            {4, 2}
    }, circle, false);
}
