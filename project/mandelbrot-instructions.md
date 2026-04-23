# Assignment: Implementing `mandelbrot.cc`

## Overview

In this assignment you will complete in `mandelbrot.cc`:

- Stream insertion and stream extraction operators for MandelParams.
- `mandel()` — the core Mandelbrot iteration for a single complex point.
- `genMandel()` — the top-level renderer that wires together `ComplexGrid`, `Canvas`, palette generation, and file I/O.

Everything else — `MandelParams`, both palette generators, and the `STANDALONE` main — is already complete and must not be modified.

---

## Files

| File | Your role |
|------|-----------|
| `mandelbrot-skeleton.cc` | **Edit this file.** Fill in TODOs. |
| `mandelbrot-params-full.json` | Full Mandelbrot overview — try this first. |
| `mandelbrot-params-seahorse.json` | Zoom into the Seahorse Valley. |
| `mandelbrot-params-elephant.json` | Zoom into the Elephant Valley. |
| `mandelbrot-params-spiral.json` | Deep zoom into a spiral near a satellite bulb. |

The support files `rgb.h`, `utils.h`, `canvas.h`, `complexgrid.h`, and `json.hpp` are provided and must not be modified.

---

## Background: the Mandelbrot set

A point **c** in the complex plane belongs to the Mandelbrot set if the sequence

```
z₀ = 0
zₙ₊₁ = zₙ² + c
```

remains bounded forever.  In practice we iterate up to a fixed limit `maxiter` and test whether |z| ≥ 2 (the standard escape radius).  If the sequence escapes we record the iteration count; if it reaches `maxiter` without escaping we treat the point as being inside the set.

---

## What You Must Implement

### 1. `mandel(c, maxiter)`

```cpp
unsigned int mandel(const complex & c, unsigned int maxiter);
```

**Algorithm:**

1. Initialise `z = 0` (type `complex`) and `i = 0` (type `unsigned int`).
2. Loop **while** `i < maxiter + 1` **and** `std::abs(z) < 2`:
   - Increment `i`.
   - Update `z = z*z + c`.
3. If `i > maxiter` the point did not escape — return **0**.
4. Otherwise return **i** (the escape iteration count).

**Why return 0 for interior points?**  
Palette index 0 is reserved for the interior colour.  Escape counts start at 1, which means every escaped point maps to a distinct non-zero palette entry.

**Key points to get right:**

- The loop condition uses `maxiter + 1`, not `maxiter`. This ensures that a point which would escape on exactly iteration `maxiter` is still counted as escaped.
- Use `std::abs(z)` for the complex modulus (not `std::norm`, which returns the squared modulus).
- The return value is **always** in the set {0} ∪ {1, …, maxiter}.

**Worked examples:**

| c | maxiter | Expected return | Reason |
|---|---------|-----------------|--------|
| 0 + 0i | 255 | 0 | z stays 0 — never escapes |
| −1 + 0i | 255 | 0 | Period-2 orbit: 0 → −1 → 0 → … |
| 3 + 0i | 255 | 1 | z = 3 after first iteration, |3| ≥ 2 |
| 0 + 1i | 255 | > 0 | Escapes after a few iterations |

---

### 2. `genMandel(mp)`

```cpp
void genMandel(const MandelParams & mp);
```

This function orchestrates the entire render pipeline:

**Step 1 — Build the complex grid**

```cpp
ComplexGrid grid(mp.corner1, mp.corner2, mp.resolution);
```

**Step 2 — Create the canvas**

```cpp
Canvas canvas(grid.width(), grid.height());
```

The canvas uses the default maximum RGB component of 255.

**Step 3 — Generate the palette**

```cpp
Palette palette = generateRandomPalette(mp.maxiter + 1, mp.palgenseed);
```

The palette has `maxiter + 1` entries: index 0 is the interior colour, indices 1…maxiter are the escape colours.

**Step 4 — Render**

Iterate over every pixel. The canvas pixels and grid nodes are both in row-major order, so a single linear counter `n` keeps them in sync:

```cpp
ComplexGrid::size_type n = 0;
for (auto & pixel : canvas) {
    auto iter = mandel(grid[n], mp.maxiter);
    pixel = palette[iter];
    ++n;
}
```

**Step 5 — Save**

```cpp
canvas.save(mp.imagefile);
```

Pass `"-"` to write PPM data to stdout; any other string is treated as a file path.

**Step 6 — Log (optional but required)**

If `mp.imagefile != "-"`, print to `std::cerr`:

```
Saved image to <filename>
```

---

## Trying the Parameter Files

Once both functions are implemented, build the standalone binary and run each parameter file:

```bash
g++ -std=c++17 -DSTANDALONE -O2 -o mandelbrot mandelbrot.cc
./mandelbrot mandelbrot-params-full.json
./mandelbrot mandelbrot-params-seahorse.json
./mandelbrot mandelbrot-params-elephant.json
./mandelbrot mandelbrot-params-spiral.json
```

Each run writes a `.ppm` file that you can open in any image viewer that supports PPM (e.g. GIMP, IrfanView, `eog`, or convert with ImageMagick).

| Parameter file | Region | What you should see |
|----------------|--------|---------------------|
| `mandelbrot-params-full.json` | Full overview [−2.5,−1.2]×[1.0,1.2] | Classic cardioid + bulb, symmetric about the real axis |
| `mandelbrot-params-seahorse.json` | Seahorse Valley zoom | Interleaved spirals resembling seahorse tails |
| `mandelbrot-params-elephant.json` | Elephant Valley zoom | Rows of elephant-trunk-shaped filaments |
| `mandelbrot-params-spiral.json` | Deep spiral zoom | A single large spiral with fine tendrils |

---

## Tips

- Implement and test `mandel()` first — `genMandel()` depends on it.
- The loop bound `i < maxiter + 1` is deliberate: make sure you copy it exactly.
- Watch out for `std::abs` vs `std::norm`: `std::abs` returns |z|, while `std::norm` returns |z|². You want `std::abs(z) < 2`, not `std::norm(z) < 4` (they are mathematically equivalent, but the test checks the exact loop structure indirectly through edge-case counts).
- The palette has `maxiter + 1` entries (indices 0…maxiter). Calling `palette[iter]` where `iter` is the return value of `mandel()` is always safe because `mandel()` is guaranteed to return a value in {0, …, maxiter}.
