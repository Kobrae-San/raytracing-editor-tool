#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>

#include "math/vector.h"

TEST_CASE("Vector addition", "[vector]") {
    Vector a(1, 2, 3);
    Vector b(4, 5, 6);

    Vector result = a + b;

    // (1, 2, 3) + (4, 5, 6) = (5, 7, 9)
    REQUIRE(result.x() == Catch::Approx(5.0));
    REQUIRE(result.y() == Catch::Approx(7.0));
    REQUIRE(result.z() == Catch::Approx(9.0));
}

TEST_CASE("Vector subtraction", "[vector]") {
    Vector a(-1, 4, 0);
    Vector b(-5, 2, 1);

    Vector result = a - b;

    // (-1, 4, 0) - (-5, 2, 1) = (4, 2, -1)
    REQUIRE(result.x() == Catch::Approx(4.0));
    REQUIRE(result.y() == Catch::Approx(2.0));
    REQUIRE(result.z() == Catch::Approx(-1.0));
}

TEST_CASE("Vector normalised", "[vector]") {
    Vector a(3, 4, 0);

    Vector result = a.normalised();

    // length of (3, 4, 0) is 5, so normalised = (3/5, 4/5, 0)
    REQUIRE(result.x() == Catch::Approx(3.0 / 5.0));
    REQUIRE(result.y() == Catch::Approx(4.0 / 5.0));
    REQUIRE(result.z() == Catch::Approx(0.0));
}
