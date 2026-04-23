# Assignment: Implementing 2D Affine Transformations

## Objective
You will implement a complete `Transformation` class that represents 2D affine transformations using 3×3 homogeneous matrices. This class is a key building block for graphics, geometry, and computer vision applications.

## Provided (do NOT modify these)
- `matrix.h` – base class `Matrix<double>` with row/column access via `operator()(i,j)` and the required constructor
- `position.h` – `Position` struct/class with public `x` and `y` members
- `boundingbox.h` – `BoundingBox` class with `bottom_left()`, `top_right()`, `width()` and `height()`

## What You Have to Implement
Fill in **every `// TODO`** in the skeleton file `transformation.h`.

The detailed specification for each method is already written in the Doxygen-style comments inside the file. Follow those comments exactly.

### Hints / Requirements
- All static factory methods (`ident`, `translate`, `scale`, …) must create the matrix using the private constructor and the 9-element initializer list.
- `operator*=` performs **post-multiplication** (`this = this * other`).
- The free `operator*(Transformation, Transformation)` should simply use the `*= ` operator (see the comment in the reference implementation).
- The free `operator*(Transformation, Position)` must use homogeneous coordinates and divide by the homogeneous `w` component (`t(2,2)`).
- `toScreen` must compose the three transformations **exactly** in the order shown in its comment (the operator* will handle the rest).
- You may use `std::min`, `cos`, `sin`, etc. from `<cmath>`.
