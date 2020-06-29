#ifndef MATRIX_TEST_HELPER_H
#define MATRIX_TEST_HELPER_H

#include <GfxPrimitive.h>
#include <vector>

#define TEST_ASSERT_COLOR(expected, actual) { \
TEST_ASSERT_EQUAL(expected.r, actual.r); \
TEST_ASSERT_EQUAL(expected.g, actual.g); \
TEST_ASSERT_EQUAL(expected.b, actual.b); \
}

typedef std::pair<int16_t, int16_t> Point_t;
typedef std::vector<Point_t> PointList_t;

bool pointInListOfPixels(const Point_t &expectedPoint, const Pixels &listOfPixels, bool includeBlackPixels);
bool primitiveHasPoint(Point_t point, const GfxPrimitive &primitive, bool includeBlackPixels);
void primitiveHasPixels(int expectedPixelCount, PointList_t expectedPoints, const GfxPrimitive &primitive, bool includeBlackPixels);
void expectPixels(int expectedPixelCount, PointList_t expectedPoints, const Pixels& pixels, bool includeBlackPixels);
void primitiveNotHasPixels(PointList_t notExpectedPoints, const GfxPrimitive& primitive);

void dumpPixels(const GfxPrimitive& primitive);
void dumpPixels(const Pixels& pixels);
int countPixels(const GfxPrimitive& primitive, bool includeBlackPixels = false);
int countPixels(const Pixels& pixels, bool includeBlackPixels = false);

#endif //MATRIX_TEST_HELPER_H
