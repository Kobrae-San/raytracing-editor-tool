#pragma once

#include "material/material.h"

// Lambert's law: brightness = max(0, N . L), the cosine of the angle between
// the surface normal and the direction to the light.
class LambertShader : public Material {
public:
    explicit LambertShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Vector& toLight) const override;

private:
    Colour _colour;
};
