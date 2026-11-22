#include "io/png_saver.h"

#include <cstdint>
#include <stdexcept>
#include <vector>

#include "lodepng.h"

namespace {

// Converts one colour component (expected range 0.0-1.0) to a 0-255 byte,
// clamping out-of-range values instead of wrapping or overflowing.
std::uint8_t toByte(double component) {
    double clamped = component < 0.0 ? 0.0 : (component > 1.0 ? 1.0 : component);
    return static_cast<std::uint8_t>(clamped * 255.0 + 0.5);
}

}  // namespace

void PngSaver::save(Image& image, const std::string& path) {
    // LodePNG expects one flat buffer of RGBA bytes, row by row from the
    // top, which matches how Image already stores its pixels.
    std::vector<unsigned char> pixels(static_cast<std::size_t>(image.width()) * image.height() * 4);

    for (unsigned int y = 0; y < image.height(); ++y) {
        for (unsigned int x = 0; x < image.width(); ++x) {
            const Colour& colour = image.pixel(x, y);
            std::size_t index = (static_cast<std::size_t>(y) * image.width() + x) * 4;
            pixels[index + 0] = toByte(colour.r());
            pixels[index + 1] = toByte(colour.g());
            pixels[index + 2] = toByte(colour.b());
            pixels[index + 3] = 255;
        }
    }

    unsigned int error = lodepng::encode(path, pixels, image.width(), image.height());
    if (error != 0) {
        throw std::runtime_error("PngSaver: failed to save '" + path + "': " + lodepng_error_text(error));
    }
}
