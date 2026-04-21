#pragma once

#include <complex>
#include <iostream>

/**
 * @brief Represents a 2D position (or vector) in Cartesian coordinates.
 */
class Position {

public:

  typedef double value_type;
  typedef std::complex<value_type> complex;

  value_type x;
  value_type y;

  /**
   * @brief Default constructor.
   */
  constexpr Position() : x(0), y(0) {
  }

  /**
   * @brief Construct from explicit x and y coordinates.
   * @param pos_x X coordinate.
   * @param pos_y Y coordinate.
   */
  constexpr Position(value_type x0, value_type y0) : x(x0), y(y0) {
  }

  /**
   * @brief Construct from a complex number (real → x, imag → y).
   * @param pos Complex number.
   */
  constexpr Position(const complex & z) : x(z.real()), y(z.imag()) {
  }

  /**
   * @brief Compound addition operator (+=).
   */
  Position & operator += (const Position & other) {
    x += other.x;
    y += other.y;
    return *this;
  }

  /**
   * @brief Compound subtraction operator (-=).
   */
  Position & operator -= (const Position & other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }

  /**
   * @brief Compound scalar multiplication operator (*=).
   * @param v Scalar multiplier.
   */
  Position & operator *= (const Position::value_type & scale) {
    x *= scale;
    y *= scale;
    return *this;
  }

  /**
   * @brief Compound scalar division operator (/=).
   * @param v Scalar divisor.
   */
  Position & operator /= (const Position::value_type & scale) {
    x /= scale;
    y /= scale;
    return *this;
  }
};

// -----------------------------------------------------------------------
// Non-member operators  (implement each as an inline free function)
// -----------------------------------------------------------------------

/** @brief Unary negation.
 * Return a new Position whose x and y are the negation of p's. */
inline Position operator - (const Position & p) {
  return Position(p) *= -1;
}

/** @brief Binary addition.
 * Return the element-wise sum of p1 and p2.
 */
inline Position operator + (const Position & p1, const Position & p2) {
  return Position(p1)+=p2;
}

/** @brief Binary subtraction.
 * Return the element-wise difference of p1 and p2. */
inline Position operator - (const Position & p1, const Position & p2) {
  return Position(p1)-=p2;
}

/** @brief Scale position by scalar (position * scalar).
 * Return a scaled copy of p. */
inline Position operator * (const Position & p, const Position::value_type & scale) {
  return Position(p)*=scale;
}

/** @brief Scale position by scalar (scalar * position).
 * Ensure commutativity — scalar on the left should work too. */
inline Position operator * (const Position::value_type & scale, const Position & p) {
  return Position(p)*=scale;
}

/** @brief Divide position by scalar.
 * Return a divided copy of p. */
inline Position operator / (const Position & p, const Position::value_type & s) {
  return Position(p)/=s;
}

/**
 * @brief Stream output operator.
 * Print the position as "(x,y)" to the output stream os and return os.
 */
inline std::ostream & operator << (std::ostream & os, const Position & p) {
  return os << "(" << p.x << "," << p.y << ")";
}
