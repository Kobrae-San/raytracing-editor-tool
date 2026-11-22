#pragma once

#include "material/material.h"

// The simplest material: every point on the surface shades to the same
// fixed colour, with no lighting calculation at all.
class FlatShader : public Material {
public:
    FlatShader(const Colour& colour);

    Colour shade(const HitInfo& hit, const Light& light) const override;

private:
    Colour _colour;
};
