# Exercise: Implementing the `BoundingBox` Class

## Overview

In this exercise you will implement `boundingbox.h` — a header that represents an axis-aligned 2D bounding box. The class tracks the minimum and maximum extents of a collection of `Position` objects, and supports incremental expansion, uniform scaling, aspect-ratio-preserving screen-size computation.

A skeleton file (`boundingbox-skeleton.h`) is provided. Every `// TODO` marks code you must write. Do **not** change the file structure, includes, or existing comments.

---

## Prerequisites

- A correct implementation of `position.h` from the previous exercise.
- C++17 or later.

---

## Tasks

### 1. `ScreenSize` struct

Complete the `ScreenSize` struct with two `public` members of type `unsigned long`:

| Member | Meaning |
|---|---|
| `width` | Width in pixels |
| `height` | Height in pixels |

---

### 2. Private member variables

Inside `BoundingBox`, declare three private members:

| Member | Type | Role |
|---|---|---|
| `is_empty` | `bool` | Whether the box contains any geometry |
| `corner1` | `Position` | Bottom-left corner (min x, min y) |
| `corner2` | `Position` | Top-right corner (max x, max y) |

---

### 3. Constructors

Implement **five** constructors:

1. **Default** — sets `is_empty = true`; the corner values are unimportant.
2. **Single position** `(const Position & p)` — sets `is_empty = false` and initialises both corners to `p`.
3. **Two corners** `(const Position & p1, const Position & p2)` — sets `is_empty = false` and normalises so that `corner1` always holds the component-wise minimum and `corner2` the component-wise maximum. Use `std::min` / `std::max`.
4. **`initializer_list<Position>`** — if the list is empty, set `is_empty = true`; otherwise set `is_empty = false`, seed both corners from `*poslist.begin()` (there is no `operator[]` on `initializer_list`), then iterate and expand.
5. **`vector<Position>`** — same logic as (4); here `poslist[0]` is available.

---

### 4. Accessors

Implement five `const` member functions:

| Function | Return type | Behaviour |
|---|---|---|
| `empty()` | `bool` | Returns `is_empty` |
| `width()` | `Position::value_type` | `std::abs(corner2.x - corner1.x)` |
| `height()` | `Position::value_type` | `std::abs(corner2.y - corner1.y)` |
| `bottom_left()` | `Position` | Returns `corner1` |
| `top_right()` | `Position` | Returns `corner2` |

---

### 5. `screenSize`

Implement:

```cpp
ScreenSize screenSize(unsigned long resolution) const;
```

Use the formulas below, which preserve the aspect ratio while targeting a total pixel count of `resolution`:

```
screen_width  = sqrt(resolution × width()  / height())
screen_height = sqrt(resolution × height() / width())
```

Cast both results to `unsigned long`. Use `std::sqrt` and `static_cast`.

---

### 6. Compound assignment operators

Implement three member operators, each returning `*this` by reference:

**`operator+=(const Position & p)`**
- If the box is empty: seed both corners from `p`, clear `is_empty`.
- Otherwise: expand `corner1` and `corner2` component-wise with `std::min` / `std::max`.

**`operator+=(const BoundingBox & other)`**
- If this box is empty: copy `other`'s state entirely (including its `is_empty`).
- Otherwise: if `other` is not empty, expand component-wise.

**`operator*=(const Position::value_type & factor)`**

Scale around the center:

```
center = (corner1 + corner2) / 2
half_w = width()  * factor / 2
half_h = height() * factor / 2

corner1 = (center.x - half_w, center.y - half_h)
corner2 = (center.x + half_w, center.y + half_h)
```

> **Hint:** You can reuse `Position` arithmetic from the previous exercise.

---

### 7. Non-member operators

Implement six `inline` free functions outside the class:

| Signature | Behaviour |
|---|---|
| `operator+(BoundingBox b, const Position & p)` | Copy of `b` expanded by `p` |
| `operator+(const Position & p, BoundingBox b)` | Same, commutative |
| `operator+(BoundingBox b1, const BoundingBox & b2)` | Union of two boxes |
| `operator*(BoundingBox b, value_type factor)` | Copy of `b` scaled by `factor` |
| `operator*(value_type factor, BoundingBox b)` | Same, commutative |

> **Hint:** Construct a copy and delegate to the corresponding `operator+=` or `operator*=`, exactly as in the `Position` exercise.

---

### 8. Stream output operator

Implement `operator<<` with the following format:

| State | Output example |
|---|---|
| Empty box | `[]` |
| Non-empty box | `[(0,0)-(3,4)]` |

Use `bottom_left()` and `top_right()` (which in turn use `Position`'s `operator<<`). Return the stream by reference.

---

## Verification checklist

- [ ] `BoundingBox b;` compiles and `b.empty() == true`.
- [ ] `BoundingBox b(Position(1,2));` gives `bottom_left() == (1,2)` and `top_right() == (1,2)`.
- [ ] `BoundingBox b(Position(3,4), Position(1,2));` normalises to `corner1=(1,2)`, `corner2=(3,4)`.
- [ ] Initializer-list and vector constructors produce the correct min/max corners.
- [ ] `width()` and `height()` return correct non-negative values.
- [ ] `operator+=(Position)` correctly expands an empty and a non-empty box.
- [ ] `operator+=(BoundingBox)` correctly merges two boxes; adding an empty box has no effect.
- [ ] `operator*=(1.0)` leaves the box unchanged; `operator*=(2.0)` doubles width and height.
- [ ] `screenSize(1000000)` returns width and height whose product is close to 1 000 000.
- [ ] `std::cout << BoundingBox()` prints `[]`.
- [ ] `std::cout << BoundingBox(Position(0,0), Position(3,4))` prints `[(0,0)-(3,4)]`.
