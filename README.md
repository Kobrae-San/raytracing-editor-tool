# Raytracing Live Demo 2026

A C++ raytracer built incrementally during the course, using TDD.

---

## Project structure

```
.
├── .devcontainer/      # Dev container config (VSCode / Zed)
├── src/
│   └── main.cpp        # Main entry point
├── tests/
│   └── test_main.cpp   # Catch2 unit tests
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

## Building

```bash
# Configure (only needed once, or after changing CMakeLists.txt)
cmake -S . -B build -DCMAKE_BUILD_TYPE=Debug

# Build everything (main binary + test binary)
cmake --build build
```

---

## Running the Hello World demo

```bash
./build/raytracer
# Hello, Raytracer!
```

---

## Running the tests

```bash
# Run all tests via CTest
ctest --test-dir build --output-on-failure

# Or run the test binary directly for more verbose output
./build/tests --reporter compact
```

You should see:

```
All tests passed (2 assertions in 2 test cases)
```

---

## Test-driven development workflow

Tests live in `tests/`. Add a new `TEST_CASE` before writing the implementation, confirm it fails, then implement until it passes.

```cpp
// tests/test_vec3.cpp  (example)
#include <catch2/catch_test_macros.hpp>
#include "vec3.h"

TEST_CASE("Vec3 dot product", "[vec3]") {
    Vec3 a{1, 0, 0};
    Vec3 b{0, 1, 0};
    REQUIRE(dot(a, b) == 0.0f);
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

1. Create `src/yourfile.cpp` and optionally `src/yourfile.h`.
2. Add it to `CMakeLists.txt`:
   ```cmake
   target_sources(raytracer PRIVATE src/yourfile.cpp)
   ```
3. For tests, add a new `.cpp` under `tests/` and add it similarly to the `tests` target:
   ```cmake
   target_sources(tests PRIVATE tests/test_yourfile.cpp)
   ```
