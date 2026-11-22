#pragma once

#include "colour/colour.h"
#include "math/vector.h"

// A point light: a single point in the scene that emits light of a given
// colour in all directions.
class Light {
public:
    Light(const Vector& position, const Colour& colour);

    // Read-only access to the position and colour.
    const Vector& position() const;
    const Colour& colour() const;

private:
    Vector _position;
    Colour _colour;
};
