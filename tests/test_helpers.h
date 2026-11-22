#pragma once

#include "colour/colour.h"
#include "math/vector.h"

// Doubles are binary approximations: compare them within a tolerance, never
// with ==.
extern const double tolerance;

void requireVectorsEqual(const Vector& actual, const Vector& expected);
void requireColoursEqual(const Colour& actual, const Colour& expected);
