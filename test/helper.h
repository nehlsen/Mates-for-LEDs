#ifndef MATRIXTEST_TEST_HELPER_H
#define MATRIXTEST_TEST_HELPER_H

#include <GfxPrimitive.h>
#include <vector>

typedef std::pair<uint8_t, uint8_t> Point_t;
typedef std::vector<Point_t> PointList_t;

bool primitiveHasPoint(Point_t point, const GfxPrimitive& primitive);
void primitiveHasPixels(int expectedPixelCount, PointList_t expectedPoints, const GfxPrimitive& primitive);
void primitiveNotHasPixels(PointList_t notExpectedPoints, const GfxPrimitive& primitive);
void dumpPixels(const GfxPrimitive& primitive);

#endif //MATRIXTEST_TEST_HELPER_H
