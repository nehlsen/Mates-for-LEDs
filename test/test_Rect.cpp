#include "unity.h"
#include <Rect.h>
#include "helper.h"

TEST_CASE("Rect: ctor, setter, getter", "[Matrix]")
{
    auto rect = Rect(1, 2, 3, 3);
    TEST_ASSERT_EQUAL(1, rect.getX0());
    TEST_ASSERT_EQUAL(2, rect.getY0());
    TEST_ASSERT_EQUAL(3, rect.getWidth());
    TEST_ASSERT_EQUAL(3, rect.getHeight());
    TEST_ASSERT_EQUAL(3, rect.getX1());
    TEST_ASSERT_EQUAL(4, rect.getY1());

    rect.setStart(7, 8);
    TEST_ASSERT_EQUAL(7, rect.getX0());
    TEST_ASSERT_EQUAL(8, rect.getY0());
    TEST_ASSERT_EQUAL(3, rect.getWidth());
    TEST_ASSERT_EQUAL(3, rect.getHeight());
    TEST_ASSERT_EQUAL(9, rect.getX1());
    TEST_ASSERT_EQUAL(10, rect.getY1());

    rect.setEnd(5, 6);
    TEST_ASSERT_EQUAL(5, rect.getX0());
    TEST_ASSERT_EQUAL(6, rect.getY0());
    TEST_ASSERT_EQUAL(3, rect.getWidth());
    TEST_ASSERT_EQUAL(3, rect.getHeight());
    TEST_ASSERT_EQUAL(7, rect.getX1());
    TEST_ASSERT_EQUAL(8, rect.getY1());

    auto anotherRect = Rect();
    TEST_ASSERT_EQUAL(0, anotherRect.getX0());
    TEST_ASSERT_EQUAL(0, anotherRect.getY0());
    TEST_ASSERT_EQUAL(0, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(0, anotherRect.getHeight());
    TEST_ASSERT_EQUAL(0, anotherRect.getX1());
    TEST_ASSERT_EQUAL(0, anotherRect.getY1());

    anotherRect.setStart(2, 3).setEnd(4, 5).setBorderColor(CRGB(10, 20, 30));
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(4, anotherRect.getX1());
    TEST_ASSERT_EQUAL(5, anotherRect.getY1());
    TEST_ASSERT_EQUAL(CRGB(10, 20, 30), anotherRect.getBorderColor());
    TEST_ASSERT_EQUAL(3, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(3, anotherRect.getHeight());

    anotherRect.setWidth(7);
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(8, anotherRect.getX1());
    TEST_ASSERT_EQUAL(5, anotherRect.getY1());
    TEST_ASSERT_EQUAL(7, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(3, anotherRect.getHeight());

    anotherRect.setHeight(5);
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(8, anotherRect.getX1());
    TEST_ASSERT_EQUAL(7, anotherRect.getY1());
    TEST_ASSERT_EQUAL(7, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(5, anotherRect.getHeight());

    anotherRect.setStart(0, 0).setSize(0, 0);
    TEST_ASSERT_EQUAL(0, anotherRect.getX0());
    TEST_ASSERT_EQUAL(0, anotherRect.getY0());
    TEST_ASSERT_EQUAL(0, anotherRect.getX1());
    TEST_ASSERT_EQUAL(0, anotherRect.getY1());
    TEST_ASSERT_EQUAL(0, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(0, anotherRect.getHeight());

    anotherRect.setStart(0, 0).setSize(11, 13);
    TEST_ASSERT_EQUAL(0, anotherRect.getX0());
    TEST_ASSERT_EQUAL(0, anotherRect.getY0());
    TEST_ASSERT_EQUAL(10, anotherRect.getX1());
    TEST_ASSERT_EQUAL(12, anotherRect.getY1());
    TEST_ASSERT_EQUAL(11, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(13, anotherRect.getHeight());

    anotherRect.setStart(7, 9).setEnd(2, 4);
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(4, anotherRect.getY0());
    TEST_ASSERT_EQUAL(7, anotherRect.getX1());
    TEST_ASSERT_EQUAL(9, anotherRect.getY1());
    TEST_ASSERT_EQUAL(6, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(6, anotherRect.getHeight());
}

TEST_CASE("Rect: paint, zero", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(0, 0);
    primitiveHasPixels(0, {}, rect);

    rect.setStart(5, 1);
    primitiveHasPixels(0, {}, rect);
}

TEST_CASE("Rect: paint, 1px", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(1, 1);
    primitiveHasPixels(1, {{0, 0}}, rect);

    rect.setStart(0, 0).setEnd(0, 0);
    primitiveHasPixels(1, {{0, 0}}, rect);

    rect.setStart(5, 1).setSize(1, 1);
    primitiveHasPixels(1, {{5, 1}}, rect);

    rect.setStart(5, 1).setEnd(5, 1);
    primitiveHasPixels(1, {{5, 1}}, rect);
}

TEST_CASE("Rect: paint, cube", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(2, 2);
    primitiveHasPixels(4, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, rect);

    rect.setStart(0, 0).setEnd(1, 1);
    primitiveHasPixels(4, {{0, 0}, {0, 1}, {1, 0}, {1, 1}}, rect);

    rect.setStart(4, 5).setSize(2, 2);
    primitiveHasPixels(4, {{4, 5}, {5, 5}, {4, 6}, {5, 6}}, rect);

    rect.setStart(7, 3).setEnd(8, 4);
    primitiveHasPixels(4, {{7, 3}, {7, 4}, {8, 3}, {8, 4}}, rect);

    rect.setStart(7, 3).setEnd(6, 2);
    primitiveHasPixels(4, {{6, 2}, {7, 2}, {6, 3}, {7, 3}}, rect);
}

TEST_CASE("Rect: paint, horizontal line", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(3, 0);
    primitiveHasPixels(3, {{0, 0}, {1, 0}, {2, 0}}, rect);
    primitiveNotHasPixels({{3, 0}}, rect);
}

TEST_CASE("Rect: paint, vertical line", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(0, 3);
    primitiveHasPixels(3, {{0, 0}, {0, 1}, {0, 2}}, rect);
    primitiveNotHasPixels({{0, 3}}, rect);
}

TEST_CASE("Rect: paint, empty rect", "[Matrix]")
{
    auto rect = Rect().setStart(0, 0).setSize(3, 3);
    primitiveHasPixels(12, {{0, 0}, {0, 2}, {2, 0}, {2, 2}}, rect);
    primitiveNotHasPixels({{1, 1}}, rect);

    rect.setSize(4, 4);
    primitiveHasPixels(16, {{0, 0}, {0, 3}, {3, 0}, {3, 3}}, rect);
    primitiveNotHasPixels({{1, 1}, {1, 2}, {2, 1}, {2, 2}}, rect);
}

TEST_CASE("Rect: paint, filled rect", "[Matrix]")
{
    auto rect = Rect(0, 0, 3, 3, CRGB(255, 0, 0)).setFillColor(CRGB(0, 255, 0));
    primitiveHasPixels(13, {{0, 0}, {0, 2}, {2, 0}, {2, 2}}, rect);

    rect.setSize(4, 4);
    primitiveHasPixels(20, {{0, 0}, {0, 3}, {3, 0}, {3, 3}}, rect);
}