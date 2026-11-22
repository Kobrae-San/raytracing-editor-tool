#pragma once

#include "material/material.h"

// Ignores the light: every point shades to the same colour.
class FlatShader : public Material {
public:
    explicit FlatShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Vector& toLight) const override;

private:
    Colour _colour;
};
