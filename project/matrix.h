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

  typedef T value_type;
  typedef size_t size_type;
  typedef  typename std::vector<value_type>::iterator iterator;
  typedef  typename std::vector<value_type>::const_iterator const_iterator;

private:

  size_type num_rows;
  size_type num_cols;
  std::vector<value_type> data;

public:

  // The default constructor is explicitly disabled — a Matrix must always
  // have dimensions. Do not remove this line.
  Matrix() = delete;

  /**
   * @brief Construct a matrix of given dimensions with default-initialized elements.
   * @param rows Number of rows.
   * @param cols Number of columns.
   */
  constexpr Matrix(size_type rows, size_type cols) : num_rows(rows), num_cols(cols), data(num_rows*num_cols) {
  }

  /**
   * @brief Construct a matrix filled with a constant value.
   * @param rows  Number of rows.
   * @param cols  Number of columns.
   * @param value Fill value for all elements.
   */
  constexpr Matrix(size_type rows, size_type cols, const value_type & value)
  : num_rows(rows), num_cols(cols), data(num_rows*num_cols, value) {
  }

  /**
   * @brief Construct from an initializer list of elements in row-major order.
   * @param rows   Number of rows.
   * @param cols   Number of columns.
   * @param values Elements in row-major order; count must equal rows * cols.
   * @throw std::invalid_argument if the number of values does not match rows * cols.
   */
  Matrix(size_type rows, size_type cols, std::initializer_list<value_type> values) :
  num_rows(rows), num_cols(cols), data(values) {
    if (data.size() != num_rows*num_cols) {
      throw std::invalid_argument("Bad matrix dimensions");
    }
  }

  // Copy/move/destructor — keep these defaulted, do not implement them manually.
  Matrix(const Matrix &) = default;
  Matrix(Matrix &&) = default;
  ~Matrix() = default;
  Matrix & operator = (const Matrix &) = default;
  Matrix & operator = (Matrix &&) = default;

  /**
   * @brief Return the number of rows.
   */
  size_type rows() const {
    return num_rows;
  }

  /**
   * @brief Return the number of columns.
   */
  size_type cols() const {
    return num_cols;
  }

  /**
   * @brief Return the total number of elements (rows * cols).
   */
  size_type size() const {
    return num_rows * num_cols;
  }

  /**
   * @brief Non-const element access without bounds checking.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at (row, col).
   * TODO: Compute the flat index as row * num_cols + col and return data[index].
   */
  value_type & operator () (size_type row, size_type col) {
    return data[row * num_cols + col];
  }

  /**
   * @brief Const element access without bounds checking.
   * @param row Row index.
   * @param col Column index.
   * @return Const reference to the element at (row, col).
   */
  const value_type & operator () (size_type row, size_type col) const {
    return data[row * num_cols + col];
  }

  /**
   * @brief Bounds-checked non-const element access.
   * @param row Row index.
   * @param col Column index.
   * @return Reference to the element at (row, col).
   * @throw std::out_of_range if row >= num_rows or col >= num_cols.
   */
  value_type & at(size_type row, size_type col) {
    if (row >= num_rows || col >= num_cols) {
      throw std::out_of_range("Invalid index");
    }
    return data[row * num_cols + col];
  }

  /**
   * @brief Bounds-checked const element access.
   * @param row Row index.
   * @param col Column index.
   * @return Const reference to the element at (row, col).
   * @throw std::out_of_range if row >= num_rows or col >= num_cols.
   */
  const value_type & at(size_type row, size_type col) const {
    if (row >= num_rows || col >= num_cols) {
      throw std::out_of_range("Invalid index");
    }
    return data[row * num_cols + col];
  }

  /** @brief Return a mutable iterator to the first element.
   */
  iterator begin() {
    return data.begin();
  }

  /** @brief Return a mutable iterator past the last element.
   */
  iterator end() {
    return data.end();
  }

  /** @brief Return a const iterator to the first element.
   */
  const_iterator begin() const {
    return data.begin();
  }

  /** @brief Return a const iterator past the last element.
   */
  const_iterator end() const {
    return data.end();
  }

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
template <typename T>
inline std::ostream & operator << (std::ostream & os, const Matrix<T> & mat) {
  for (typename Matrix<T>::size_type r = 0; r < mat.rows(); ++r) {
    os << (r ? "\n" : "");
    for (typename Matrix<T>::size_type c = 0; c < mat.cols(); ++c) {
      os << (c ? " " : "") << mat(r,c);
    }
  }
  return os;
}

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
 */
template <typename T>
inline std::istream & operator >> (std::istream & is, Matrix<T> & mat) {
  for (auto & item : mat) {
    is >> item;
  }
  return is;
}
