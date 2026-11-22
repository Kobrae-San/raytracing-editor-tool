# 0011 — A shape has a material

## Status

Accepted

## Context

A sphere can be matte, shiny or flat, and so can a plane. Inheritance
(`RedLambertSphere`, `MetalPlane`, ...) would need one class per shape and
material pair.

## Decision

Composition: every shape holds a material and passes it in the `HitInfo`;
the renderer asks that material to shade the hit. `Material` is an interface
(Strategy) with `FlatShader` and `LambertShader`, so a new material is one new
class. Shapes hold it through `std::shared_ptr<const Material>`, so several
shapes can share one material; a `HitInfo` points to it without owning it.

## Consequences

- Shapes × materials combine freely; adding either touches no existing class.
- Each shape repeats the small plumbing of its material into the hit (parked
  until a third shape).
- The course's reference uses one concrete `Material` class held by value. We
  chose an interface from the start because two materials already exist.

## Rejected alternative

Inheritance (a sphere _is a_ material, or one subclass per pair): the number
of classes multiplies, and a material can't be shared.
