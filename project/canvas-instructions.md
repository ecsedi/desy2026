# Assignment: Implementing the `Canvas` Class

## Overview

In this assignment you will complete the implementation of the `Canvas` class declared in `canvas.h`. `Canvas` is a 2-D pixel buffer that stores `RGB` color values in a `Matrix<RGB>` and adds:

- Intuitive **(x, y)** coordinate access where **(0, 0)** is the **top-left** corner (x grows right, y grows down).
- Silent out-of-bounds protection — writes to invalid coordinates are discarded without crashing.
- Strict bounds-checked access via `at()` that throws on invalid coordinates.
- PPM P3 file I/O (`load` / `save`).

You are given the complete class declaration with all member variables and helper infrastructure already in place. Your job is to fill in every method body that currently contains a `// TODO` comment.

---

## Files

| File | Your role |
|------|-----------|
| `canvas.h` | **Edit this file.** Replace every `// TODO` block with a correct implementation. |
| `rgb.h` | Provided — do not modify. |
| `matrix.h` | Provided — do not modify. |
| `position.h` | Provided — do not modify. |
| `utils.h` | Provided — do not modify. Contains `skipComments` stream manipulator. |
| `canvas-test.cpp` | Provided — do not modify. Used to verify your implementation. |

---

## What You Must Implement

Work through the `// TODO` comments in order. Each one explains exactly what the method should do.

### 1. `onscreen(x, y)` and `onscreen(pos)` — coordinate validation

`onscreen(x, y)` must return `true` when both coordinates are inside the canvas:

```
0 <= x < width()   AND   0 <= y < height()
```

`onscreen(pos)` simply delegates to `onscreen(pos.x, pos.y)`.

---

### 2. `width()` and `height()` — dimension accessors

These must cast `cols()` and `rows()` (inherited from `Matrix`) to `coord_type` and return them.

**Important:** Notice that the Matrix is constructed as `Matrix<RGB>(canvas_height, canvas_width)` — rows correspond to height and columns correspond to width.

---

### 3. `maximum_rgb_component()` — getter and setter

- The **getter** simply returns `rgb_max`.
- The **setter** rescales every pixel in the canvas if the new maximum differs from the current one:

```
scale_factor = (new_max + 1) / (old_max + 1)     // use double arithmetic
```

Multiply every pixel (iterate with a range-for over `*this`) by `scale_factor`, then update `rgb_max`.

---

### 4. `operator()(x, y)` — coordinate pixel access (non-const and const)

Map canvas coordinates to matrix storage. The base-class `operator()` takes `(row, col)`.

The mapping is direct — no flipping required:

```
Matrix::operator()(y, x)   // row = y, col = x
```

This works because both the canvas and the matrix share the same convention: (0, 0) / row 0 is at the **top**, and y / row index increases **downward**.

If the coordinates are out of bounds, return `offscreen_pixel` instead (the silent sink).

---

### 5. `operator[](pos)` — Position-based pixel access

Delegate directly to `operator()(pos.x, pos.y)`.

---

### 6. `at(x, y)` and `at(pos)` — bounds-checked access

These are identical to `operator()` / `operator[]` except they **throw `std::out_of_range`** instead of silently returning `offscreen_pixel`:

```cpp
// at(coord_type x, coord_type y)
throw std::out_of_range("Coordinates out of bounds");

// at(const Position & pos)
throw std::out_of_range("Position out of bounds");
```

Implement both the `const` and non-`const` overloads for each.

---

### 7. `load(std::istream &)` — PPM P3 parsing

This is the most complex method. Implement it in the steps described in the `// TODO` comment:

1. Read exactly two characters with `is.get()`. Fail if they are not `'P'` and `'3'`.
2. The very next character must be whitespace (check with `std::isspace(is.peek())`). Fail otherwise.
3. Read width `w`, height `h`, and max component `m` from the stream, skipping comments:
   `is >> skipComments >> w >> skipComments >> h >> skipComments >> m;`
4. Validate: if any of `w`, `h`, `m` are `<= 0`, set the failbit and return.
5. Create a temporary `Canvas newcanvas(w, h, m)`.
6. Read its pixel data: `is >> dynamic_cast<Matrix<RGB> &>(newcanvas);`
7. If the stream is still good, move-assign: `*this = std::move(newcanvas);`
8. Return `is`.

"Failing" always means calling `is.clear(std::ios_base::failbit)` and then `return is`.

---

### 8. `load(const std::string &)` — file-based load

- If `filename == "-"`, load from `std::cin`; throw `std::runtime_error("Failed to read image from STDIN")` on failure.
- Otherwise, open `std::ifstream f(filename)`. Throw `std::runtime_error("Failed to open " + filename + " for reading")` if it does not open.
- Call `load(f)`. Throw `std::runtime_error("Failed to read image from " + filename)` on failure.

---

### 9. `save(std::ostream &)` — PPM P3 output

Write the PPM P3 header followed by the pixel matrix:

```
P3
<width> <height>
<max_rgb_component>
<pixel data>
<trailing newline>
```

Use `dynamic_cast<const Matrix<RGB> &>(*this)` with `operator<<` for the pixel data, just as in `load`.

---

### 10. `save(const std::string &)` — file-based save

Mirror of the file-based `load`. Use these error messages:

- `"Failed to write image to STDOUT"`
- `"Failed to open " + filename + " for writing"`
- `"Failed to write image to " + filename`

---

## Compilation

```bash
g++ -std=c++17 -Wall -Wextra -o canvas-test canvas-test.cpp
./canvas-test
```

All tests should pass with no output. Any failing test prints a descriptive message and the program exits with a non-zero status.

---

## Tips

- Read the Doxygen comments carefully — they precisely describe the expected behaviour.
- The `// TODO` comments in the skeleton are ordered to match the description above; implementing them top-to-bottom is the recommended strategy.
- The base class `Matrix<RGB>` already handles memory. You only need to map coordinates and delegate calls.
- When in doubt about the matrix indexing convention, re-read the note in section 4 above.
- Test incrementally: get `width()` / `height()` working before `operator()`, and `operator()` working before `at()`.
