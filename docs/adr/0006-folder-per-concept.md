# 0006 — One folder per concept

## Status

Accepted

## Context

A flat `src/` folder becomes hard to navigate as the ray tracer grows: maths,
shapes, materials, the scene, rendering and file output would sit side by
side with no visible structure.

## Decision

One folder per concept under `src/` (`math/`, `colour/`, `geometry/`,
`material/`, `scene/`, `render/`, `image/`, `io/`), with each class's tests in
the matching folder under `tests/`. Includes start from `src/`, e.g.
`#include "math/vector.h"`. A folder appears with its first class.

Dependencies between folders go one way (acyclic dependencies principle):
`render/` → `scene/` → `geometry/` → `math/`, `material/` → `geometry/`,
`io/` → `image/` → `colour/`. `Colour` has its own folder so that `geometry/`
and `render/` don't depend on each other through it. `Ray` lives in `math/`
next to `Vector`, since it is the maths of a half-line.

## Consequences

- A class is easy to find, and so are its tests.
- Moving a file means updating `CMakeLists.txt` and its includes.
- A folder holding a single file can look excessive at first.

## Left out for now

- **Namespaces:** when names clash or partner studios share code with ours.
- **One library per folder:** when we need to enforce dependencies or control
  build times.
- **A separate `include/` folder:** when the core ships as a library.
