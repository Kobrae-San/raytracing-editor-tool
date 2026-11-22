#pragma once

#include "material/material.h"

// Lambertian (diffuse) shading: the surface's base colour is scaled by the
// dot product of the surface normal and the direction to the light, so
// surfaces facing the light appear brighter than surfaces facing away.
class LambertShader : public Material {
public:
    LambertShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
