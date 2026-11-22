# 0012 — Short commands with a Makefile

## Status

Proposed

## Context

The raw CMake commands (`cmake -S . -B build`, `cmake --build build`,
`ctest --test-dir build`) are long and easy to get wrong, for people and for
AI assistants alike.

## Decision

A `Makefile` at the root with four targets: `build`, `run`, `test` and
`clean`. It only calls CMake; CMake stays the build system (ADR 0002). CI and
`AGENTS.md` use the same targets.

## Consequences

- One short command for each everyday action, the same in the container,
  in CI and in the docs.
- `make` isn't native on Windows: outside the dev container, use the raw
  CMake commands from the README.
- Recipe lines need tabs, and Windows line endings break them.
