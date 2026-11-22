#include "material/flat_shader.h"

FlatShader::FlatShader(const Colour& colour)
    : _colour(colour) {
}

Colour FlatShader::shade(const HitInfo& hit, const Light& light) const {
    (void)hit;
    (void)light;
    return _colour;
}
