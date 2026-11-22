#pragma once

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "math/vector.h"

// Strategy interface: how a surface takes the light. A shape has a material
// and delegates its shading to it (ADR 0011), so a new kind of material
// (mirror, glass) is a new class that no shape has to know about.
class Material {
public:
    virtual ~Material() = default;

    // toLight and hit.normal must both be unit vectors.
    virtual Colour shade(const HitInfo& hit, const Vector& toLight) const = 0;
};
