#include "material/lambert_shader.h"

LambertShader::LambertShader(const Colour& colour)
    : _colour(colour) {
}

Colour LambertShader::shade(const HitInfo& hit, const Light& light) const {
    Vector directionToLight = (light.position() - hit.point).normalised();

    // The dot product is the cosine of the angle between the normal and the
    // light direction: 1 when facing the light head-on, 0 at a right angle,
    // negative when facing away. Negative values are clamped since a
    // surface facing away from the light receives no light from it.
    double brightness = hit.normal.dot(directionToLight);
    if (brightness < 0.0) {
        brightness = 0.0;
    }

    return _colour * brightness;
}
