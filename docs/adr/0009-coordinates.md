# 0009 — Coordinates: x right, y up, z forward; pixels from the top left

## Status

Proposed

## Context

The camera, the shapes and the image must agree on where things are. The
world and the image naturally count differently: image rows grow downward,
while "up" in the scene should be positive y.

## Decision

- World: x to the right, y up, z forward (into the screen). This is a
  left-handed system.
- Image: pixel (0, 0) is the top-left corner; columns grow to the right, rows
  downward. This is also the order PNG stores pixels in.
- `Camera::rayThroughPixel` flips y and aims at the centre of each pixel
  (`+ 0.5`).

## Consequences

- Positive z means "in front of the camera", which makes scenes easy to read.
- The y flip lives in one place and is covered by tests on an odd-sized,
  non-square image with off-centre pixels.

## Rejected alternatives

- Looking along −z (right-handed, as in *Ray Tracing in One Weekend*): common
  in graphics, but every scene would have negative depths.
- Pixel (0, 0) at the bottom left: matches the world's y, but not image files.
