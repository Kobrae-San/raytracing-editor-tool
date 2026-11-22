#pragma once

#include "colour/colour.h"
#include "math/ray.h"
#include "scene/scene.h"

// The colour seen along ray: the nearest surface's material lit by the sun,
// or black if the ray hits nothing. Answers "who colours the pixel?" (ADR 0010).
Colour trace(const Ray& ray, const Scene& scene);
