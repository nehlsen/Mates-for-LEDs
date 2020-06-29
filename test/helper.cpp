#include "helper.h"
#include "unity.h"
#include <numeric>

bool pointInListOfPixels(const Point_t &expectedPoint, const Pixels &listOfPixels, bool includeBlackPixels)
{
    for (const Pixel& pixel: listOfPixels) {
        if (pixel.getX() == expectedPoint.first && pixel.getY() == expectedPoint.second) {
            if (!includeBlackPixels) {
                return pixel.getColor() != CRGB(CRGB::Black);
            }
            return true;
        }
    }

    return false;
}

bool primitiveHasPoint(Point_t point, const GfxPrimitive &primitive, bool includeBlackPixels)
{
    return pointInListOfPixels(point, primitive.pixels(), includeBlackPixels);
}

void primitiveHasPixels(int expectedPixelCount, PointList_t expectedPoints, const GfxPrimitive &primitive, bool includeBlackPixels)
{
    expectPixels(expectedPixelCount, expectedPoints, primitive.pixels(), includeBlackPixels);
}

void expectPixels(int expectedPixelCount, PointList_t expectedPoints, const Pixels& pixels, bool includeBlackPixels)
{
    char assertMessage[58];
    const int actualPixelCount = countPixels(pixels, includeBlackPixels);
    sprintf(assertMessage, "Expected %d Pixels, got %d", expectedPixelCount, actualPixelCount);
    if (expectedPixelCount != actualPixelCount) {
        ESP_LOGE("TEST", "expectedPixelCount %d != actual %d", expectedPixelCount, actualPixelCount);
        dumpPixels(pixels);
    }
    TEST_ASSERT_EQUAL_MESSAGE(expectedPixelCount, actualPixelCount, assertMessage);

    while (!expectedPoints.empty()) {
        Point_t expectedPoint = expectedPoints.back();
        const bool hasExpectedPoint = pointInListOfPixels(expectedPoint, pixels, includeBlackPixels);

        sprintf(assertMessage, "Expected Point (%d,%d) not found", expectedPoint.first, expectedPoint.second);
        if (!hasExpectedPoint) {
            ESP_LOGE("TEST", "%s", assertMessage);
            dumpPixels(pixels);
        }
        TEST_ASSERT_MESSAGE(hasExpectedPoint, assertMessage);

        expectedPoints.pop_back();
    }
}

void primitiveNotHasPixels(PointList_t notExpectedPoints, const GfxPrimitive& primitive)
{
    char assertMessage[58];

    while (!notExpectedPoints.empty()) {
        Point_t point = notExpectedPoints.back();

        sprintf(assertMessage, "Not expected Point (%d,%d) found on gfx-primitive", point.first, point.second);
        TEST_ASSERT_MESSAGE(!primitiveHasPoint(point, primitive, false), assertMessage);
        notExpectedPoints.pop_back();
    }
}

void dumpPixels(const GfxPrimitive& primitive)
{
    dumpPixels(primitive.pixels());
}

void dumpPixels(const Pixels& pixels)
{
    for (const Pixel& pixel: pixels) {
        ESP_LOGI("TEST", "%d / %d", pixel.getX(), pixel.getY());
    }
}

int countPixels(const GfxPrimitive &primitive, bool includeBlackPixels)
{
    return countPixels(primitive.pixels(), includeBlackPixels);
}

int countPixels(const Pixels& pixels, bool includeBlackPixels)
{
    if (includeBlackPixels) {
        return pixels.size();
    }

//    return std::accumulate(
//            pixels.begin(),
//            pixels.end(),
//            0,
//            [](const int &carry, const Pixel &pixel) {
////                if (pixel.getColor().r == 0 && pixel.getColor().g == 0 && pixel.getColor().b == 0) {
////                    return carry;
////                }
//
//                return carry + 1;
//
////                return carry + (pixel.getColor() != CRGB(0, 0, 0) ? 1 : 0);
//            });

    int count = 0;
    for (const Pixel& pixel: pixels) {
        count += (pixel.getColor() == CRGB(0, 0, 0) ? 0 : 1);
    }
    return count;
}
