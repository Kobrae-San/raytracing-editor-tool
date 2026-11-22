#include "material/lambert_shader.h"

#include <algorithm>

LambertShader::LambertShader(const Colour& colour)
    : _colour(colour) {
}

Colour LambertShader::shade(const HitInfo& hit, const Vector& toLight) const {
    // Negative means the surface faces away from the light: no light at all.
    double brightness = std::max(0.0, hit.normal.dot(toLight));
    return brightness * _colour;
}
