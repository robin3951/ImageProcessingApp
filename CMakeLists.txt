cmake_minimum_required(VERSION 3.14)
project(ImageProcessingApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_COVERAGE "Enable code coverage" OFF)

if(NOT ENABLE_COVERAGE)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()

include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

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
        src/image_processing.h
        src/filter.cpp
        src/filter.h
)

target_include_directories(image_processing PUBLIC src)

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    message(STATUS "Coverage enabled for image_processing")
    target_compile_options(image_processing PRIVATE --coverage -O0 -g)
    target_link_options(image_processing PRIVATE --coverage)
endif()

add_executable(cv-cli src/main.cpp)
target_link_libraries(cv-cli
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

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    target_compile_options(tests_image_processing PRIVATE -O0 -g)
    target_link_options(tests_image_processing PRIVATE --coverage)
endif()

if(ENABLE_COVERAGE AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    file(GLOB_RECURSE TEST_SOURCES
            ${CMAKE_SOURCE_DIR}/tests/*.cpp
            ${CMAKE_SOURCE_DIR}/tests/*.h
    )

    set_source_files_properties(
            ${TEST_SOURCES}
            PROPERTIES COMPILE_FLAGS "-fno-profile-arcs -fno-test-coverage"
    )
endif()

include(GoogleTest)
gtest_discover_tests(tests_image_processing)
