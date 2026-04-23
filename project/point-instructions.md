# `Point` — Single-Pixel Drawable

## Overview

`Point` is the simplest concrete drawable in the hierarchy. It inherits from `Drawable` and renders as **exactly one pixel** on a `Canvas`, at the integer coordinates nearest to its stored `Position`. No diameter or width concept applies — the point is always one pixel, regardless of any scaling.

## Header

```cpp
#include "point.h"
```

## Class Members

| Member | Type | Description |
|--------|------|-------------|
| `pos` | `Position` | The pixel position of the point. |
| `color` | `color_type` (= `Canvas::value_type`) | The RGB color of the pixel. |

## Constructors

```cpp
Point();                                          // Default: uninitialized pos and color
Point(const Position& position,
      const color_type& point_color = {0,0,0});  // Explicit position and optional color
```

The two-argument constructor is `constexpr`.  Copy and move constructors are defaulted.

## Methods to Implement

### `draw`

```cpp
virtual Canvas & draw(Canvas & canvas) const override;
```

Sets the single canvas pixel at `pos` to `color` and returns the canvas. The canvas provides an index operator `canvas[pos]` for this purpose.

### `transform`

```cpp
virtual Point & transform(const Transformation & t) override;
```

Replaces `pos` with `t * pos` (i.e., applies the affine transformation to the stored position). Returns `*this` to allow chaining.

### `boundingBox`

```cpp
virtual BoundingBox boundingBox() const override;
```

Returns a 1×1 axis-aligned box centered on `pos`:

```
lower-left  = { pos.x - 0.5, pos.y - 0.5 }
upper-right = { pos.x + 0.5, pos.y + 0.5 }
```

### `copy`

```cpp
virtual Point * copy() const override;
```

Allocates and returns a heap copy of `*this`. The caller owns the returned pointer.

## Relationship to Other Classes

```
Drawable  (abstract base)
  └── Point   ← you implement this
```

Unlike `Dot`, `Point` does **not** use `Line` internally. It writes directly to the canvas via the index operator.

## Key Differences: `Point` vs `Dot`

| | `Point` | `Dot` |
|-|---------|-------|
| Pixel size | Always 1 pixel | `size` canvas units (diameter) |
| Rendering | Direct pixel write | Delegates to `Line` |
| Has `size` member | No | Yes |
| Scales with zoom | No | Yes |
