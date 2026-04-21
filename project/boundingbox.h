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
 */
struct ScreenSize {
  unsigned long width;
  unsigned long height;
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

  bool     is_empty;
  Position corner1; // bottom-left: min x, min y
  Position corner2; // top-right:   max x, max y

public:

  /**
   * @brief Default constructor. Creates an empty bounding box.
   */
  constexpr BoundingBox() : is_empty(true) {
  }

  /**
   * @brief Construct a degenerate bounding box from a single position.
   * @param p The single point; both corners are set to this position.
   */
  explicit constexpr BoundingBox(const Position & p) : is_empty(false), corner1(p), corner2(p) {
  }

  /**
   * @brief Construct from two corner positions.
   *
   * Normalise so that corner1 is always the bottom-left (min x, min y)
   * and corner2 is always the top-right (max x, max y), regardless of
   * the order in which p1 and p2 are supplied.
   *
   * @param p1 First corner.
   * @param p2 Second corner (opposite diagonal).
   */
  BoundingBox(const Position & p1, const Position & p2) : is_empty(false), corner1(p1), corner2(p1) {
    *this += p2;
  }

  /**
   * @brief Construct as the bounding box of an initializer_list of positions.
   * @param poslist List of positions to enclose.
   *                An empty list yields an empty bounding box.
   */
  BoundingBox(std::initializer_list<Position> poslist) : is_empty(true) {
    for (auto & pos : poslist) {
      *this += pos;
    }
  }

  /**
   * @brief Construct as the bounding box of a vector of positions.
   * @param poslist Vector of positions to enclose.
   *                An empty vector yields an empty bounding box.
   */
  BoundingBox(const std::vector<Position> & poslist) : is_empty(true) {
    for (auto & pos : poslist) {
      *this += pos;
    }
  }

  /**
   * @brief Check whether the bounding box contains no geometry.
   * @return true if empty, false otherwise.
   */
  bool empty() const {
    return is_empty;
  }

  /**
   * @brief Return the width of the bounding box.
   * @return Absolute difference between the x coordinates of the two corners.
   */
  Position::value_type width() const {
    return std::abs(corner2.x - corner1.x);
  }

  /**
   * @brief Return the height of the bounding box.
   * @return Absolute difference between the y coordinates of the two corners.
   */
  Position::value_type height() const {
    return std::abs(corner2.y - corner1.y);
  }

  /**
   * @brief Return the bottom-left corner (minimum x and y).
   */
  Position bottom_left() const {
    return corner1;
  }

  /**
   * @brief Return the top-right corner (maximum x and y).
   */
  Position top_right() const {
    return corner2;
  }

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
   */
  ScreenSize screenSize(unsigned long resolution) const {
    return ScreenSize{
      static_cast<unsigned long>(std::sqrt(resolution * width() ) / height()),
      static_cast<unsigned long>(std::sqrt(resolution * height()) / width() )
    };
  }

  /**
   * @brief Expand the bounding box to include a single position.
   * @param p Position to include.
   * @return Reference to this object.
   */
  BoundingBox & operator += (const Position & p) {
    if (is_empty) {
      is_empty = false;
      corner1 = corner2 = p;
    }
    else {
      corner1.x = std::min(corner1.x, p.x);
      corner1.y = std::min(corner1.y, p.y);
      corner2.x = std::max(corner2.x, p.x);
      corner2.y = std::max(corner2.y, p.y);
    }
    return *this;
  }

  /**
   * @brief Expand this bounding box to also enclose another bounding box.
   * @param other The other bounding box. Has no effect if other is empty.
   * @return Reference to this object.
   */
  BoundingBox & operator += (const BoundingBox & other) {
    if (is_empty) {
      is_empty = other.is_empty;
      corner1  = other.corner1;
      corner2  = other.corner2;
    }
    else {
      if (!other.is_empty) {
        *this += other.corner1;
        *this += other.corner2;
      }
    }
    return *this;
  }

  /**
   * @brief Scale the bounding box around its center by a scalar factor.
   * @param factor Scaling factor (e.g. 1.05 adds a 5 % margin).
   * @return Reference to this object.
   * TODO: Compute center = (corner1 + corner2) / 2.
   *       Compute half_w = width() * factor / 2 and half_h = height() * factor / 2.
   *       Update corners: corner1 = center - (half_w, half_h),
   *                       corner2 = center + (half_w, half_h).
   */
  BoundingBox & operator *= (double factor) {
    if (!is_empty) {
      auto center = (corner1+corner2)/2;
      auto half_w = width()  * factor/2;
      auto half_h = height() * factor/2;
      corner1     = center - Position(half_w, half_h);
      corner2     = center + Position(half_w, half_h);
    }
    return *this;
  }

};

// -----------------------------------------------------------------------
// Non-member operators  (implement each as an inline free function)
// -----------------------------------------------------------------------

/** @brief Return a new box that also encloses position p.
 */
inline BoundingBox operator + (const BoundingBox & b, const Position & p) {
  return BoundingBox(b)+=p;
}

/** @brief Return a new box that also encloses position p (commutative).
 */
inline BoundingBox operator + (const Position & p, const BoundingBox & b) {
  return BoundingBox(b)+=p;
}

/** @brief Return the union of two bounding boxes.
 */
inline BoundingBox operator + (const BoundingBox & b1, const BoundingBox & b2) {
  return BoundingBox(b1) += b2;
}

/** @brief Return a copy of b scaled by factor around its center.
 */
inline BoundingBox operator * (const BoundingBox & b, const Position::value_type & factor) {
  return BoundingBox(b) *= factor;
}

/** @brief Return a copy of b scaled by factor around its center (commutative).
 */
inline BoundingBox operator * (const Position::value_type & factor, const BoundingBox & b) {
  return BoundingBox(b) *= factor;
}

/**
 * @brief Stream output operator.
 */
inline std::ostream & operator << (std::ostream & os, const BoundingBox & b) {
  if (b.empty()) {
    os << "[]";
  }
  else {
    os << "[" << b.bottom_left() << "," << b.top_right() << "]";
  }
  return os;
}
