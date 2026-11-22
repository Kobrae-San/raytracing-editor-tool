#pragma once

#include <string>

#include "image/image.h"

// Interface for saving an image to some destination and format.
// Concrete implementations (e.g. PngSaver) decide how and where.
class ImageSaver {
public:
    virtual ~ImageSaver() = default;

    virtual void save(Image& image, const std::string& path) = 0;
};
