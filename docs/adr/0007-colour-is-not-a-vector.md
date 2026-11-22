# 0007 — A colour is not a vector

## Status

Proposed

## Context

A colour and a vector both hold three doubles. Reusing `Vector` for colours
would save a class, but the two don't mean the same thing: adding a colour to
a position, or taking the dot product of two colours, makes no sense. Colours
also have their own needs: a 0–1 range, conversion to bytes, multiplication
component by component.

## Decision

`Colour` is its own class with `r()`, `g()`, `b()` and scaling by a number.
DRY is about knowledge, not similar-looking lines: the vector maths and the
colour maths are separate pieces of knowledge.

## Consequences

- The compiler refuses `position + colour`.
- Some operations look alike in both classes (scaling); that is accepted.
- Values outside 0–1 are allowed (a strong light can exceed 1); they are
  clamped only when saved to a byte format.

## Rejected alternative

`using Colour = Vector;`: less code, but nothing stops mixing a colour and a
position.
