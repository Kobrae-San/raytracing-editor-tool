#pragma once

#include "colour/colour.h"
#include "geometry/hit_info.h"
#include "scene/light.h"

// Interface for calculating the final colour of a shaded surface.
// Concrete implementations (e.g. FlatShader, LambertShader) decide how,
// using where/how the surface was hit and the light illuminating it.
class Material {
public:
    virtual ~Material() = default;

    virtual Colour shade(const HitInfo& hit, const Light& light) const = 0;
};
