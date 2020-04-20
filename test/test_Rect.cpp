#include "unity.h"
#include <Rect.h>

TEST_CASE("Rect: ctor, setter, getter", "[Matrix]")
{
    auto rect = Rect(1, 2, 3, 4);
    TEST_ASSERT_EQUAL(1, rect.getX0());
    TEST_ASSERT_EQUAL(2, rect.getY0());
    TEST_ASSERT_EQUAL(3, rect.getX1());
    TEST_ASSERT_EQUAL(4, rect.getY1());
    TEST_ASSERT_EQUAL(2, rect.getWidth());
    TEST_ASSERT_EQUAL(2, rect.getHeight());

    rect.setStart(7, 8);
    TEST_ASSERT_EQUAL(7, rect.getX0());
    TEST_ASSERT_EQUAL(8, rect.getY0());
    TEST_ASSERT_EQUAL(3, rect.getX1());
    TEST_ASSERT_EQUAL(4, rect.getY1());
    TEST_ASSERT_EQUAL(4, rect.getWidth());
    TEST_ASSERT_EQUAL(4, rect.getHeight());

    rect.setEnd(5, 6);
    TEST_ASSERT_EQUAL(7, rect.getX0());
    TEST_ASSERT_EQUAL(8, rect.getY0());
    TEST_ASSERT_EQUAL(5, rect.getX1());
    TEST_ASSERT_EQUAL(6, rect.getY1());
    TEST_ASSERT_EQUAL(2, rect.getWidth());
    TEST_ASSERT_EQUAL(2, rect.getHeight());

    auto anotherRect = Rect();
    TEST_ASSERT_EQUAL(0, anotherRect.getX0());
    TEST_ASSERT_EQUAL(0, anotherRect.getY0());
    TEST_ASSERT_EQUAL(0, anotherRect.getX1());
    TEST_ASSERT_EQUAL(0, anotherRect.getY1());
    TEST_ASSERT_EQUAL(0, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(0, anotherRect.getHeight());

    anotherRect.setStart(2, 3).setEnd(4, 5).setColor(CRGB(10, 20, 30));
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(4, anotherRect.getX1());
    TEST_ASSERT_EQUAL(5, anotherRect.getY1());
    TEST_ASSERT_EQUAL(CRGB(10, 20, 30), anotherRect.getColor());
    TEST_ASSERT_EQUAL(2, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(2, anotherRect.getHeight());

    anotherRect.setWidth(7);
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(9, anotherRect.getX1());
    TEST_ASSERT_EQUAL(5, anotherRect.getY1());
    TEST_ASSERT_EQUAL(7, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(2, anotherRect.getHeight());

    anotherRect.setHeight(5);
    TEST_ASSERT_EQUAL(2, anotherRect.getX0());
    TEST_ASSERT_EQUAL(3, anotherRect.getY0());
    TEST_ASSERT_EQUAL(9, anotherRect.getX1());
    TEST_ASSERT_EQUAL(8, anotherRect.getY1());
    TEST_ASSERT_EQUAL(7, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(5, anotherRect.getHeight());

    anotherRect.setStart(0, 0).setSize(11, 13);
    TEST_ASSERT_EQUAL(0, anotherRect.getX0());
    TEST_ASSERT_EQUAL(0, anotherRect.getY0());
    TEST_ASSERT_EQUAL(11, anotherRect.getX1());
    TEST_ASSERT_EQUAL(13, anotherRect.getY1());
    TEST_ASSERT_EQUAL(11, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(13, anotherRect.getHeight());

    anotherRect.setStart(7, 9).setEnd(2, 4);
    TEST_ASSERT_EQUAL(7, anotherRect.getX0());
    TEST_ASSERT_EQUAL(9, anotherRect.getY0());
    TEST_ASSERT_EQUAL(2, anotherRect.getX1());
    TEST_ASSERT_EQUAL(4, anotherRect.getY1());
    TEST_ASSERT_EQUAL(5, anotherRect.getWidth());
    TEST_ASSERT_EQUAL(5, anotherRect.getHeight());
}
