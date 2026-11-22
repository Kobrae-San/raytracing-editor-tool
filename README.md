# Raytracing Live Demo 2026

A C++ raytracer built incrementally during the course, using TDD.

[![CI](https://github.com/glassworks/raytracing-live-demo-2026/actions/workflows/ci.yml/badge.svg)](https://github.com/glassworks/raytracing-live-demo-2026/actions/workflows/ci.yml)

Licence: [MIT](LICENSE) · [Contributing](CONTRIBUTING.md) · [Code of Conduct](CODE_OF_CONDUCT.md)

---

## Project structure

```
.
├── .devcontainer/        # Dev container config (VSCode / Zed)
├── docs/adr/             # Architecture decision records
├── src/
│   ├── main.cpp          # Main entry point
│   ├── math/             # Vector, Ray
│   └── geometry/         # Sphere, and future shapes
├── tests/
│   ├── test_main.cpp     # Catch2 entry + smoke tests
│   └── math/             # Tests for src/math
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
3. The container image provides GCC, CMake ≥ 3.20, and Git. Catch2 is downloaded automatically at first build.
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

## Running the Hello World demo

```bash
make run
# Hello, Raytracer!
```

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

Tests live in `tests/`. Add a new `TEST_CASE` before writing the implementation, confirm it fails, then implement until it passes.

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
