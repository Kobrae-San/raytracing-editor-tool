# 0010 — `trace` decides a pixel's colour

## Status

Accepted

## Context

Who decides the colour of a pixel: the camera, the image, or `main`? In the
spike it was `main`, where it couldn't be tested. Then it was a `Camera`
method, which gave the camera two reasons to change: how rays are made, and
how light is computed.

## Decision

A free function `Colour trace(const Ray& ray, const Scene& scene)` in
`src/render/trace.h`. It asks the scene for the nearest hit and the hit's
material for its shade, or returns black. `Camera` only makes rays and loops
over pixels; `Image` only stores colours.

## Consequences

- The colour of one ray is tested without an image or a camera.
- `trace` will grow with shadows, reflections and the sky; it can become a
  `Renderer` class (Strategy) once there are several ways to trace.
- `Camera::render` still holds the pixel loop (parked: the camera has two
  reasons to change).
