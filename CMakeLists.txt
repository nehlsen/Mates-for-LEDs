set(Matrix_srcs
        "LedMatrix/LedMatrix.cpp"
        "LedMatrix/PixelLocator.cpp"
        "LedMatrix/color_utils.cpp"
        )
set(Matrix_include_dirs
        "LedMatrix/"
        )

set(GfxPrimitives_srcs
        "GfxPrimitives/GfxPrimitive.cpp"
        "GfxPrimitives/Pixel.cpp"
        "GfxPrimitives/PixelMap.cpp"
        "GfxPrimitives/Line.cpp"
        "GfxPrimitives/Rect.cpp"
        "GfxPrimitives/Circle.cpp"
        )
set(GfxPrimitives_include_dirs
        "GfxPrimitives/"
        )

idf_component_register(
        SRCS "${Matrix_srcs}" "${GfxPrimitives_srcs}"
        INCLUDE_DIRS "${Matrix_include_dirs}" "${GfxPrimitives_include_dirs}"
        REQUIRES FastLedIdf
        )
