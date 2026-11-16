# raytracing-editor-tool

A **CPU raytracer** written in **C++20** for a film studio that needs a
renderer it fully owns: tested, documented, open to partner studios, and fast
enough to render an entire movie. It's a deliberate alternative to closed
commercial renderers (Arnold, RenderMan, V-Ray) with their recurring licences
and vendor-driven roadmaps.

See the full brief in [docs/discovery/discovery-report.md](docs/discovery/discovery-report.md).

This repository is currently the **project skeleton**: a cross-platform build,
a Hello World demo, and a test setup ready for TDD. The raytracing itself comes
next.

## Goals & constraints

These shape every technical decision and are why the skeleton looks the way it
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
- **Deadline:** first delivery targeted for **5 January**.

## Planned architecture

The core is organised around SOLID so new shapes/materials plug in via
interfaces without changing the renderer:

- **Maths:** `Vec3`, `Ray`
- **Scene:** `Shape` (Sphere, Plane, Mesh), `Material` (Diffuse, Metal, Glass),
  `Light`, `Camera`, `Scene`
- **Rendering:** `Renderer`, `Sampler`, `BVH`
- **I/O:** `SceneLoader`, `Image`, `ImageWriter`

The current `rt_core` library (just `rt::greeting` for now) is the seed this
grows into.

## Layout

```
.
├── CMakeLists.txt         # Top-level build: defines the rt_core lib + app
├── CMakePresets.json      # One-command configure/build/test presets
├── .devcontainer/         # Reproducible toolchain (VSCode / Zed / CLI)
├── include/core/          # Public headers
├── src/                   # main.cpp (app) + core/ (library sources)
└── tests/                 # GoogleTest unit tests
```

The actual logic lives in a library (`rt_core`) and the executable
(`raytracer`) is a thin wrapper around it. Tests link against the library, so
every piece of behaviour can be tested in isolation — this is what makes TDD
work.

## Cross-platform strategy

We rely on two things so the project builds the same everywhere (Linux, macOS,
Windows):

1. **CMake** as the build system — it generates native build files for any
   compiler/IDE (GCC, Clang, MSVC, Ninja, Make, Visual Studio…).
2. **A dev container** (`.devcontainer/`) — a pinned Ubuntu image with CMake,
   Ninja, GCC and Clang preinstalled. This is the recommended way to work: it
   guarantees everyone has the exact same toolchain, no manual setup.

Dependencies (currently just GoogleTest) are fetched automatically at configure
time via CMake's `FetchContent` — nothing to install by hand.

## Getting started

### Option A — Dev container (recommended)

Requires [Docker](https://www.docker.com/) and an editor with dev-container
support.

- **VSCode:** install the *Dev Containers* extension, open the folder, and run
  **"Dev Containers: Reopen in Container"**.
- **Zed / other:** use the [Dev Container CLI](https://github.com/devcontainers/cli):
  ```sh
  devcontainer up --workspace-folder .
  devcontainer exec --workspace-folder . bash
  ```

Once inside the container, follow the build commands below.

### Option B — Local toolchain

Install **CMake ≥ 3.20**, **Ninja**, and a C++20 compiler.

| Platform | Install |
| -------- | ------- |
| Ubuntu/Debian | `sudo apt install cmake ninja-build g++` |
| macOS (Homebrew) | `brew install cmake ninja` (Xcode CLT for the compiler) |
| Windows | Install CMake + Visual Studio 2022 (MSVC), or use the dev container |

## Build & run the demo

From the project root:

```sh
# Configure (downloads GoogleTest the first time) + build
cmake --preset default
cmake --build --preset default
```

Run the Hello World app:

```sh
./build/bin/raytracer      # Windows: .\build\bin\raytracer.exe
```

Expected output:

```
Hello, Raytracer!
```

> Prefer a GUI? With the **CMake Tools** extension (bundled in the dev
> container) just hit *Configure*, then *Build*, then *Run* from the status bar.

## Testing & TDD

Tests use [GoogleTest](https://google.github.io/googletest/). Run the whole
suite with CTest:

```sh
ctest --preset default
```

Or run the test binary directly for more detailed output:

```sh
./build/bin/rt_tests
```

### The TDD loop

1. **Write a failing test** in `tests/` (add a `TEST(...)` or a new
   `*_test.cpp` — register new files in [tests/CMakeLists.txt](tests/CMakeLists.txt)).
2. **Run the tests** and watch the new one fail (`ctest --preset default`).
3. **Write the minimum code** in `include/core/` + `src/core/` to make it pass.
4. **Re-run** until green, then **refactor** with the tests as your safety net.

See [tests/greeting_test.cpp](tests/greeting_test.cpp) for a worked example that
tests the `rt::greeting` function from the core library.

## License

Student project — add a license before any public release.
