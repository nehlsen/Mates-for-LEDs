#include "unity.h"
#include <Line.h>
#include "helper.h"

static void testLine(int expectedLength, PointList_t expectedPoints, const Line& line)
{
    primitiveHasPixels(expectedLength, expectedPoints, line);
}

static void printLine(const Line& line)
{
    dumpPixels(line);
}

TEST_CASE("Line: ctor, setter, getter", "[Matrix]")
{
    auto line = Line(1, 2, 3, 4);
    TEST_ASSERT_EQUAL(1, line.getX0());
    TEST_ASSERT_EQUAL(2, line.getY0());
    TEST_ASSERT_EQUAL(3, line.getX1());
    TEST_ASSERT_EQUAL(4, line.getY1());

    line.setStart(7, 8);
    TEST_ASSERT_EQUAL(7, line.getX0());
    TEST_ASSERT_EQUAL(8, line.getY0());
    TEST_ASSERT_EQUAL(3, line.getX1());
    TEST_ASSERT_EQUAL(4, line.getY1());

    line.setEnd(5, 6);
    TEST_ASSERT_EQUAL(7, line.getX0());
    TEST_ASSERT_EQUAL(8, line.getY0());
    TEST_ASSERT_EQUAL(5, line.getX1());
    TEST_ASSERT_EQUAL(6, line.getY1());

    auto anotherLine = Line();
    TEST_ASSERT_EQUAL(0, anotherLine.getX0());
    TEST_ASSERT_EQUAL(0, anotherLine.getY0());
    TEST_ASSERT_EQUAL(0, anotherLine.getX1());
    TEST_ASSERT_EQUAL(0, anotherLine.getY1());

    anotherLine.setStart(2, 3).setEnd(4, 5).setColor(CRGB(10, 20, 30));
    TEST_ASSERT_EQUAL(2, anotherLine.getX0());
    TEST_ASSERT_EQUAL(3, anotherLine.getY0());
    TEST_ASSERT_EQUAL(4, anotherLine.getX1());
    TEST_ASSERT_EQUAL(5, anotherLine.getY1());
    TEST_ASSERT_EQUAL(CRGB(10, 20, 30), anotherLine.getColor());
}

TEST_CASE("Line: straight Lines", "[Matrix]")
{
    auto lineUp = Line(0, 0, 0, 7);
    TEST_ASSERT_EQUAL(8, lineUp.pixels().size());
    testLine(8, {{0, 0}, {0, 2}, {0, 5}}, lineUp);
    
    auto lineDown = Line(5, 7, 5, 0);
    TEST_ASSERT_EQUAL(8, lineDown.pixels().size());
    testLine(8, {{5, 7}, {5, 2}, {5, 0}}, lineDown);

    auto lineRight = Line(5, 5, 9, 5);
    TEST_ASSERT_EQUAL(5, lineRight.pixels().size());
    testLine(5, {{5, 5,}, {7, 5}, {9, 5}}, lineRight);

    auto lineLeft = Line(5, 7, 1, 7);
    TEST_ASSERT_EQUAL(5, lineLeft.pixels().size());
    testLine(5, {{5, 7}, {3, 7}, {1, 7}}, lineLeft);
}

TEST_CASE("Line: 45 degree Lines", "[Matrix]")
{
    auto line45right = Line(3, 3, 6, 6);
    TEST_ASSERT_EQUAL(4, line45right.pixels().size());
    testLine(4, {{3, 3}, {4, 4}, {5, 5}, {6, 6}}, line45right);

    auto line45left = Line(7, 7, 3, 3);
    TEST_ASSERT_EQUAL(5, line45left.pixels().size());
    testLine(5, {{3, 3}, {4, 4}, {7, 7}}, line45left);
}

TEST_CASE("Line: steep Lines", "[Matrix]")
{
    auto lineSteepRight = Line(2, 2, 4, 9);
    TEST_ASSERT_EQUAL(8, lineSteepRight.pixels().size());
    PointList_t lineSteepRightPoints = {
            {2, 2},
            {2, 3},
            {3, 4},
            {3, 5},
            {3, 6},
            {3, 7},
            {4, 8},
            {4, 9}
    };
    testLine(8, lineSteepRightPoints, lineSteepRight);

    auto lineSteepLeft = Line(9, 2, 5, 9);
    TEST_ASSERT_EQUAL(8, lineSteepLeft.pixels().size());
    PointList_t lineSteepLeftPoints = {
            {9, 2},
            {8, 3},
            {8, 4},
            {7, 5},
            {7, 6},
            {6, 7},
            {6, 8},
            {5, 9}
    };
    testLine(8, lineSteepLeftPoints, lineSteepLeft);
}

TEST_CASE("Line: shallow Lines", "[Matrix]")
{
    auto lineShallowRight = Line(4, 7, 7, 5);
    TEST_ASSERT_EQUAL(4, lineShallowRight.pixels().size());
    PointList_t lineShallowRightPoints = {
            {4, 7},
            {5, 6},
            {6, 6},
            {7, 5}
    };
    testLine(4, lineShallowRightPoints, lineShallowRight);

    auto lineShallowLeft = Line(9, 2, 5, 4);
    TEST_ASSERT_EQUAL(5, lineShallowLeft.pixels().size());
    PointList_t lineShallowLeftPoints = {
            {5, 4},
            {6, 4},
            {7, 3},
            {8, 3},
            {9, 2}
    };
    testLine(5, lineShallowLeftPoints, lineShallowLeft);
}
