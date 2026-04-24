# `Dot` — Filled Circular Dot Drawable

## Overview

`Dot` inherits from `Drawable` and renders a **filled disk** of a given diameter centered at a position. Its implementation is intentionally thin: rather than handling rasterization directly, it **delegates to `Line`** by constructing a zero-length line segment (`from == to`) with `width == size`. Because `Line` uses a distance test with rounded caps, a zero-length segment produces a perfect circle.

## Header

```cpp
#include "dot.h"
```

`dot.h` includes `line.h`, so `Line` is available within the implementation.

## Class Members

| Member | Type | Description |
|--------|------|-------------|
| `pos`   | `Position` | Center of the dot. |
| `color` | `color_type` (= `Canvas::value_type`) | RGB fill color. |
| `size`  | `double` | Diameter of the dot in canvas units. |

## Constructors

```cpp
Dot();   // Default: uninitialized members

Dot(
  const Position   & position,
  const color_type & dot_color = {0,0,0},
  double             diameter  = 1
);
```

## Methods to Implement

### `draw`

```cpp
virtual Canvas & draw(Canvas & canvas) const override;
```

Construct a `Line` from `pos` to `pos` (same point for both endpoints) using `color` and `size` as the line width, then call its `draw` method and return the result. This one-liner is the entire rendering implementation.

```
return Line(pos, pos, color, size).draw(canvas);
```

### `transform`

```cpp
virtual Dot & transform(const Transformation & t) override;
```

Apply `t` to `pos` and return `*this`. Only the center position is transformed; `size` and `color` are unaffected.

### `boundingBox`

```cpp
virtual BoundingBox boundingBox() const override;
```

Returns a square box of side `size` centered on `pos`:

```
lower-left  = { pos.x - size/2,  pos.y - size/2 }
upper-right = { pos.x + size/2,  pos.y + size/2 }
```

### `copy`

```cpp
virtual Dot * copy() const override;
```

Allocates and returns a heap copy of `*this`.

## Relationship to Other Classes

```
Drawable  (abstract base)
  └── Dot     ← you implement this
               (internally uses Line for rendering)
```

## Key Differences: `Dot` vs `Point`

| | `Dot` | `Point` |
|-|-------|---------|
| Pixel footprint | `size` canvas units (diameter) | Always 1 pixel |
| Rendering | Delegates to `Line` | Direct pixel write |
| Has `size` member | Yes | No |
| Scales with zoom | Yes | No |
