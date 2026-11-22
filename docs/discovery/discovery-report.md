# Discovery report

## Problem statement

In 2035, when AI-generated software works on demo day and then breaks with no one able to explain why, that's the reason a Los Angeles film studio needs a tool written in C++ (the only royalty-free language left) that is tested, documented, open to its partner studios and fast enough to render an entire movie.

## Client interview summary

### Speed and quality

**Need:** Fast, high-quality images; artists shouldn't wait during renders.

> **Q:** _(spontaneous)_
>
> **A:** "We don't want to take cigarette breaks while rendering." / "Fast images and high quality."

**My conclusion:** Two needs: quick previews for artists, and enough throughput to render the whole film. Quality vs. speed must be adjustable (preview / final modes).

### Reliability

**Need:** Correct images, and problems that can be explained.

> **Q:** _(spontaneous)_
>
> **A:** "Six months ago we had black artefacts in our images while rendering got slower."

**My conclusion:** Automated tests (maths + reference images), performance benchmarks and logging. Black pixels in ray tracers often come from NaN values or self-intersection: to be covered by tests.

### CPU only

**Need:** All rendering on CPU.

> **Q:** _(spontaneous)_
>
> **A:** "Everything needs to be rendered by the CPU."

**My conclusion:** Performance through multithreading, an acceleration structure (BVH) and cache-friendly code; frames can be split across machines.

### Schedule

> **Q ([Djédjé Gboble]):** "Given that you need 3 months to make your movie, what is our deadline?"
>
> **A:** "January the 5th."

### Independence and maintenance

> **Q ([Djédjé Gboble]):** "Are there specific features you want that aren't always in rendering software?"
>
> **A:** "We are limited to MIA's features; asking for new ones takes too long."

> **Q ([A colleague]):** "Who will maintain the project after delivery?"
>
> **A:** "Our partners, who will use it and take part in its maintenance."

**My conclusion:** The real need is extensibility: add shapes, materials or lights without touching the core (Open/Closed). Partners need documentation, a contribution guide, CI and code reviews.

### Open questions

- Scene file format? (answer "no extension" unclear) Import of existing MIA assets?
- Target render time per frame (preview / final)? Resolution and required effects?
- Film length, available machines and cores?
- Speed vs. quality: which wins in a conflict?
- Does production start after January 5th or run in parallel?
- Which MIA features are needed on day one? Sample scenes with the black artefacts?
- Partner contribution model and licence? Output formats (PNG, EXR)?

## State of the art

| Solution  | Maker                   | Licence                          | Pricing (16 Nov 2026)                | Capabilities                                   | Sources                                                                                                                             |
| --------- | ----------------------- | -------------------------------- | ------------------------------------ | ---------------------------------------------- | ----------------------------------------------------------------------------------------------------------------------------------- |
| Arnold    | Autodesk                | Proprietary, subscription        | ≈ $430/year (third-party listing)    | CPU/GPU Monte Carlo ray tracer for film        | [Autodesk](https://www.autodesk.com/products/arnold/buy), [FitGap](https://us.fitgap.com/products/008657/autodesk-arnold)           |
| RenderMan | Pixar                   | Proprietary, free non-commercial | $595/licence + $250/year maintenance | Pixar's film renderer + Tractor farm scheduler | [RenderMan store](https://renderman.pixar.com/store/), [Super Renders Farm](https://superrendersfarm.com/article/pixar-render-farm) |
| V-Ray     | Chaos                   | Proprietary, subscription        | Solo $514.80/year                    | Photoreal renderer for many 3D tools           | [Chaos](https://www.chaos.com/vray/jumpstart)                                                                                       |
| Redshift  | Maxon                   | Proprietary, subscription        | Not verified                         | GPU renderer, CPU mode since 3.5               | [CG Channel](https://www.cgchannel.com/2022/04/maxon-ships-redshift-3-5/)                                                           |
| Cycles    | Blender Foundation      | Apache 2.0                       | Free                                 | C/C++ path tracer, CPU (SIMD) + GPU            | [cycles-renderer.org](https://cycles-renderer.org/)                                                                                 |
| pbrt-v4   | Pharr, Jakob, Humphreys | Open source                      | Free                                 | C++ reference renderer for learning/research   | [pbrt.org](https://pbrt.org/)                                                                                                       |

Commercial renderers are mature but reproduce the client's problem: recurring licences, closed code, vendor-driven roadmap. Cycles is open but too large to master by January. Our value: a smaller renderer the studio fully owns and understands, tested and built for extension.

## What is ray tracing?

Ray tracing is an image rendering technique who simulate the real behaviour of light to provide ultra-realistic images.

**Sources:** [Ray Tracing in One Weekend](https://raytracing.github.io/) (starting point), [Physically Based Rendering](https://pbr-book.org/) (reference).

## What is C++?

### Programming paradigms

Compiled language, fast, object oriented, typed.

### What to watch out for

- Memory: no garbage collector; use RAII and smart pointers, not raw `new`/`delete`.
- Undefined behaviour: may silently produce wrong results; use warnings and sanitizers.
- Multithreading: avoid data races (read-only scene, per-thread data).
- Floating-point: NaN and self-intersection bugs.
- Performance: avoid copies and allocations in hot loops.
- AI-generated C++ needs careful review and tests.

### Shaping the domain model

- **Maths:** `Vec3`, `Ray` (shared once, DRY).
- **Scene:** `Shape` (Sphere, Plane, Mesh), `Material` (Diffuse, Metal, Glass), `Light`, `Camera`, `Scene`.
- **Rendering:** `Renderer`, `Sampler`, `BVH`.
- **I/O:** `SceneLoader`, `Image`, `ImageWriter`.
  SOLID: one responsibility per class; new shapes/materials added via interfaces without changing the renderer (Open/Closed); the renderer depends on abstractions, which makes it testable (Dependency Inversion).

**Sources:** [LearnCpp](https://www.learncpp.com/) (starting point), [cppreference](https://en.cppreference.com/) and [C++ Core Guidelines](https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines) (reference).
