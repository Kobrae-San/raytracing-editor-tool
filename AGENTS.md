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

## Architecture decisions

Our architecture decisions live in `docs/adr/`. Read them before changing the build system, tooling, or test setup.

## Rules

- Never go against an accepted ADR. To change a decision, write a new ADR with status `Proposed` and ask the user.
- Never set an ADR status to `Accepted`.
