cmake_minimum_required(VERSION 3.14)
project(ImageProcessingApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")


include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
        GIT_TAG release-1.14.0
)

# Für Windows: verhindert CRT-Warnungen
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

FetchContent_Declare(
        cli11
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG v2.4.2
)
FetchContent_MakeAvailable(cli11)



add_library(image_processing
        src/image_processing.cpp
)
target_include_directories(image_processing PUBLIC src)

add_executable(cli_app src/main.cpp)
target_link_libraries(cli_app
        image_processing
        CLI11::CLI11
)

enable_testing()
add_executable(tests_image_processing
        tests/example_test.cpp
)

target_link_libraries(tests_image_processing
        image_processing
        GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(tests_image_processing)
