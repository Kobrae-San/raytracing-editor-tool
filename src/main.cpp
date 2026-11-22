#include <exception>
#include <iostream>
#include <memory>

#include "geometry/plane.h"
#include "geometry/sphere.h"
#include "io/png_saver.h"
#include "material/lambert_shader.h"
#include "render/camera.h"
#include "scene/scene.h"

int main() {
    // A red ball standing on a grey floor, lit by the sun from the top left.
    Scene scene(Vector(-1, 1, -1));
    scene.add(std::make_unique<Sphere>(
        Vector(0, 0, 9), 5, std::make_shared<LambertShader>(Colour(1, 0, 0))));
    scene.add(std::make_unique<Plane>(
        Vector(0, -5, 0), Vector(0, 1, 0), std::make_shared<LambertShader>(Colour(0.8, 0.8, 0.8))));

    Camera camera(Vector(0, 0, -1), Vector(0, 0, 0), 2);
    Image image = camera.render(scene, 400, 300);

    const std::string path = "image.png";
    try {
        PngSaver().save(image, path);
    } catch (const std::exception& error) {
        std::cerr << error.what() << '\n';
        return 1;
    }
    std::cout << "Saved " << path << '\n';
    return 0;
}
