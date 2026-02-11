cmake_minimum_required(VERSION 3.14)
project(ImageProcessingApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        GIT_TAG release-1.14.0
)

# Für Windows: verhindert CRT-Warnungen
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(image_processing
        src/main.cpp
)

add_executable(tests_image_processing
        tests/example_test.cpp
)

target_link_libraries(tests_image_processing
        image_processing
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_image_processing)
