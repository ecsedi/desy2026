# `Line` — Thick Line Segment Drawable

## Overview

`Line` inherits from `Drawable` and renders a **thick line segment** between two endpoints onto a `Canvas`. The rasterization strategy is distance-based: for every pixel in the bounding rectangle of the segment, the pixel center is tested against the segment using a point-to-segment distance function. Any pixel closer than `width/2` is painted, which naturally produces **rounded caps** and works correctly for all orientations including vertical, horizontal, and diagonal lines.

`Dot` is built on top of `Line` — a dot is simply a zero-length `Line` whose width equals the dot diameter.

## Header

```cpp
#include "line.h"
```

## Class Members

| Member | Type | Description |
|--------|------|-------------|
| `from` | `Position` | Start point of the segment. |
| `to`   | `Position` | End point of the segment. |
| `color` | `color_type` (= `Canvas::value_type`) | RGB color of the line. |
| `width` | `double` | Diameter of the line in canvas units. |

## Constructors

```cpp
Line();   // Zero-length, black, width 0, at origin

constexpr Line(
  const Position   & pos_from,
  const Position   & pos_to,
  const color_type & line_color = {0,0,0},
  const double     & line_width = 1.0
);
```

## Private Helper

### `pointToSegmentDistance`

```cpp
double pointToSegmentDistance(
  double px, double py,
  double x0, double y0,
  double x1, double y1
) const;
```

Returns the Euclidean distance from point `(px, py)` to the nearest point on the segment `(x0,y0)–(x1,y1)`.

**Algorithm:**

1. Compute `dx = x1 - x0`, `dy = y1 - y0`, `length_sq = dx² + dy²`.
2. **Degenerate case** (`length_sq == 0`): return distance from `(px, py)` to `(x0, y0)`.
3. **General case:** Project `(px, py)` onto the infinite line and clamp the parameter `t` to `[0, 1]`:
   ```
   t = ((px - x0)*dx + (py - y0)*dy) / length_sq
   t = clamp(t, 0.0, 1.0)
   proj = (x0 + t*dx,  y0 + t*dy)
   ```
4. Return distance from `(px, py)` to `proj`.

## Methods to Implement

### `length`

```cpp
double length() const;
```

Returns the Euclidean distance between `from` and `to`.

### `draw`

```cpp
virtual Canvas & draw(Canvas & canvas) const override;
```

Rasterizes the segment onto the canvas:

1. Return immediately if `width <= 0`.
2. Compute `half_width = width / 2`.
3. Build the integer pixel bounding box by rounding `min/max` of `from`/`to` coordinates outward, expanded by `half_width + 1`.
4. Iterate over every `(x, y)` in the box. For each pixel, test the **pixel center** `(x + 0.5, y + 0.5)` using `pointToSegmentDistance`.
5. If the distance is ≤ `half_width`, set `canvas(x, y) = color`.

> **Note:** The canvas uses `canvas(x, y)` (function-call syntax) for writing, unlike `Point` which uses `canvas[pos]`.

### `transform`

```cpp
virtual Line & transform(const Transformation & t) override;
```

Applies `t` to both `from` and `to`, then returns `*this`.

### `boundingBox`

```cpp
virtual BoundingBox boundingBox() const override;
```

Returns an axis-aligned box expanded by `width/2` on each side:

```
lower-left  = { min(from.x, to.x) - width/2,  min(from.y, to.y) - width/2 }
upper-right = { max(from.x, to.x) + width/2,  max(from.y, to.y) + width/2 }
```

### `copy`

```cpp
virtual Line * copy() const override;
```

Allocates and returns a heap copy of `*this`.

## Stream Output

A free function is already provided:

```cpp
std::ostream & operator << (std::ostream & os, const Line & line);
// Prints: [from-to]
```

## Relationship to Other Classes

```
Drawable  (abstract base)
  └── Line    ← you implement this
        ↑
      used by Dot (a Dot is a Line from pos to pos with width = diameter)
```
