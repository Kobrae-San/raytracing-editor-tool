#pragma once

#include "io/image_saver.h"

// Adapter: saves an Image as a PNG file, hiding LodePNG behind ImageSaver.
class PngSaver : public ImageSaver {
public:
    void save(const Image& image, const std::string& path) const override;
};
