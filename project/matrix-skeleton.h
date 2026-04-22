#pragma once

#include <vector>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <stdexcept>

/**
 * @brief Generic 2D matrix stored in row-major order.
 *
 * Provides element access by (row, col) index with both checked (at()) and
 * unchecked (operator()) variants, as well as forward iterators over all
 * elements in row-major order.
 *
 * @tparam T Element type. Must be default-constructible.
 */
template <typename T>
class Matrix {

public:

  // TODO: Define three public type aliases:
  //   - `value_type`    for T
  //   - `size_type`     for size_t
  //   - `iterator`      for the mutable iterator of std::vector<value_type>
  //                     (hint: typename std::vector<value_type>::iterator)
  //   - `const_iterator` for the immutable iterator of std::vector<value_type>

private:

  // TODO: Declare three private member variables:
  //   - `num_rows` of type size_type
  //   - `num_cols` of type size_type
  //   - `data`     of type std::vector<value_type>  (stores elements in row-major order)

public:

  // The default constructor is explicitly disabled — a Matrix must always
  // have dimensions. Do not remove this line.
  Matrix() = delete;

  /**
   * @brief Construct a matrix of given dimensions with default-initialized elements.
   * @param rows Number of rows.
   * @param cols Number of columns.
   * TODO: Initialise num_rows, num_cols, and data (size = rows * cols).
   */
  // TODO

  /**
   * @brief Construct a matrix filled with a constant value.
   * @param rows  Number of rows.
   * @param cols  Number of columns.
   * @param value Fill value for all elements.
   * TODO: Initialise num_rows, num_cols, and data (all elements equal to value).
   */
  // TODO

  /**
   * @brief Construct from an initializer list of elements in row-major order.
   * @param rows   Number of rows.
   * @param cols   Number of columns.
   * @param values Elements in row-major order; count must equal rows * cols.
   * @throw std::invalid_argument if the number of values does not match rows * cols.
   * TODO: Initialise num_rows, num_cols, and data from `values`.
   *       After construction, check that data.size() == num_rows * num_cols and
   *       throw std::invalid_argument("Bad matrix dimensions") if not.
   */
  // TODO

  // Copy/move/destructor — keep these defaulted, do not implement them manually.
  Matrix(const Matrix &) = default;
  Matrix(Matrix &&) = default;
  ~Matrix() = default;
  Matrix & operator = (const Matrix &) = default;
  Matrix & operator = (Matrix &&) = default;

  /**
   * @brief Return the number of rows.
   * TODO: Return num_rows.
   */
  // TODO

  /**
   * @brief Return the number of columns.
   * TODO: Return num_cols.
   */
  // TODO

  /**
   * @brief Return the total number of elements (rows * cols).
   * TODO: Delegate to data.size().
   */
  // TODO

  /**
   * @brief Non-const element access without bounds checking.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at (row, col).
   * TODO: Compute the flat index as row * num_cols + col and return data[index].
   */
  // TODO

  /**
   * @brief Const element access without bounds checking.
   * @param row Row index.
   * @param col Column index.
   * @return Const reference to the element at (row, col).
   * TODO: Same formula as the non-const version above.
   */
  // TODO

  /**
   * @brief Bounds-checked non-const element access.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at (row, col).
   * @throw std::out_of_range if row >= num_rows or col >= num_cols.
   * TODO: Check bounds first, then return data[row * num_cols + col].
   *       Throw std::out_of_range("Matrix index out of bounds") on failure.
   */
  // TODO

  /**
   * @brief Bounds-checked const element access.
   * @param row Row index.
   * @param col Column index.
   * @return Const reference to the element at (row, col).
   * @throw std::out_of_range if row >= num_rows or col >= num_cols.
   * TODO: Identical logic to the non-const at(), but const-qualified.
   */
  // TODO

  /** @brief Return a mutable iterator to the first element.
   *  TODO: Delegate to data.begin(). */
  // TODO

  /** @brief Return a mutable iterator past the last element.
   *  TODO: Delegate to data.end(). */
  // TODO

  /** @brief Return a const iterator to the first element.
   *  TODO: Delegate to data.begin() (const overload). */
  // TODO

  /** @brief Return a const iterator past the last element.
   *  TODO: Delegate to data.end() (const overload). */
  // TODO

  /** @brief Return a const iterator to the first element (explicit const version).
   *  TODO: Delegate to begin(). */
  // TODO

  /** @brief Return a const iterator past the last element (explicit const version).
   *  TODO: Delegate to end(). */
  // TODO

};

// -----------------------------------------------------------------------
// Non-member stream operators  (implement as inline template functions)
// -----------------------------------------------------------------------

/**
 * @brief Stream output operator for Matrix.
 *
 * Print elements in row-major order: elements on the same row separated by
 * spaces, rows separated by newlines.  Example for a 2x3 matrix:
 *   1 2 3
 *   4 5 6
 *
 * @tparam T Element type.
 * @param os  Output stream.
 * @param mat Matrix to print.
 * @return Reference to output stream.
 *
 * TODO: Use two nested loops over mat.rows() and mat.cols().
 *       Print a newline before each row except the first (if (i) os << "\n").
 *       Print a space before each element except the first in a row (if (j) os << " ").
 *       Access elements via mat(i, j).
 */
// TODO: template <typename T>
// TODO: inline std::ostream & operator << (std::ostream & os, const Matrix<T> & mat)

/**
 * @brief Stream input operator for Matrix.
 *
 * Read elements in row-major order into an already-sized matrix.
 * The matrix dimensions must already be set; simply fill the existing storage
 * without resizing.
 *
 * @tparam T Element type.
 * @param is  Input stream.
 * @param mat Matrix to fill.
 * @return Reference to input stream.
 *
 * TODO: Use a range-based for loop over mat (relies on begin()/end())
 *       and read each element with is >> item.
 */
// TODO: template <typename T>
// TODO: inline std::istream & operator >> (std::istream & is, Matrix<T> & mat)
