# 0008 — Points and directions share the Vector class

## Status

Accepted

## Context

A point (a position in the scene) and a direction (where a ray goes) are
different ideas: adding two points makes no sense, while adding a direction to
a point does. Separate `Point` and `Direction` classes would let the compiler
catch some mistakes.

## Decision

Keep one `Vector` class for both, as the client and the reference books
(e.g. _Ray Tracing in One Weekend_) do. Names make the role explicit:
`origin`, `center`, `point` for points; `direction`, `normal`, `toLight` for
directions.

## Consequences

- One set of operations, tested once; the ray equation `O + t * D` reads like
  the maths.
- The compiler won't stop `point + point`. Reviews and names have to.
- Revisit if such a bug ever reaches a render.

## Rejected alternative

`Point` and `Direction` classes: safer, but twice the operators and
conversions everywhere before we know we need them.
