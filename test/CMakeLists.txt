idf_component_register(
        SRCS helper.cpp test_PixelLocator.cpp test_Pixel.cpp test_Line.cpp test_Rect.cpp test_PixelMap.cpp test_GfxPrimitive.cpp
        INCLUDE_DIRS "."
        REQUIRES unity Matrix
)
