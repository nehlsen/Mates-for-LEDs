#include "unity.h"
#include <Text.h>
#include "helper.h"

TEST_CASE("Text: one line", "[Matrix]")
{
    auto text = Text(0, 0, "t", CRGB(50, 50, 50));
    primitiveHasPixels(12, {
            {0,4},{1,4},{2,6},{2,5},{2,4},{2,3},{2,2},{2,1},
            {3,4},{3,0},{4,4},{4,1},
    }, text);

    text.setText("+");
    primitiveHasPixels(9, {
            {0,3},{1,3},{3,3},{4,3},
            {2,1},{2,2},{2,3},{2,4},{2,5},
    }, text);
}

TEST_CASE("Text: multi line", "[Matrix]")
{
    auto text = Text(0, 0, "t\n+", CRGB(50, 50, 50));
    primitiveHasPixels(21, {
            {0,11},{1,11},{2,13},{2,12},{2,11},{2,10},{2,9},{2,8},
            {3,11},{3,7},{4,11},{4,8},
            {0,3},{1,3},{3,3},{4,3},
            {2,1},{2,2},{2,3},{2,4},{2,5},
    }, text);

    text.setTopLeft(0, 13); // calculate the x,y -> should change nothing
}

TEST_CASE("Text: size", "[Matrix]")
{
    auto text = Text(0, 0, "", CRGB(50, 50, 50));
    TEST_ASSERT_EQUAL(0, text.getSize().width);
    TEST_ASSERT_EQUAL(0, text.getSize().height);

    text.setText("t");
    TEST_ASSERT_EQUAL(5, text.getSize().width);
    TEST_ASSERT_EQUAL(7, text.getSize().height);

    text.setText("t\n+");
    TEST_ASSERT_EQUAL(5, text.getSize().width);
    TEST_ASSERT_EQUAL(14, text.getSize().height);

    text.setText("tt");
    TEST_ASSERT_EQUAL(10, text.getSize().width);
    TEST_ASSERT_EQUAL(7, text.getSize().height);

    text.setText("tt\n+");
    TEST_ASSERT_EQUAL(10, text.getSize().width);
    TEST_ASSERT_EQUAL(14, text.getSize().height);

    text.setText("t\n++");
    TEST_ASSERT_EQUAL(10, text.getSize().width);
    TEST_ASSERT_EQUAL(14, text.getSize().height);
}

TEST_CASE("Text: get/set TopLeft", "[Matrix]")
{
    auto text = Text(0, 0, "", CRGB(50, 50, 50));
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(0, text.getTopLeft().y);

    text.setTopLeft(0, 0); // calculate the x,y -> should change nothing
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(0, text.getTopLeft().y);

    text.setText("t");
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(6, text.getTopLeft().y);

    text.setTopLeft(0, 6); // calculate the x,y -> should change nothing
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(6, text.getTopLeft().y);

    text.setText("t\n+");
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(13, text.getTopLeft().y);

    text.setTopLeft(0, 13); // calculate the x,y -> should change nothing
    TEST_ASSERT_EQUAL(0, text.getX());
    TEST_ASSERT_EQUAL(0, text.getY());
    TEST_ASSERT_EQUAL(0, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(13, text.getTopLeft().y);

    text.setTopLeft(5, 18);
    TEST_ASSERT_EQUAL(5, text.getX());
    TEST_ASSERT_EQUAL(5, text.getY());
    TEST_ASSERT_EQUAL(5, text.getTopLeft().x);
    TEST_ASSERT_EQUAL(18, text.getTopLeft().y);
}
