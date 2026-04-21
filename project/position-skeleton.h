#pragma once

#include <complex>
#include <iostream>

/**
 * @brief Represents a 2D position (or vector) in Cartesian coordinates.
 */
class Position {

public:

  // TODO: Define a public type alias `value_type` for double.

  // TODO: Define a public type alias `complex` for std::complex<value_type>.

  // TODO: Declare two public member variables: `x` and `y`, both of type value_type.

  /**
   * @brief Default constructor.
   * TODO: Initialize x and y to 0 using a constexpr constructor.
   */
  // TODO

  /**
   * @brief Construct from explicit x and y coordinates.
   * @param pos_x X coordinate.
   * @param pos_y Y coordinate.
   * TODO: Write a constexpr constructor that accepts pos_x and pos_y and
   *       initializes x and y accordingly.
   */
  // TODO

  /**
   * @brief Construct from a complex number (real → x, imag → y).
   * @param pos Complex number.
   * TODO: Write a constexpr constructor that accepts a const reference to
   *       a complex number and initializes x from its real part and y from
   *       its imaginary part.
   */
  // TODO

  /**
   * @brief Compound addition operator (+=).
   * TODO: Implement operator+= so that it adds the x and y components of
   *       `other` to this object's x and y, then returns *this by reference.
   */
  // TODO

  /**
   * @brief Compound subtraction operator (-=).
   * TODO: Implement operator-= analogously to operator+=.
   */
  // TODO

  /**
   * @brief Compound scalar multiplication operator (*=).
   * @param v Scalar multiplier.
   * TODO: Implement operator*= so that it scales both x and y by v,
   *       then returns *this by reference.
   */
  // TODO

  /**
   * @brief Compound scalar division operator (/=).
   * @param v Scalar divisor.
   * TODO: Implement operator/= analogously to operator*=.
   */
  // TODO

};

// -----------------------------------------------------------------------
// Non-member operators  (implement each as an inline free function)
// -----------------------------------------------------------------------

/** @brief Unary negation.
 * TODO: Return a new Position whose x and y are the negation of p's. */
// TODO

/** @brief Binary addition.
 * TODO: Return the element-wise sum of p1 and p2.
 *       Hint: construct a copy of p1 and reuse operator+=. */
// TODO

/** @brief Binary subtraction.
 * TODO: Return the element-wise difference of p1 and p2. */
// TODO

/** @brief Scale position by scalar (position * scalar).
 * TODO: Return a scaled copy of p. */
// TODO

/** @brief Scale position by scalar (scalar * position).
 * TODO: Ensure commutativity — scalar on the left should work too. */
// TODO

/** @brief Divide position by scalar.
 * TODO: Return a divided copy of p. */
// TODO

/**
 * @brief Stream output operator.
 * TODO: Print the position as "(x,y)" to the output stream os and return os.
 */
// TODO
