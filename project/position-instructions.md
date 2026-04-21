# Exercise: Implementing the `Position` Class

## Overview

In this exercise you will implement `position.h` — a small but complete C++ header that represents a 2D point or vector in Cartesian coordinates. The finished class will support arithmetic operators, stream output.

A skeleton file (`position.h`) is provided. Every `// TODO` comment marks a piece of code you must write. Do **not** change the file structure, includes, or any existing comments.

---

## Prerequisites

- C++17 or later

---

## Tasks

### 1. Type aliases

Inside the `Position` class, add two `public` type aliases:

| Alias | Underlying type |
|---|---|
| `value_type` | `double` |
| `complex` | `std::complex<value_type>` |

These aliases let the rest of the code remain generic with respect to the numeric type.

---

### 2. Member variables

Declare two `public` member variables of type `value_type`:

- `x` — the horizontal coordinate
- `y` — the vertical coordinate

---

### 3. Constructors

Implement **three** `constexpr` constructors:

1. **Default constructor** — initialises `x` and `y` to `0`.
2. **Coordinate constructor** — accepts `pos_x` and `pos_y` and initialises `x` and `y` from them.
3. **Complex constructor** — accepts a `const complex &` and initialises `x` from its real part and `y` from its imaginary part.

> **Hint:** Use member-initialiser lists (`: x(...), y(...)`) for all three.

---

### 4. Compound assignment operators

Implement four member operators, each returning `*this` by reference:

| Operator | Behaviour |
|---|---|
| `operator+=` | Add the components of `other` to `x` and `y` |
| `operator-=` | Subtract the components of `other` from `x` and `y` |
| `operator*=` | Multiply both `x` and `y` by scalar `v` |
| `operator/=` | Divide both `x` and `y` by scalar `v` |

---

### 5. Non-member operators

Implement the following **free functions** as `inline` functions outside the class:

| Signature | Behaviour |
|---|---|
| `operator-(const Position &p)` | Unary negation — return `Position(-p.x, -p.y)` |
| `operator+(const Position &p1, Position p2)` | Element-wise addition |
| `operator-(const Position &p1, Position p2)` | Element-wise subtraction |
| `operator*(const Position &p, value_type v)` | Scale by scalar on the right |
| `operator*(value_type v, const Position &p)` | Scale by scalar on the left |
| `operator/(const Position &p, value_type v)` | Divide by scalar |

> **Hint:** For the binary arithmetic operators, construct a copy and delegate to the corresponding compound assignment operator, e.g.:
> ```cpp
> return Position(p1) += p2;
> ```

---

### 6. Stream output operator

Implement `operator<<` so that a `Position` is printed as `(x,y)`:

```
(3.5,−1.2)
```

The function must return the output stream by reference.

---

## Verification checklist

Before submitting, verify that your implementation satisfies all of the following:

- [ ] `Position p;` compiles and `p.x == 0 && p.y == 0`.
- [ ] `Position p(3.0, 4.0);` gives `p.x == 3.0` and `p.y == 4.0`.
- [ ] `Position p(std::complex<double>(1.0, 2.0));` gives `p.x == 1.0` and `p.y == 2.0`.
- [ ] `p1 + p2`, `p1 - p2`, `p * 2.0`, `2.0 * p`, `p / 2.0` all produce correct results.
- [ ] Unary `-p` negates both components.
- [ ] `std::cout << Position(1, 2)` prints `(1,2)`.

---

## Submission

Submit the completed `position.h` file. Do not add extra headers, change the class layout, or split the implementation into a `.cpp` file — everything must remain in the single header.
