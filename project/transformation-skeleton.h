// transformation_skeleton.h
#pragma once

#include "matrix.h"
#include "position.h"
#include "boundingbox.h"

#include <cmath>
#include <iostream>
#include <algorithm>
#include <initializer_list>

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
  constexpr Transformation(std::initializer_list<value_type> values)
  : Matrix<double>(3, 3, values) {
  }

public:

  /**
   * @brief Default constructor. Creates the identity transformation.
   */
  constexpr Transformation()
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
    // TODO: Implement matrix multiplication here.
    // You must create a temporary 3x3 result matrix filled with zeros,
    // perform the triple loop multiplication, then move the result into *this.
  }

  /**
   * @brief Return the identity transformation.
   * @return Identity matrix.
   */
  static Transformation ident() {
    // TODO: Implement (you may call the default constructor or use the private constructor)
  }

  /**
   * @brief Return a translation transformation.
   * @param p Translation vector.
   * @return Translation matrix.
   */
  static Transformation translate(const Position & p) {
    // TODO: Implement using the private constructor with the correct 9 values
  }

  /**
   * @brief Return a uniform scaling transformation around the origin.
   * @param factor Scale factor applied to both axes.
   * @return Uniform scale matrix.
   */
  static Transformation scale(double factor) {
    // TODO: Implement using the private constructor
  }

  /**
   * @brief Return a scaling transformation along the X axis.
   * @param factor Scale factor for the X axis.
   * @return X-axis scale matrix.
   */
  static Transformation scale_x(double factor) {
    // TODO: Implement using the private constructor
  }

  /**
   * @brief Return a scaling transformation along the Y axis.
   * @param factor Scale factor for the Y axis.
   * @return Y-axis scale matrix.
   */
  static Transformation scale_y(double factor) {
    // TODO: Implement using the private constructor
  }

  /**
   * @brief Return a reflection about the X axis (negates Y coordinates).
   * @return Mirror-X matrix.
   */
  static Transformation mirror_x() {
    // TODO: Implement (you may call scale_y(-1) once scale_y is done, or hard-code)
  }

  /**
   * @brief Return a reflection about the Y axis (negates X coordinates).
   * @return Mirror-Y matrix.
   */
  static Transformation mirror_y() {
    // TODO: Implement (you may call scale_x(-1) once scale_x is done, or hard-code)
  }

  /**
   * @brief Return a counter-clockwise rotation around the origin.
   * @param angle Rotation angle in radians.
   * @return Rotation matrix.
   */
  static Transformation rotate(double angle) {
    // TODO: Implement using cos(angle) and sin(angle) with the private constructor
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
    // TODO: Implement exactly as described in the comment above.
    // Compute top_left, scale_x, scale_y, scale = min(scale_x, scale_y),
    // then return the composition: scale_x(scale) * scale_y(-scale) * translate(-top_left)
    // (the operator* will be implemented below)
  }
};

/**
 * @brief Compose two transformations (matrix multiplication).
 * @param t1 Left-hand transformation.
 * @param t2 Right-hand transformation.
 * @return Combined transformation equivalent to applying t2 then t1.
 */
inline Transformation operator * (const Transformation & t1, const Transformation & t2) {
  // TODO: Implement using the *= operator (or any other correct method)
}

/**
 * @brief Apply a transformation to a position using homogeneous coordinates.
 * @param t Transformation matrix.
 * @param p Input position.
 * @return Transformed position.
 */
inline Position operator * (const Transformation & t, const Position & p) {
  // TODO: Implement homogeneous multiplication and divide by the homogeneous coordinate
}
