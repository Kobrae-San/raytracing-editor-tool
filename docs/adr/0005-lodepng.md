# 0005 — Use LodePNG for PNG Encoding

## Status

Accepted

## Context

`PngSaver` needs to encode an in-memory `Image` (a grid of `Colour`s) as a
PNG file on disk. We need a PNG encoder that is easy to vendor into a CMake
project without a system-wide package manager, since the project already
relies on `FetchContent` for Catch2 rather than external package managers.

Alternatives considered:

- **libpng** — the reference implementation, but it depends on zlib and
  expects to be installed as a system library; integrating it without a
  package manager is significantly more work for a student project.
- **stb_image_write** — a popular single-header library, simple to vendor,
  but it only supports basic PNG writing (no fine control over compression)
  and mixes several unrelated image formats in one header.
- **Writing raw PPM instead of PNG** — trivial to implement by hand, but PPM
  is not a format artists or other tools can open directly, which defeats
  the point of `PngSaver`.

## Decision

Use [LodePNG](https://github.com/lvandeve/lodepng), fetched via CMake
`FetchContent`. LodePNG has no CMake build of its own and no tagged
releases, so we pin `GIT_TAG` to a specific commit
(`7b2893e35891c0c85bee5595caafaf3c2044b409`) and build `lodepng.cpp` as our
own small static library target.

## Consequences

**Positive:**

- Single `.cpp`/`.h` pair, easy to read and debug when something goes wrong.
- No system dependency (no zlib, no package manager) — fits the project's
  existing `FetchContent`-only approach.
- Pinning to a commit hash keeps builds reproducible even without releases.

**Negative:**

- No tagged releases means upgrading requires picking a new commit by hand
  and re-verifying it builds, rather than bumping a version number.
- LodePNG's single-file design means we build and maintain our own minimal
  CMake target for it instead of using a ready-made one.
- LodePNG is less battle-tested than libpng for edge cases (unusual colour
  types, interlacing), though none of those are needed here.
