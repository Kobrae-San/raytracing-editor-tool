#pragma once

#include <vector>

#include "colour/colour.h"

// A 2D grid of pixels, each with its own colour. Pixel (0, 0) is the
// top-left corner; x grows to the right, y grows downward.
class Image {
public:
    Image(unsigned int width, unsigned int height);

    // Read-only access to the dimensions.
    unsigned int width() const;
    unsigned int height() const;

    // Set the colour of the pixel at column x, row y.
    void setPixel(unsigned int x, unsigned int y, const Colour& colour);

    // Read-only access to the colour of the pixel at column x, row y.
    const Colour& pixel(unsigned int x, unsigned int y) const;

private:
    unsigned int _width;
    unsigned int _height;
    std::vector<Colour> _pixels;
};
