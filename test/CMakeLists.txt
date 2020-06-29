set(TEST_SRCS
        helper.cpp
        test_PixelLocator.cpp
        test_Pixel.cpp
        test_Line.cpp
        test_Rect.cpp
        test_PixelMap.cpp
        test_GfxPrimitive.cpp
        test_GfxCanvas.cpp
        test_Canvas.cpp
        test_Circle.cpp
        test_Text.cpp
        test_color_utils.cpp
        )

idf_component_register(
        SRCS ${TEST_SRCS}
        INCLUDE_DIRS "."
        REQUIRES unity Mates-for-LEDs
)
