# Agents

## Commands

**Build:**
```
make build
```

**Run:**
```
make run
```

**Test:**
```
make test
```

**Clean:**
```
make clean
```

## Contributing

See [CONTRIBUTING.md](CONTRIBUTING.md) for dev container setup, make commands, TDD workflow, and how to work with ADRs.

See [CODE_OF_CONDUCT.md](CODE_OF_CONDUCT.md) for community standards.

CI ([.github/workflows/ci.yml](.github/workflows/ci.yml)) runs `make build` and `make test` on every pull request.

## Code style

- Private member variables are prefixed with an underscore (e.g. `_x`, `_y`,
  `_z`).
- Do not prefix getters with `get` (it is redundant); name them after the value
  they return (e.g. `x()`, not `getX()`).

## How we work

- Test-driven development: write the test first and watch it fail, then the
  least code that passes, then refactor while the tests stay green.
- Expected values come from the maths, never from running the code. Ask
  before changing what a failing test expects.
- Compare doubles within a tolerance (`requireVectorsEqual`,
  `requireColoursEqual`, `WithinAbs` in `tests/test_helpers.h`), never with
  `==` unless the result is a whole number.
- One small step at a time. Keep the C++ simple.
- Don't build or run anything on the host: use the dev container.

## Source layout

- New classes go in a folder named for their concept under `src/` (see
  `docs/adr/0006-folder-per-concept.md`), with their tests in the matching
  folder under `tests/`. Register new files in `CMakeLists.txt`.
- Includes start from `src/`, e.g. `#include "math/vector.h"`.
- Keep `docs/domain/domain-model.md` up to date when a class or a link changes.

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
