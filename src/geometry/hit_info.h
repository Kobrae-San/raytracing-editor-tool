#pragma once

#include <memory>

#include "math/vector.h"

// Declared, not included: Material::shade() needs a HitInfo, so including
// material.h here would create a cycle. shared_ptr only needs the full
// Material definition where one is actually constructed, not here.
class Material;

// Information about where a ray hit a surface, returned by intersection
// tests such as Sphere::intersect. A plain data holder, so its fields are
// public instead of going through getters.
struct HitInfo {
    Vector point;
    Vector normal;
    std::shared_ptr<Material> material;
};
