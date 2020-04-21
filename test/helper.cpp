#include "helper.h"
#include "unity.h"

bool primitiveHasPoint(Point_t point, const GfxPrimitive& primitive)
{
    for (const Pixel& pixel: primitive.pixels()) {
        if (pixel.getX() == point.first && pixel.getY() == point.second) {
            return true;
        }
    }

    return false;
}

void primitiveHasPixels(int expectedPixelCount, PointList_t expectedPoints, const GfxPrimitive& primitive)
{
    char assertMessage[52];
    sprintf(assertMessage, "Expected gfx-primitive to have %d Points got %d", expectedPixelCount, primitive.pixels().size());
    TEST_ASSERT_EQUAL_MESSAGE(expectedPixelCount, primitive.pixels().size(), assertMessage);

    while (!expectedPoints.empty()) {
        Point_t point = expectedPoints.back();

        sprintf(assertMessage, "Expected Point (%d,%d) not found on gfx-primitive", point.first, point.second);
        TEST_ASSERT_MESSAGE(primitiveHasPoint(point, primitive), assertMessage);
        expectedPoints.pop_back();
    }
}

void primitiveNotHasPixels(PointList_t notExpectedPoints, const GfxPrimitive& primitive)
{
    char assertMessage[52];

    while (!notExpectedPoints.empty()) {
        Point_t point = notExpectedPoints.back();

        sprintf(assertMessage, "Not expected Point (%d,%d) found on gfx-primitive", point.first, point.second);
        TEST_ASSERT_MESSAGE(!primitiveHasPoint(point, primitive), assertMessage);
        notExpectedPoints.pop_back();
    }
}

void dumpPixels(const GfxPrimitive& primitive)
{
    for (const Pixel& pixel: primitive.pixels()) {
        ESP_LOGI("TEST", "%d / %d", pixel.getX(), pixel.getY());
    }
}
