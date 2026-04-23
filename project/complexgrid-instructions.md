# Assignment: Implementing the `ComplexGrid` Class

## Overview

In this assignment you will complete the implementation of the `ComplexGrid` class declared in `complexgrid-skeleton.h`. `ComplexGrid` builds a regular 2-D grid of `std::complex<double>` values that sample a rectangular region of the complex plane. It is the foundation of a Mandelbrot / Julia set renderer: you construct a grid once, then iterate over its nodes to compute per-pixel escape times.

The class is already declared with all member variables in place. Your task is to fill in every method body and the constructor that currently contain `// TODO` comments.

---

## Files

| File | Your role |
|------|-----------|
| `complexgrid.h` | **Edit this file.** Replace every `// TODO` with a correct implementation. |
| `complexgrid-test.cpp` | Provided — do not modify. Used to verify your implementation. |

---

## Background: the complex plane grid

The grid covers an axis-aligned rectangle in the complex plane given by two corners. After normalisation:

- `bl` (bottom-left) holds the **minimum** real and imaginary parts.
- `tr` (top-right) holds the **maximum** real and imaginary parts.

Nodes are laid out in **row-major order, top-left first** — that is, the first node has the largest imaginary part (top of the image) and real part equal to `bl.real()`. The real part increases as the column index increases; the imaginary part *decreases* as the row index increases. This matches the screen convention used by the `Canvas` class (row 0 = top).

---

## What You Must Implement

Work through the `// TODO` comments in order.

### 1. Constructor — member initialiser list

Six members must be initialised before the constructor body runs:

**`bl` and `tr` — normalised corners**

Regardless of the order the corners are passed in, `bl` must hold the minimum values and `tr` the maximum:

```cpp
bl = complex{ std::min(corner1.real(), corner2.real()),
              std::min(corner1.imag(), corner2.imag()) };

tr = complex{ std::max(corner1.real(), corner2.real()),
              std::max(corner1.imag(), corner2.imag()) };
```

**`res`** — store `resolution` directly.

**`w` and `h` — aspect-ratio-preserving dimensions**

The width and height are chosen so that `w * h ≈ resolution` and `w / h` matches the aspect ratio of the rectangle:

```
w = sqrt( resolution * width_of_region  / height_of_region )
h = sqrt( resolution * height_of_region / width_of_region  )
```

where `width_of_region = tr.real() - bl.real()` and `height_of_region = tr.imag() - bl.imag()`. Cast both results to `size_type`.

**`nodes`** — a `std::vector<complex>` of size `w * h`.

---

### 2. Constructor — body (filling the nodes)

After the member initialiser list runs, fill `nodes` row by row.

Start at the **top-left** complex value:

```
current = complex{ bl.real(), tr.imag() }
```

Step sizes:

```
dx = (tr.real() - bl.real()) / w     // advance right along a row
dy = (tr.imag() - bl.imag()) / h     // step down between rows
```

Loop structure:

```
n = 0
for y in 0 .. h-1:
    for x in 0 .. w-1:
        nodes[n] = current
        n++
        current.real += dx
    current.real = bl.real()   // reset to left edge
    current.imag -= dy         // move down one row
```

Note that `dy` is positive (since `tr.imag() > bl.imag()`), so subtracting it moves the imaginary part downward.

---

### 3. Simple accessors

These are all one-liners:

| Method | Returns |
|--------|---------|
| `width()` | `w` |
| `height()` | `h` |
| `bottom_left()` | `bl` |
| `top_right()` | `tr` |
| `resolution()` | `res` |
| `size()` | `nodes.size()` |

---

### 4. `operator()(x, y)` — 2D node access

Nodes are stored in row-major order. Column `x`, row `y` maps to linear index:

```
nodes[w * y + x]
```

Return a `const` reference to that element.

---

### 5. `operator[](n)` — linear node access

Simply return `nodes[n]`.

---

### 6. `begin()` and `end()`

Return `nodes.begin()` and `nodes.end()` respectively.

---

### 7. `operator<<` — stream output (free function)

Print all nodes in row-major order:

- If `n > 0` and `x == 0` (start of a new row), print `"\n"`.
- If `x > 0` (not the first node in a row), print `" "`.
- Print `grid[n]`.

where `x = n % grid.width()`.

---

## Tips

- Implement the member initialiser list first, then verify `width()` / `height()` / `size()` before tackling the node-filling loop.
- The imaginary part of `current` starts at `tr.imag()` (top of the region) and *decreases* — make sure you subtract `dy`, not add it.
- `operator()(x, y)` and `operator[](n)` both return `const` references into `nodes`; neither modifies anything.
- `std::complex` member functions `.real()` and `.imag()` have both a getter (no argument) and a setter (one argument) form — the setter is used in the loop: `current.real(new_value)`.
