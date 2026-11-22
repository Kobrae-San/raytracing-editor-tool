cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# LodePNG: single-file PNG encoder/decoder. It ships no CMakeLists.txt of its
# own, so we fetch its source and build it ourselves as a small static
# library. There are no tagged releases, so we pin to a specific commit.
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
)
FetchContent_MakeAvailable(lodepng)

add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng PUBLIC ${lodepng_SOURCE_DIR})

# Core library: everything except the entry point, shared between the
# main executable and the test binary so each source file is listed once.
add_library(raytracer_core STATIC
  src/math/vector.cpp
  src/colour/colour.cpp
  src/math/ray.cpp
  src/geometry/sphere.cpp
  src/render/camera.cpp
  src/io/png_saver.cpp
  src/material/flat_shader.cpp
  src/material/lambert_shader.cpp
  src/image/image.cpp
  src/scene/light.cpp)
target_include_directories(raytracer_core PUBLIC src)
target_link_libraries(raytracer_core PRIVATE lodepng)

# Warnings for our own code only (LodePNG and Catch2 are built without them).
set(RT_WARNINGS -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
target_compile_options(raytracer_core PRIVATE ${RT_WARNINGS})

# Main executable
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)
target_compile_options(raytracer PRIVATE ${RT_WARNINGS})

# Testing
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests
  tests/test_helpers.cpp
  tests/math/test_vector.cpp
  tests/colour/test_colour.cpp
  tests/math/test_ray.cpp
  tests/image/test_image.cpp
  tests/render/test_camera.cpp
  tests/geometry/test_sphere.cpp)
target_include_directories(tests PRIVATE tests)
target_link_libraries(tests PRIVATE raytracer_core Catch2::Catch2WithMain)
target_compile_options(tests PRIVATE ${RT_WARNINGS})

include(CTest)
include(Catch)
catch_discover_tests(tests)
