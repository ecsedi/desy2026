#pragma once

#include <vector>
#include <complex>
#include <iostream>
#include <algorithm>

/**
 * @brief A regular 2D grid of complex numbers covering a rectangular region.
 *
 * The grid spans a rectangular region in the complex plane defined by two
 * corner values.  Given a target resolution (total node count), the grid
 * dimensions are chosen to preserve the aspect ratio of the region.  Nodes
 * are stored in row-major order from top-left to bottom-right (i.e. the
 * imaginary component decreases as the row index increases).
 *
 * Typical use: pre-computing the complex sample points for a Mandelbrot or
 * Julia set renderer.
 */
class ComplexGrid {

public:

  /** @brief Size / index type. */
  typedef size_t                               size_type;

  /** @brief Complex number type used for grid nodes. */
  typedef std::complex<double>                 complex;

  /** @brief Const iterator over grid nodes in row-major order. */
  typedef std::vector<complex>::const_iterator const_iterator;

private:

  complex              bl;    ///< Bottom-left corner of the region.
  complex              tr;    ///< Top-right corner of the region.
  unsigned long        res;   ///< Requested resolution (approximate total node count).
  size_type            w;     ///< Actual grid width (columns).
  size_type            h;     ///< Actual grid height (rows).
  std::vector<complex> nodes; ///< Grid nodes in row-major order (top-left first).

public:

  ComplexGrid() = delete;

  /**
   * @brief Construct a grid over a complex rectangle.
   *
   * The two corner arguments may be given in any order; the constructor
   * normalises them so that @c bl holds the minimum real and imaginary parts
   * and @c tr holds the maximum.  Grid dimensions are calculated to match the
   * aspect ratio while keeping the total node count close to @p resolution.
   *
   * Nodes are filled row by row from the top-left corner, with the real part
   * increasing and the imaginary part decreasing.
   *
   * @param corner1    One corner of the complex rectangular region.
   * @param corner2    The opposite corner.
   * @param resolution Approximate desired total number of grid nodes.
   */
  ComplexGrid(
    const complex & corner1,
    const complex & corner2,
    unsigned long   resolution
  ) :

  // TODO — member initialiser list:
  //
  // bl: complex whose real part is min(corner1.real(), corner2.real())
  //     and imaginary part is min(corner1.imag(), corner2.imag()).
  //     Use std::min for both components.
  //
  // tr: complex whose real part is max(corner1.real(), corner2.real())
  //     and imaginary part is max(corner1.imag(), corner2.imag()).
  //     Use std::max for both components.
  //
  // res: store resolution directly.
  //
  // w: number of columns, computed to preserve aspect ratio:
  //      w = sqrt( resolution * (tr.real()-bl.real()) / (tr.imag()-bl.imag()) )
  //    Cast the result to size_type.
  //
  // h: number of rows, computed symmetrically:
  //      h = sqrt( resolution * (tr.imag()-bl.imag()) / (tr.real()-bl.real()) )
  //    Cast the result to size_type.
  //
  // nodes: a std::vector<complex> of size w*h (default-initialised).

  bl(complex{}),   // placeholder
  tr(complex{}),   // placeholder
  res(0),          // placeholder
  w(0),            // placeholder
  h(0),            // placeholder
  nodes()          // placeholder

  {
    // TODO — fill the nodes vector:
    //
    // The grid is filled row by row, starting from the TOP-LEFT corner.
    // The top-left complex value has:
    //   real part = bl.real()
    //   imag part = tr.imag()       <-- note: tr, not bl
    //
    // Step sizes:
    //   dx = (tr.real() - bl.real()) / w    (real part increases left → right)
    //   dy = (tr.imag() - bl.imag()) / h    (imag part decreases top → bottom)
    //
    // For each row y (0 .. h-1), for each column x (0 .. w-1):
    //   nodes[w*y + x] = current complex value
    //   then advance current.real() by +dx
    // After finishing a row:
    //   reset current.real() back to bl.real()
    //   decrease current.imag() by dy
    //
    // Use a single linear counter n (starting at 0) to index into nodes,
    // incrementing it after each node is stored.
  }

  ComplexGrid(const ComplexGrid &) = delete;
  ComplexGrid(ComplexGrid &&) = default;
  ComplexGrid & operator = (const ComplexGrid &) = delete;
  ComplexGrid & operator = (ComplexGrid &&) = default;

  /**
   * @brief Return the grid width (number of columns).
   * @return Column count.
   */
  size_type width() const {
    // TODO: return w
    return 0; // placeholder
  }

  /**
   * @brief Return the grid height (number of rows).
   * @return Row count.
   */
  size_type height() const {
    // TODO: return h
    return 0; // placeholder
  }

  /**
   * @brief Return the bottom-left corner of the covered region.
   * @return Bottom-left complex value.
   */
  complex bottom_left() const {
    // TODO: return bl
    return complex{}; // placeholder
  }

  /**
   * @brief Return the top-right corner of the covered region.
   * @return Top-right complex value.
   */
  complex top_right() const {
    // TODO: return tr
    return complex{}; // placeholder
  }

  /**
   * @brief Return the requested resolution.
   * @return Approximate total node count passed to the constructor.
   */
  unsigned long resolution() const {
    // TODO: return res
    return 0; // placeholder
  }

  /**
   * @brief Return the total number of grid nodes.
   * @return width() * height(), i.e. nodes.size().
   */
  size_type size() const {
    // TODO: return nodes.size()
    return 0; // placeholder
  }

  /**
   * @brief Access a node by (column, row) index.
   * @param x Column index (0-based).
   * @param y Row index (0-based, 0 = top row).
   * @return Const reference to the complex node value.
   */
  const complex & operator() (size_type x, size_type y) const {
    // TODO: nodes are stored in row-major order; return nodes[w*y + x]
    static complex dummy{};
    return dummy; // placeholder
  }

  /**
   * @brief Access a node by linear index in row-major order.
   * @param n Linear index (0-based).
   * @return Const reference to the complex node value.
   */
  const complex & operator [] (size_type n) const {
    // TODO: return nodes[n]
    static complex dummy{};
    return dummy; // placeholder
  }

  /**
   * @brief Return a const iterator to the first node.
   * @return Begin iterator.
   */
  const_iterator begin() const {
    // TODO: return nodes.begin()
    return nodes.begin(); // placeholder (nodes is empty, so this won't crash)
  }

  /**
   * @brief Return a const iterator past the last node.
   * @return End iterator.
   */
  const_iterator end() const {
    // TODO: return nodes.end()
    return nodes.end(); // placeholder
  }
};

/**
 * @brief Stream output operator for ComplexGrid.
 *
 * Prints all nodes in row-major order, space-separated within each row,
 * with rows separated by newlines.
 *
 * @param os   Output stream.
 * @param grid Grid to print.
 * @return Reference to @p os.
 */
inline std::ostream & operator << (std::ostream & os, const ComplexGrid & grid) {

  // TODO:
  //   Iterate n from 0 to grid.size()-1.
  //   Compute x = n % grid.width().
  //   If n > 0 and x == 0, output "\n" (new row).
  //   If x > 0, output " " (space between nodes in the same row).
  //   Output grid[n].

  return os;
}

//#endif
