#pragma once

#include "math/vector.h"

// Declared, not included: material.h includes this file, so including it here
// would create a cycle.
class Material;

// Where a ray hit a surface. A plain data holder, so its fields are public.
struct HitInfo {
    double t;                  // distance along the ray, in units of its direction
    Vector point;
    Vector normal;             // unit length, pointing out of the surface
    const Material* material;  // non-owning: the shape keeps its material alive
};
