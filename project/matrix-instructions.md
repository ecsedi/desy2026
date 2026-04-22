# Exercise: Implementing the `Matrix<T>` Class

## Overview

In this exercise you will implement `matrix.h` — a generic, header-only 2D matrix class template stored in **row-major order**. The class supports construction from dimensions, fill values and initializer lists, unchecked and bounds-checked element access, and STL-compatible iterators that allow it to work with range-based `for` loops and standard algorithms.

A skeleton file (`matrix-skeleton.h`) is provided. Every `// TODO` marks code you must write.

---

## Prerequisites

- C++17 or later.
- Familiarity with class templates (`template <typename T>`).

---

## Tasks

### 1. Type aliases

Inside the class, add four `public` type aliases:

| Alias | Underlying type |
|---|---|
| `value_type` | `T` |
| `size_type` | `size_t` |
| `iterator` | `typename std::vector<value_type>::iterator` |
| `const_iterator` | `typename std::vector<value_type>::const_iterator` |

The `typename` keyword is required here because the compiler cannot know at the point of template definition that `::iterator` is a type and not a static member.

---

### 2. Private member variables

Declare three private members:

| Member | Type | Role |
|---|---|---|
| `num_rows` | `size_type` | Number of rows |
| `num_cols` | `size_type` | Number of columns |
| `data` | `std::vector<value_type>` | All elements in row-major order |

The element at logical position `(row, col)` lives at `data[row * num_cols + col]`.

---

### 3. Constructors

Implement **three** `constexpr` constructors (the default constructor is already deleted):

1. **Dimensions only** `(size_type rows, size_type cols)` — initialise `num_rows`, `num_cols`, and `data` with size `rows * cols` (elements are value-initialized).
2. **Fill value** `(size_type rows, size_type cols, const value_type & value)` — same as above but all elements are set to `value`.
3. **Initializer list** `(size_type rows, size_type cols, std::initializer_list<value_type> values)` — initialise `data` directly from `values`, then verify that `data.size() == num_rows * num_cols`; throw `std::invalid_argument("Bad matrix dimensions")` if not.

> **Hint:** Use member-initialiser lists for all three. `std::vector` can be constructed directly from an `initializer_list`.

---

### 4. Accessors

Implement three simple `const` member functions:

| Function | Returns |
|---|---|
| `rows()` | `num_rows` |
| `cols()` | `num_cols` |
| `size()` | `data.size()` |

---

### 5. Element access operators

Implement **two** overloads of `operator()` for unchecked access:

```cpp
value_type &       operator()(size_type row, size_type col);
const value_type & operator()(size_type row, size_type col) const;
```

Both compute the flat index as `row * num_cols + col` and index directly into `data`. No bounds checking is performed.

---

### 6. Bounds-checked access (`at`)

Implement **two** overloads of `at`:

```cpp
value_type &       at(size_type row, size_type col);
const value_type & at(size_type row, size_type col) const;
```

Both must check that `row < num_rows` and `col < num_cols`. If either condition fails, throw:

```cpp
throw std::out_of_range("Matrix index out of bounds");
```

Otherwise return the element using the same flat-index formula.

> **Note:** Because `size_type` is `size_t` (unsigned), a negative index wraps to a very large value and will correctly fail the `>=` check — no special handling is needed.

---

### 7. Iterators

Implement six iterator member functions, all delegating to `data`:

| Function | Delegates to |
|---|---|
| `begin()` (non-const) | `data.begin()` |
| `end()` (non-const) | `data.end()` |
| `begin()` const | `data.begin()` |
| `end()` const | `data.end()` |
| `cbegin()` const | `begin()` |
| `cend()` const | `end()` |

These four functions make `Matrix` compatible with range-based `for` loops and standard algorithms such as `std::fill`, `std::transform`, and `std::copy`.

---

### 8. Stream output operator

Implement a non-member template function:

```cpp
template <typename T>
inline std::ostream & operator<<(std::ostream & os, const Matrix<T> & mat);
```

Print elements in row-major order with the following rules:
- Rows are separated by `"\n"` — print it **before** each row except the first.
- Elements within a row are separated by `" "` — print it **before** each element except the first.
- Access elements via `mat(i, j)`.

Example output for a 2×3 matrix:

```
1 2 3
4 5 6
```

---

### 9. Stream input operator

Implement a non-member template function:

```cpp
template <typename T>
inline std::istream & operator>>(std::istream & is, Matrix<T> & mat);
```

The matrix dimensions are already fixed. Use a range-based `for` loop over `mat` and read each element with `is >> item`. This works because `Matrix` now provides `begin()` and `end()`.

---

## Verification checklist

- [ ] `Matrix<int> m(2, 3);` compiles and all elements are `0`.
- [ ] `Matrix<double> m(2, 2, 1.5);` fills every element with `1.5`.
- [ ] `Matrix<int> m(2, 3, {1,2,3,4,5,6});` stores elements in row-major order.
- [ ] `Matrix<int> m(2, 3, {1,2,3});` throws `std::invalid_argument`.
- [ ] `m.rows()`, `m.cols()`, `m.size()` return the correct values.
- [ ] `m(0, 0) = 42;` modifies the element and `m(0, 0) == 42`.
- [ ] `m.at(0, 0)` returns the same element as `m(0, 0)`.
- [ ] `m.at(99, 0)` throws `std::out_of_range`.
- [ ] A range-based `for` loop over a `Matrix` visits all elements in row-major order.
- [ ] `std::fill(m.begin(), m.end(), 7);` sets all elements to `7`.
- [ ] `std::cout << m` prints rows separated by newlines with space-separated elements.
- [ ] Reading from a `std::istringstream` via `is >> m` fills elements correctly.

---

## Compilation

```bash
g++ -std=c++17 -o matrix-test matrix-test.cc && ./matrix-test
```
