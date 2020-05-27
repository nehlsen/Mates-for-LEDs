cmake_minimum_required(VERSION 3.5)

set(EXTRA_COMPONENT_DIRS ../../FastLedIdf ../../Mates-for-LEDs)
set(TEST_COMPONENTS "Matrix" CACHE STRING "List of components to test")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(matrix_test)
