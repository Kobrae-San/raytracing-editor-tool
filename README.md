# raytracing-editor-tool

A **CPU raytracer** written in **C++20** for a film studio that needs a
renderer it fully owns: tested, documented, open to partner studios, and fast
enough to render an entire movie. It's a deliberate alternative to closed
commercial renderers (Arnold, RenderMan, V-Ray) with their recurring licences
and vendor-driven roadmaps.

See the full brief in [docs/discovery/discovery-report.md](docs/discovery/discovery-report.md).

[![CI](https://github.com/Kobrae-San/raytracing-editor-tool/actions/workflows/ci.yml/badge.svg)](https://github.com/Kobrae-San/raytracing-editor-tool/actions/workflows/ci.yml)

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md)

---

## Goals & constraints

These shape every technical decision and are why the code looks the way it
does:

- **CPU-only rendering.** Performance comes from multithreading, an
  acceleration structure (BVH) and cache-friendly code — not the GPU.
- **Fast *and* high quality.** Quick previews for artists plus enough
  throughput for a full film → adjustable preview/final modes.
- **Reliable and explainable.** Correct images, with failures that can be
  diagnosed. Hence automated tests (maths + reference images), benchmarks and
  logging from day one. (Black artefacts usually trace back to NaN or
  self-intersection — things tests must cover.)
- **Extensible by partners.** Add shapes, materials and lights *without*
  touching the core (Open/Closed). Needs docs, a contribution guide, CI and
  code review.

---

## Architecture

Organised around SOLID so new shapes/materials plug in via interfaces without
changing the renderer:

- **Maths** (`src/math/`): `Vector`, `Ray`
- **Colour** (`src/colour/`): `Colour`
- **Geometry** (`src/geometry/`): `Sphere`, `HitInfo` — more shapes later
- **Scene** (`src/scene/`): `Light`
- **Material** (`src/material/`): `Material` (Strategy interface), `FlatShader`,
  `LambertShader`
- **Rendering** (`src/render/`): `Camera` (ray generation + tracing)
- **I/O** (`src/io/`): `ImageSaver` (Strategy interface), `PngSaver` (via
  [LodePNG](https://github.com/lvandeve/lodepng), see
  [ADR 0005](docs/adr/0005-lodepng.md))
- **Image** (`src/image/`): `Image` (pixel grid)

`Material` and `ImageSaver` are abstract interfaces (Dependency Inversion): the
renderer and `Image` depend on them, not on a concrete shader or file format,
so adding e.g. a `GlassShader` or an `ExrSaver` later won't touch existing
code.

## Project structure

```
.
├── .devcontainer/    # Dev container config (VSCode / Zed)
├── docs/adr/         # Architecture decision records
├── src/
│   ├── main.cpp      # Main entry point
│   ├── math/         # Vector, Ray
│   ├── colour/       # Colour
│   ├── geometry/     # Sphere, HitInfo
│   ├── scene/        # Light
│   ├── material/     # Material, FlatShader, LambertShader
│   ├── render/       # Camera
│   ├── io/           # ImageSaver, PngSaver
│   └── image/        # Image
├── tests/            # Catch2 unit tests, mirroring src/
└── CMakeLists.txt
```

---

## Cross-platform setup

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and either:
- **VS Code** with the [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers) extension, or
- **Zed** with its built-in dev container support.

1. Open the repository folder in VS Code or Zed.
2. When prompted, click **"Reopen in Container"** (VS Code) or **"Use Dev Container"** (Zed).
3. The container image provides GCC, CMake ≥ 3.20, and Git. Catch2 and LodePNG are downloaded automatically at first build.
4. CMake configures and builds automatically on container creation (`postCreateCommand`).

### Option B — Native (macOS / Linux / Windows)

Prerequisites:
| Tool | Minimum version |
|------|----------------|
| CMake | 3.20 |
| C++ compiler | GCC 12 / Clang 15 / MSVC 19.34 (C++20) |
| Git | any recent |

---

## Common commands

| Command | What it does |
|---------|-------------|
| `make build` | Configure + compile everything |
| `make run` | Build then launch the raytracer |
| `make test` | Build then run the test suite |
| `make clean` | Delete the `build/` directory |

`run` and `test` both depend on `build`, so they recompile automatically if sources have changed.

---

## Building

```bash
make build
```

<details>
<summary>Raw CMake (if you prefer)</summary>

```bash
# Configure (only needed once, or after changing CMakeLists.txt)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Build everything (main binary + test binary)
cmake --build build
```
</details>

---

## Running the demo

```bash
make run
# Hello, Raytracer!
```

The pieces above (`Camera`, `Sphere`, `Image`, `PngSaver`, ...) aren't wired
together into an end-to-end render yet — each is tested in isolation, but
`main.cpp` doesn't yet assemble a scene and write an image file.

---

## Running the tests

```bash
make test
```

<details>
<summary>More verbose output</summary>

```bash
# Run the test binary directly for Catch2's reporter
./build/tests --reporter compact
```
</details>

You should see all test cases pass, e.g.:

```
All tests passed (N assertions in M test cases)
```

---

## Test-driven development workflow

Tests live in `tests/`, mirroring the `src/` layout. Add a new `TEST_CASE`
before writing the implementation, confirm it fails, then implement until it
passes.

```cpp
// tests/math/test_vector.cpp  (example)
#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "math/vector.h"

TEST_CASE("Vector addition", "[vector]") {
    Vector a(1, 0, 0);
    Vector b(0, 1, 0);
    Vector result = a + b;
    REQUIRE(result.x() == Catch::Approx(1.0));
}
```

Useful Catch2 macros:

| Macro | Purpose |
|-------|---------|
| `REQUIRE(expr)` | Assert; stop test on failure |
| `CHECK(expr)` | Assert; continue on failure |
| `REQUIRE_THROWS(expr)` | Expect an exception |
| `Catch::Approx(x).epsilon(e)` | Floating-point comparison |

Full docs: https://github.com/catchorg/Catch2/blob/devel/docs/tutorial.md

---

## Adding new source files

Library code (anything other than `main.cpp`) lives in the `raytracer_core`
target, shared by both the `raytracer` executable and the `tests` binary —
list each source file once and both pick it up:

1. Create `src/yourmodule/yourfile.cpp` and `src/yourmodule/yourfile.h`.
2. Add the `.cpp` to `raytracer_core` in `CMakeLists.txt`:
   ```cmake
   target_sources(raytracer_core PRIVATE src/yourmodule/yourfile.cpp)
   ```
3. For tests, add a new `.cpp` under `tests/` and add it to the `tests` target:
   ```cmake
   target_sources(tests PRIVATE tests/yourmodule/test_yourfile.cpp)
   ```

---

## Architecture decisions

Significant build/tooling decisions are recorded as ADRs in
[`docs/adr/`](docs/adr/) (dev container, CMake, Catch2, GitHub Actions CI,
LodePNG). See [AGENTS.md](AGENTS.md) for the rules on reading and proposing
ADRs before changing build, tooling or test setup.
