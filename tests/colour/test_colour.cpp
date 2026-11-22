#include <catch2/catch_test_macros.hpp>

#include "colour/colour.h"

// Compares r(), g(), b() with plain numbers on purpose: using
// requireColoursEqual here would test Colour against itself.

TEST_CASE("Colour holds its three components", "[colour]") {
    Colour colour(1, 0.5, 0);

    REQUIRE(colour.r() == 1.0);
    REQUIRE(colour.g() == 0.5);
    REQUIRE(colour.b() == 0.0);
}

TEST_CASE("Colour scaled by a number", "[colour]") {
    Colour colour = 0.5 * Colour(1, 0.5, 0);

    REQUIRE(colour.r() == 0.5);
    REQUIRE(colour.g() == 0.25);
    REQUIRE(colour.b() == 0.0);
}
