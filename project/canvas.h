#pragma once

#include "rgb.h"
//#include "utils.h"
#include "matrix.h"
#include "position.h"

#include <cctype>
#include <limits>
#include <string>
#include <vector>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <iterator>
#include <stdexcept>

/**
 * @brief A 2D pixel canvas backed by a Matrix of RGB colors.
 *
 * Wraps Matrix<RGB> and adds coordinate-space pixel access (x, y) as well
 * as PPM file I/O.  Pixel (0,0) is the top-left of the canvas; x grows
 * right, y grows down, matching the screen/image convention used in PPM
 * files and most raster graphics contexts.
 *
 * Out-of-bounds writes through operator() and operator[] are silently
 * discarded (written to an offscreen pixel sink).  Use at() when you want
 * a bounds-checking throw instead.
 */
class Canvas : public Matrix<RGB> {

public:

  /** @brief Coordinate type for x and y pixel positions. */
  typedef Position::value_type   coord_type;

  /** @brief Type of a single RGB color channel value. */
  typedef value_type::value_type rgb_component;

private:

  rgb_component      rgb_max;         ///< Maximum possible value of an RGB color component.
  mutable value_type offscreen_pixel; ///< Sink for out-of-bounds writes.

  /**
   * @brief Check whether (x, y) lies within the canvas.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @return true if the pixel is on-screen.
   */
  bool onscreen(coord_type x, coord_type y) const {
    return (x >= 0 && x < width() && y >= 0 && y < height());
  }

  /**
   * @brief Check whether a Position lies within the canvas.
   * @param pos Position to check.
   * @return true if the pixel is on-screen.
   */
  bool onscreen(const Position & pos) const {
    return onscreen(static_cast<coord_type>(pos.x), static_cast<coord_type>(pos.y));
  }

public:

  Canvas() = delete;

  /**
   * @brief Construct a blank canvas of the given size.
   * @param canvas_width      Width in pixels.
   * @param canvas_height     Height in pixels.
   * @param max_rgb_component Maximum RGB channel value (default 255).
   */
  Canvas(
    size_type     canvas_width,
    size_type     canvas_height,
    rgb_component max_rgb_component = 255
  )
  : Matrix<RGB>(canvas_height, canvas_width), rgb_max(max_rgb_component) {
    // Nothing extra needed — base class and member initialisation handles everything.
  }

  /**
   * @brief Construct a canvas filled with a solid background color.
   * @param canvas_width      Width in pixels.
   * @param canvas_height     Height in pixels.
   * @param color             Fill color for all pixels.
   * @param max_rgb_component Maximum RGB channel value (default 255).
   */
  Canvas(
    size_type canvas_width,
    size_type canvas_height,
    const value_type & color,
    rgb_component max_rgb_component = 255
  )
  : Matrix<RGB>(canvas_height, canvas_width, color), rgb_max(max_rgb_component) {
    // Nothing extra needed.
  }

  Canvas(const Canvas & ) = delete;
  Canvas(      Canvas &&) = default;
 ~Canvas(               ) = default;
  Canvas & operator = (const Canvas & ) = delete;
  Canvas & operator = (      Canvas &&) = default;

  /**
   * @brief Return the canvas width in pixels.
   * @return Number of pixel columns.
   */
  coord_type width() const {
    return static_cast<coord_type>(cols());
  }

  /**
   * @brief Return the canvas height in pixels.
   * @return Number of pixel rows.
   */
  coord_type height() const {
    return static_cast<coord_type>(rows());
  }

  /**
   * @brief Return the current maximum RGB channel value.
   * @return Maximum component value (e.g. 255).
   */
  rgb_component maximum_rgb_component() const {
    return rgb_max;
  }

  /**
   * @brief Rescale all pixel values to a new maximum RGB channel value.
   *
   * All existing pixel values are multiplied by (new_max+1)/(old_max+1).
   *
   * @param max_rgb_component New maximum channel value.
   */
  void maximum_rgb_component(rgb_component max_rgb_component) {
    // TODO:
    //   1. If the new maximum equals rgb_max, do nothing.
    //   2. Otherwise compute the scale factor:
    //        scale = (max_rgb_component + 1) / (rgb_max + 1)   (use double arithmetic)
    //   3. Multiply every pixel in *this by scale_factor.
    //   4. Update rgb_max.
  }

  /**
   * @brief Non-const pixel access by (x, y) coordinates.
   *
   * Out-of-bounds coordinates write to a silent sink pixel.
   *
   * @param x X coordinate (column).
   * @param y Y coordinate (row, 0 = bottom).
   * @return Reference to the pixel.
   */
  value_type & operator() (coord_type x, coord_type y) {
    // TODO:
    //   If (x, y) is onscreen, forward to the base-class operator() with
    //   (row = y, col = x) after casting to size_type.
    //   The matrix is stored row-major with row 0 at the top, and canvas
    //   y = 0 is also the top row, so the mapping is direct — no flipping needed.
    //   Otherwise return offscreen_pixel.
    return onscreen(x,y) ? Matrix<RGB>::operator()(y,x) : offscreen_pixel;
  }

  /**
   * @brief Const pixel access by (x, y) coordinates.
   *
   * Out-of-bounds coordinates return the offscreen sink pixel.
   *
   * @param x X coordinate (column).
   * @param y Y coordinate (row, 0 = bottom).
   * @return Const reference to the pixel.
   */
  const value_type & operator() (coord_type x, coord_type y) const {
    return onscreen(x,y) ? Matrix<RGB>::operator()(y,x) : offscreen_pixel;
  }

  /**
   * @brief Non-const pixel access by Position.
   * @param pos Pixel position.
   * @return Reference to the pixel.
   */
  value_type & operator [] (const Position & pos) {
    return operator()(pos.x, pos.y);
  }

  /**
   * @brief Const pixel access by Position.
   * @param pos Pixel position.
   * @return Const reference to the pixel.
   */
  const value_type & operator [] (const Position & pos) const {
    return operator()(pos.x, pos.y);
  }

  /**
   * @brief Bounds-checked non-const pixel access.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @return Reference to the pixel.
   * @throw std::out_of_range if the coordinates are outside the canvas.
   */
  value_type & at(coord_type x, coord_type y) {
    if (!onscreen(x, y)) {
      throw std::out_of_range("Coordinates out of bounds");
    }
    return operator()(x,y);
  }

  /**
   * @brief Bounds-checked const pixel access.
   * @param x X coordinate.
   * @param y Y coordinate.
   * @return Const reference to the pixel.
   * @throw std::out_of_range if the coordinates are outside the canvas.
   */
  const value_type & at(coord_type x, coord_type y) const {
    if (!onscreen(x, y)) {
      throw std::out_of_range("Coordinates out of bounds");
    }
    return operator()(x,y);
  }

  /**
   * @brief Bounds-checked non-const pixel access by Position.
   * @param pos Pixel position.
   * @return Reference to the pixel.
   * @throw std::out_of_range if the position is outside the canvas.
   */
  value_type & at(const Position & pos) {
    if (!onscreen(pos)) {
      throw std::out_of_range("Coordinates out of bounds");
    }
    return operator[](pos);
  }

  /**
   * @brief Bounds-checked const pixel access by Position.
   * @param pos Pixel position.
   * @return Const reference to the pixel.
   * @throw std::out_of_range if the position is outside the canvas.
   */
  const value_type & at(const Position & pos) const {
    if (!onscreen(pos)) {
      throw std::out_of_range("Coordinates out of bounds");
    }
    return operator[](pos);
  }

  /**
   * @brief Load a PPM (P3) image from a stream.
   *
   * The stream must begin with "P3" followed by at least one whitespace
   * character.  Comments (lines starting with '#') are skipped when reading
   * the header fields.  On success the canvas is replaced with the loaded
   * image.  On failure the stream failbit is set and the canvas is left
   * unchanged.
   *
   * @param is Input stream.
   * @return Reference to @p is.
   */
  std::istream & load(std::istream & is) {

    // TODO — implement in the following order:
    //
    // Step 1: Read the two-character magic number.
    //   Use is.get() twice to read magic1 and magic2.
    //   If the stream fails, return is immediately.
    //   If magic1 != 'P' or magic2 != '3', set failbit and return.
    //
    // Step 2: Enforce at least one whitespace character after the magic.
    //   Peek at the next character; if it is not whitespace, set failbit
    //   and return.
    //
    // Step 3: Read the header fields w (width), h (height), m (max component).
    //   Use the skipComments manipulator before each field:
    //     is >> skipComments >> w >> skipComments >> h >> skipComments >> m;
    //   (skipComments is declared in utils.h and skips '#'-prefixed lines.)
    //   If the stream fails after reading, return is.
    //   If any of w, h, m are <= 0, set failbit and return.
    //
    // Step 4: Construct a temporary Canvas(w, h, m) called newcanvas.
    //
    // Step 5: Read pixel data into newcanvas:
    //     is >> dynamic_cast<Matrix<RGB> &>(newcanvas);
    //
    // Step 6: If the stream is still good, move-assign newcanvas into *this.
    //
    // Return is.

    std::string magic;
    int w, h, m;
    is >> magic >> w >> h >> m;
    if (!is) {
      return is;
    }
    Canvas newcanvas(w,h,m);
    is >> dynamic_cast<Matrix<RGB>&>(newcanvas);
    if (is) {
      *this = std::move(newcanvas);
    }
    return is;
  }

  /**
   * @brief Load a PPM (P3) image from a file.
   *
   * Pass "-" to read from standard input.
   *
   * @param filename Path to the PPM file, or "-" for stdin.
   * @throw std::runtime_error if the file cannot be opened or the data is invalid.
   */
  void load(const std::string & filename) {
    if (filename == "-") {
      load(std::cin);
    }
    else {
      std::ifstream infile(filename);
      if (!infile) {
        throw std::runtime_error("Failed to open input file " + filename);
      }
      load(infile);
    }
  }

  /**
   * @brief Write the canvas to a stream in PPM P3 format.
   *
   * Output format:
   *   Line 1: "P3"
   *   Line 2: "<width> <height>"
   *   Line 3: "<max_rgb_component>"
   *   Remaining: pixel data via Matrix<RGB> stream operator
   *   Trailing newline after pixel data.
   *
   * @param os Output stream.
   * @return Reference to @p os.
   */
  std::ostream & save(std::ostream & os) const {
    os
    << "P3\n"
    << width() << " " << height() << "\n"
    << maximum_rgb_component() << "\n"
    << dynamic_cast<const Matrix<RGB> &>(*this) << "\n";
    return os;
  }

  /**
   * @brief Save the canvas to a file in PPM P3 format.
   *
   * Pass "-" to write to standard output.
   *
   * @param filename Path to the output file, or "-" for stdout.
   * @throw std::runtime_error if the file cannot be opened or the write fails.
   */
  void save(const std::string & filename) const {
    if (filename == "-") {
      save(std::cout);
    }
    else {
      std::ofstream outfile(filename);
      if (!outfile) {
        throw std::runtime_error("Failed to open output file " + filename);
      }
      save(outfile);
    }
  }
};

/**
 * @brief Stream output operator: saves canvas as a PPM P3 image.
 * @param os     Output stream.
 * @param canvas Canvas to save.
 * @return Reference to @p os.
 */
inline std::ostream & operator << (std::ostream & os, const Canvas & canvas) {
  return canvas.save(os);
}

/**
 * @brief Stream input operator: loads a PPM P3 image into a canvas.
 * @param is     Input stream.
 * @param canvas Canvas to load into.
 * @return Reference to @p is.
 */
inline std::istream & operator >> (std::istream & is, Canvas & canvas) {
  return canvas.load(is);
}
