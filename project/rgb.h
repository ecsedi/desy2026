#pragma once

#include <cmath>
#include <string>
#include <iostream>

/**
 * @brief Represents a color in RGB color space.
 *
 * Stores red, green, and blue components as 16-bit unsigned integers.
 * Be careful though, because predefined colors use only 8 bits (0-255)!
 * The extra bits are needed to support PPM format input/output.
 * Supports construction from numeric values, hexadecimal strings,
 * and predefined named colors.
 */
class RGB {

public:

  /** @brief Underlying channel type (unsigned 16-bit integer). */
  typedef unsigned short value_type;

  /** @brief Red channel value (0–255). */
  value_type r;

  /** @brief Green channel value (0–255). */
  value_type g;

  /** @brief Blue channel value (0–255). */
  value_type b;

  /** @brief Predefined black color (0,0,0). */
  static const RGB black;

  /** @brief Predefined white color (255,255,255). */
  static const RGB white;

  /** @brief Predefined red color (255,0,0). */
  static const RGB red;

  /** @brief Predefined green color (0,255,0). */
  static const RGB green;

  /** @brief Predefined blue color (0,0,255). */
  static const RGB blue;

  /** @brief Predefined yellow color (255,255,0). */
  static const RGB yellow;

  /** @brief Predefined cyan color (0,255,255). */
  static const RGB cyan;

  /** @brief Predefined magenta color (255,0,255). */
  static const RGB magenta;

  /**
   * @brief Default constructor.
   *
   * Initializes the color to black (0,0,0).
   */
  constexpr RGB() : r(0), g(0), b(0) {
  }

  /**
   * @brief Construct from explicit RGB channel values.
   *
   * @param red   Red component (0–255)
   * @param green Green component (0–255)
   * @param blue  Blue component (0–255)
   */
  constexpr RGB(
    const value_type & red,
    const value_type & green,
    const value_type & blue
  ) : r(red), g(green), b(blue) {
  }

  /**
   * @brief Set RGB channel values explicitly.
   *
   * @param red   Red component (0–255)
   * @param green Green component (0–255)
   * @param blue  Blue component (0–255)
   * @return Reference to this object.
   */
  constexpr RGB & set(
    const value_type & red,
    const value_type & green,
    const value_type & blue
  ) {
    r = red;
    g = green;
    b = blue;
    return *this;
  }

  /**
   * @brief Factory method to convert HSV values to an RGB color.
   *
   * @param h       Hue (0–360°).
   * @param s       Saturation (0-1).
   * @param v       Value (0-1).
   * @param maxcomp Optional maximum color component value (default 255).
   * @return The created RGB color.
   *
   * Hints:
   *  - Compute the HSV sector index i = floor(h/60) % 6 and the
   *    fractional offset f = h/60 - floor(h/60).
   *  - Derive the intermediate values p, q, and t from v and s.
   *  - Use a switch on i (cases 0-5) to assign r, g, b.
   */  // RGB color = RGB::from_hsv(h, s, v);
  static RGB from_hsv(double h, double s, double v) {
    
    double r, g, b;
    int    i = static_cast<int>(h / 60.0) % 6;
    double f = (h / 60.0) - std::floor(h / 60.0);
    double p = v * (1.0 -             s);
    double q = v * (1.0 -        f  * s);
    double t = v * (1.0 - (1.0 - f) * s);

    switch (i) {
      case 0:  r = v; g = t; b = p; break;
      case 1:  r = q; g = v; b = p; break;
      case 2:  r = p; g = v; b = t; break;
      case 3:  r = p; g = q; b = v; break;
      case 4:  r = t; g = p; b = v; break;
      case 5:  r = v; g = p; b = q; break;
      default: r = 0; g = 0; b = 0; break;
    }

    return RGB{
      static_cast<value_type>(r * 255),
      static_cast<value_type>(g * 255),
      static_cast<value_type>(b * 255)
    };
  }

  /**
   * @brief Multiply color intensity by a factor.
   *
   * @param factor Scaling factor.
   * @return Reference to this object.
   *
   * TODO: Implement this method.
   */
  RGB & operator *= (double factor) {

    r *= factor;
    g *= factor;
    b *= factor;

    return *this;
  }

  /**
   * @brief Divide color intensity by a factor.
   *
   * @param factor Divisor.
   * @return Reference to this object.
   *
   * TODO: Implement this method.
   */
  RGB & operator /= (double factor) {

    r /= factor;
    g /= factor;
    b /= factor;

    return *this;
  }

  /**
   * @brief Fade current color toward another color.
   *
   * @param target_color Target color.
   * @param speed        Fade speed (0-1). Throws if outside this range.
   * @return Reference to this object.
   *
   * TODO: Implement this method.
   *
   * Hints:
   *  - Validate that speed is in [0, 1]; throw std::invalid_argument otherwise.
   *  - For each channel: new_value = current + speed * (target - current).
   *  - Cast the result to value_type.
   */
  RGB & fade(const RGB & target_color, double speed) {

    // TODO: implement this method.

    return *this;
  }

}; // end of class RGB

/**
 * @brief Stream insertion operator.
 * Color components separated by spaces.
 * std::cout << c;   operator<<(std::cout, c)
 */
inline std::ostream & operator << (std::ostream & os, const RGB & color) {
  return os << color.r << " " << color.g << " " << color.b;
}

/**
 * @brief Stream extraction operator.
 */
inline std::istream & operator >> (std::istream & is, RGB & color) {
  RGB::value_type red, green, blue;
  is >> red >> green >> blue;
  if (is) {
    color.set(red, green, blue);
  }
  return is;
}

/** @brief Equality comparison operator. */
inline bool operator == (const RGB & left, const RGB & right) {
  return left.r == right.r && left.g == right.g && left.b == right.b;
}

/** @brief Inequality comparison operator. */
inline bool operator != (const RGB & left, const RGB & right) {
  return left.r != right.r || left.g != right.g || left.b != right.b;
}

/** @brief Multiply color by scalar. */
inline RGB operator * (const RGB & color, double factor) {
  RGB result(color);
  result *= factor;
  return result;
}

/** @brief Multiply scalar by color. */
inline RGB operator * (double factor, const RGB & color) {
  return RGB(color) *= factor;
}

/** @brief Divide color by scalar. */
inline RGB operator / (const RGB & color, double factor) {
  return RGB(color) /= factor;
}

const RGB RGB::black(0,0,0);
const RGB RGB::white(255, 255, 255);
const RGB RGB::red(255,0,0);
const RGB RGB::green(0,255,0);
const RGB RGB::blue(0,0,255);
const RGB RGB::yellow(255,255,0);
const RGB RGB::cyan(0,255,255);
const RGB RGB::magenta(255,0,255);
