// transformation_skeleton.h
#pragma once

#include "matrix.h"
#include "position.h"
#include "boundingbox.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <initializer_list>

class Transformation;
Transformation operator * (const Transformation & t1, const Transformation & t2);

/**
 * @brief Represents a 2D affine transformation as a 3×3 homogeneous matrix.
 *
 * Inherits from Matrix<double> and stores the transformation in row-major
 * homogeneous coordinates. Provides static factory methods for the most
 * common transformations (identity, translation, scaling, rotation, mirroring)
 * as well as a convenience method for mapping world coordinates to screen
 * coordinates.
 *
 * Transformations can be composed with operator*, and applied to a Position
 * via operator*(Transformation, Position).
 */
class Transformation : public Matrix<double> {

private:

  /**
   * @brief Private constructor from an initializer list of 9 matrix elements.
   * @param values Elements in row-major order (must have exactly 9 values).
   */
  Transformation(std::initializer_list<value_type> values)
  : Matrix<double>(3, 3, values) {
  }

public:

  /**
   * @brief Default constructor. Creates the identity transformation.
   */
  Transformation()
  : Transformation(
    {
      1, 0, 0,
      0, 1, 0,
      0, 0, 1
    }
  ) {
  }

  Transformation(const Transformation & ) = default;
  Transformation(      Transformation &&) = default;
 ~Transformation()                        = default;

  Transformation & operator = (const Transformation & ) = default;
  Transformation & operator = (      Transformation &&) = default;

  /**
   * @brief Compose this transformation with another (this = this * other).
   * @param other Transformation to apply after this one.
   * @return Reference to this object.
   */
  Transformation & operator *= (const Transformation & other) {
    Transformation result{0,0,0,0,0,0,0,0,0};
    for (auto i = 0U; i < 3; ++i) {
      for (auto j = 0U; j < 3; ++j) {
        for (auto k = 0U; k < 3; ++k) {
          result(i,j) += operator()(i,k)*other(k,j);
        }
      }
    }
    *this = std::move(result);
    return *this;
  }

  /**
   * @brief Return the identity transformation.
   * @return Identity matrix.
   */
  static Transformation ident() {
    return Transformation{
      1,0,0,
      0,1,0,
      0,0,1
    };
  }

  /**
   * @brief Return a translation transformation.
   * @param p Translation vector.
   * @return Translation matrix.
   */
  static Transformation translate(const Position & p) {
    return Transformation{
      1, 0, p.x,
      0, 1, p.y,
      0, 0, 1
    };
  }

  /**
   * @brief Return a uniform scaling transformation around the origin.
   * @param factor Scale factor applied to both axes.
   * @return Uniform scale matrix.
   */
  static Transformation scale(double factor) {
    return Transformation{
      factor, 0,      0,
      0,      factor, 0,
      0,      0,      1
    };
  }

  /**
   * @brief Return a scaling transformation along the X axis.
   * @param factor Scale factor for the X axis.
   * @return X-axis scale matrix.
   */
  static Transformation scale_x(double factor) {
    return Transformation{
      factor, 0, 0,
      0,      1, 0,
      0,      0, 1
    };
  }

  /**
   * @brief Return a scaling transformation along the Y axis.
   * @param factor Scale factor for the Y axis.
   * @return Y-axis scale matrix.
   */
  static Transformation scale_y(double factor) {
    return Transformation{
      1, 0,      0,
      0, factor, 0,
      0, 0,      1
    };
  }

  /**
   * @brief Return a reflection about the X axis (negates Y coordinates).
   * @return Mirror-X matrix.
   */
  static Transformation mirror_x() {
    return scale_y(-1);
  }

  /**
   * @brief Return a reflection about the Y axis (negates X coordinates).
   * @return Mirror-Y matrix.
   */
  static Transformation mirror_y() {
    return scale_x(-1);
  }

  /**
   * @brief Return a counter-clockwise rotation around the origin.
   * @param angle Rotation angle in radians.
   * @return Rotation matrix.
   */
  static Transformation rotate(double angle) {
    return Transformation{
      cos(angle), -sin(angle), 0,
      sin(angle),  cos(angle), 0,
      0,           0,          1
    };
  }

  /**
   * @brief Return a transformation that maps a bounding box to screen coordinates.
   *
   * Translates the top-left corner of @p bbox to the origin, flips the Y axis
   * (so that Y grows downward as on screen), and scales uniformly so that the
   * geometry fits within the given pixel dimensions while preserving aspect ratio.
   *
   * @param bbox   World-space bounding box of the geometry.
   * @param width  Target screen width in pixels.
   * @param height Target screen height in pixels.
   * @return Composite world-to-screen transformation.
   */
  static Transformation toScreen(const BoundingBox & bbox, double width, double height) {
    // Compute top_left, scalex, scaley, scale = min(scalex, scaley),
    // then return the composition: scale_x(scale) * scale_y(-scale) * translate(-top_left)
    // (the operator* will be implemented below)
    Position top_left{bbox.bottom_left().x, bbox.top_right().y};
    double sclx = static_cast<double>(width ) / bbox.width ();
    double scly = static_cast<double>(height) / bbox.height();
    auto   scl  = std::min(sclx, scly);
    return scale_x(scl) * scale_y(-scl) * translate(-top_left);
    // or:
    // return mirror_x() * scale(scl) * translate(-top_left);
  }
};

/**
 * @brief Compose two transformations (matrix multiplication).
 * @param t1 Left-hand transformation.
 * @param t2 Right-hand transformation.
 * @return Combined transformation equivalent to applying t2 then t1.
 */
inline Transformation operator * (const Transformation & t1, const Transformation & t2) {
  return Transformation(t1) *= t2;
}

/**
 * @brief Apply a transformation to a position using homogeneous coordinates.
 * @param t Transformation matrix.
 * @param p Input position.
 * @return Transformed position.
 */
inline Position operator * (const Transformation & t, const Position & p) {
  auto scale = t(2,0)*p.x + t(2,1)*p.y + t(2,2)*1;
  return Position{
    (t(0,0)*p.x + t(0,1)*p.y + t(0,2)*1) / scale,
    (t(1,0)*p.x + t(1,1)*p.y + t(1,2)*1) / scale
  };
}
