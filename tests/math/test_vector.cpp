#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "math/vector.h"
#include "test_helpers.h"

using Catch::Matchers::WithinAbs;

TEST_CASE("Vector addition", "[vector]") {
    requireVectorsEqual(Vector(3, 4, 0) + Vector(4, -3, 0), Vector(7, 1, 0));
    requireVectorsEqual(Vector(3, 4, 1) + Vector(4, -3, 2), Vector(7, 1, 3));
}

TEST_CASE("Vector subtraction", "[vector]") {
    requireVectorsEqual(Vector(4, 5, 0) - Vector(1, 1, 0), Vector(3, 4, 0));
    requireVectorsEqual(Vector(-1, 4, 0) - Vector(-5, 2, 1), Vector(4, 2, -1));
}

TEST_CASE("Vector scaled by a number", "[vector]") {
    requireVectorsEqual(2.0 * Vector(3, -4, 1), Vector(6, -8, 2));
}

TEST_CASE("Ray equation O + t * D", "[vector]") {
    Vector origin(0, 8, 0);
    Vector direction(3, -4, 0);

    requireVectorsEqual(origin + 2.0 * direction, Vector(6, 0, 0));
}

TEST_CASE("Vector dot product", "[vector]") {
    // Whole numbers: exact comparison is safe here.
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, 3, 0)) == 24.0);
    REQUIRE(Vector(3, 4, 0).dot(Vector(4, -3, 0)) == 0.0);
    REQUIRE(Vector(3, 4, 12).dot(Vector(4, 3, 1)) == 36.0);
}

TEST_CASE("Vector length", "[vector]") {
    REQUIRE(Vector(3, -4, 0).length() == 5.0);
    REQUIRE(Vector(3, 4, 12).length() == 13.0);
}

TEST_CASE("Vector normalised", "[vector]") {
    requireVectorsEqual(Vector(3, -4, 0).normalised(), Vector(0.6, -0.8, 0));
    REQUIRE_THAT(Vector(3, 4, 12).normalised().length(), WithinAbs(1.0, tolerance));
}
