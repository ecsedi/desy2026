#pragma once

#include "position.h"

#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
#include <stdexcept>
#include <initializer_list>

/**
 * @brief Describes a 2D screen resolution in pixels.
 * TODO: Define two public unsigned long members: `width` and `height`.
 */
struct ScreenSize {
  // TODO
};

/**
 * @brief Axis-aligned bounding box in 2D space.
 *
 * Tracks the minimum and maximum extents of a set of 2D positions.
 * An empty bounding box is valid and represents the absence of any geometry.
 * Supports incremental expansion via operator+=, scaling via operator*=,
 * and conversion to a pixel-based ScreenSize.
 */
class BoundingBox {

private:

  // TODO: Declare three private members:
  //   - a bool     `is_empty`
  //   - a Position `corner1`  (bottom-left: min x, min y)
  //   - a Position `corner2`  (top-right:   max x, max y)

public:

  /**
   * @brief Default constructor. Creates an empty bounding box.
   * TODO: Initialise is_empty to true.
   */
  // TODO

  /**
   * @brief Construct a degenerate bounding box from a single position.
   * @param p The single point; both corners are set to this position.
   * TODO: Set is_empty to false and initialise both corners to p.
   */
  // TODO

  /**
   * @brief Construct from two corner positions.
   *
   * Normalise so that corner1 is always the bottom-left (min x, min y)
   * and corner2 is always the top-right (max x, max y), regardless of
   * the order in which p1 and p2 are supplied.
   *
   * @param p1 First corner.
   * @param p2 Second corner (opposite diagonal).
   * TODO: Set is_empty to false; use std::min / std::max to normalise corners.
   */
  // TODO

  /**
   * @brief Construct as the bounding box of an initializer_list of positions.
   * @param poslist List of positions to enclose.
   *                An empty list yields an empty bounding box.
   * TODO: Initialize is_empty to true. The create a loop and use += to add
   *       positions to this object.
   */
  // TODO

  /**
   * @brief Construct as the bounding box of a vector of positions.
   * @param poslist Vector of positions to enclose.
   *                An empty vector yields an empty bounding box.
   * TODO: Initialize is_empty to true. The create a loop and use += to add
   *       positions to this object.
   */
  // TODO

  /**
   * @brief Check whether the bounding box contains no geometry.
   * @return true if empty, false otherwise.
   * TODO: Return is_empty.
   */
  // TODO

  /**
   * @brief Return the width of the bounding box.
   * @return Absolute difference between the x coordinates of the two corners.
   * TODO: Use std::abs.
   */
  // TODO

  /**
   * @brief Return the height of the bounding box.
   * @return Absolute difference between the y coordinates of the two corners.
   * TODO: Use std::abs.
   */
  // TODO

  /**
   * @brief Return the bottom-left corner (minimum x and y).
   * TODO: Return corner1.
   */
  // TODO

  /**
   * @brief Return the top-right corner (maximum x and y).
   * TODO: Return corner2.
   */
  // TODO

  /**
   * @brief Compute a ScreenSize that preserves the aspect ratio.
   *
   * Use the formulas:
   *   screen_width  = sqrt(resolution * width()  / height())
   *   screen_height = sqrt(resolution * height() / width())
   * Cast both values to unsigned long.
   *
   * @param resolution Desired total pixel count (width x height).
   * @return ScreenSize matching the box's aspect ratio.
   * TODO: Implement using std::sqrt and static_cast.
   */
  // TODO

  /**
   * @brief Expand the bounding box to include a single position.
   * @param p Position to include.
   * @return Reference to this object.
   * TODO: If is_empty, seed both corners from p and clear is_empty.
   *       Otherwise expand corner1/corner2 with std::min / std::max.
   */
  // TODO

  /**
   * @brief Expand this bounding box to also enclose another bounding box.
   * @param other The other bounding box. Has no effect if other is empty.
   * @return Reference to this object.
   * TODO: If this box is empty, copy other's full state.
   *       Otherwise, if other is not empty, expand with std::min / std::max.
   */
  // TODO

  /**
   * @brief Scale the bounding box around its center by a scalar factor.
   * @param factor Scaling factor (e.g. 1.05 adds a 5 % margin).
   * @return Reference to this object.
   * TODO: Compute center = (corner1 + corner2) / 2.
   *       Compute half_w = width() * factor / 2 and half_h = height() * factor / 2.
   *       Update corners: corner1 = center - (half_w, half_h),
   *                       corner2 = center + (half_w, half_h).
   */
  // TODO

};

// -----------------------------------------------------------------------
// Non-member operators  (implement each as an inline free function)
// -----------------------------------------------------------------------

/** @brief Return a new box that also encloses position p.
 *  TODO: Construct a copy of b and delegate to operator+=. */
// TODO: inline BoundingBox operator + (const BoundingBox & b, const Position & p)

/** @brief Return a new box that also encloses position p (commutative).
 *  TODO: Same as above with arguments swapped. */
// TODO: inline BoundingBox operator + (const Position & p, const BoundingBox & b)

/** @brief Return the union of two bounding boxes.
 *  TODO: Construct a copy of b1 and delegate to operator+=. */
// TODO: inline BoundingBox operator + (const BoundingBox & b1, const BoundingBox & b2)

/** @brief Return a copy of b scaled by factor around its center.
 *  TODO: Construct a copy of b and delegate to operator*=. */
// TODO: inline BoundingBox operator * (const BoundingBox & b, const Position::value_type & factor)

/** @brief Return a copy of b scaled by factor around its center (commutative).
 *  TODO: Same as above with arguments swapped. */
// TODO: inline BoundingBox operator * (const Position::value_type & factor, const BoundingBox & b)

/**
 * @brief Stream output operator.
 * TODO: Print "[]" if the box is empty.
 *       Otherwise print "[corner1-corner2]" using bottom_left() and top_right().
 *       Return the stream by reference.
 */
// TODO: inline std::ostream & operator << (std::ostream & os, const BoundingBox & b)
