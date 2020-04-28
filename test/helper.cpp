#include "helper.h"
#include "unity.h"

bool pointInListOfPixels(const Point_t& expectedPoint, const Pixels& listOfPixels)
{
    for (const Pixel& pixel: listOfPixels) {
        if (pixel.getX() == expectedPoint.first && pixel.getY() == expectedPoint.second) {
            return true;
        }
    }

    return false;
}

bool primitiveHasPoint(Point_t point, const GfxPrimitive& primitive)
{
    return pointInListOfPixels(point, primitive.pixels());
}

void primitiveHasPixels(int expectedPixelCount, PointList_t expectedPoints, const GfxPrimitive& primitive)
{
    char assertMessage[58];
    sprintf(assertMessage, "Expected gfx-primitive to have %d Points got %d", expectedPixelCount, primitive.pixels().size());
    if (expectedPixelCount != primitive.pixels().size()) {
        ESP_LOGE("TEST", "expectedPixelCount %d != actual %d", expectedPixelCount, primitive.pixels().size());
        dumpPixels(primitive);
    }
    TEST_ASSERT_EQUAL_MESSAGE(expectedPixelCount, primitive.pixels().size(), assertMessage);

    while (!expectedPoints.empty()) {
        Point_t point = expectedPoints.back();

        if (!primitiveHasPoint(point, primitive)) {
            ESP_LOGE("TEST", "Expected Point (%d,%d) not found on gfx-primitive", point.first, point.second);
            dumpPixels(primitive);
        }
        sprintf(assertMessage, "Expected Point (%d,%d) not found on gfx-primitive", point.first, point.second);
        TEST_ASSERT_MESSAGE(primitiveHasPoint(point, primitive), assertMessage);
        expectedPoints.pop_back();
    }
}

void primitiveNotHasPixels(PointList_t notExpectedPoints, const GfxPrimitive& primitive)
{
    char assertMessage[58];

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
