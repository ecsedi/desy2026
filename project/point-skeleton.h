#pragma once

#include "canvas.h"
#include "drawable.h"
#include "position.h"
#include "boundingbox.h"
#include "transformation.h"

/**
 * @brief A single-pixel point drawable.
 *
 * Sets exactly one pixel on the canvas at the given position.
 * Unlike Dot, no diameter is involved — the point always occupies exactly
 * one pixel regardless of scale.
 */
class Point : public Drawable {

public:

  /** @brief Color type (alias for the canvas pixel type, RGB). */
  typedef Canvas::value_type color_type;

  Position   pos;    ///< Pixel position of the point.
  color_type color;  ///< Point color.

  /** @brief Default constructor. */
  Point() = default;

  /**
   * @brief Construct a point at the given position.
   * @param position    Pixel position.
   * @param point_color Color (default black).
   */
  constexpr Point(
    const Position   & position,
    const color_type & point_color = color_type(0,0,0)
  );

  Point(const Point & ) = default;
  Point(      Point &&) = default;

  virtual ~Point() override = default;

  Point & operator = (const Point &) = default;

  /**
   * @brief Set the single pixel at @c pos to @c color.
   * @param canvas Target canvas.
   * @return Reference to @p canvas.
   *
   * @todo Implement: set canvas[pos] = color and return canvas.
   */
  virtual Canvas & draw(Canvas & canvas) const override;

  /**
   * @brief Apply a transformation to the point's position.
   * @param t Transformation to apply.
   * @return Reference to this point.
   *
   * @todo Implement: apply t to pos, return *this.
   */
  virtual Point & transform(const Transformation & t) override;

  /**
   * @brief Compute the bounding box of this point.
   *
   * Returns a 1×1 box (half a unit in each direction) centered on @c pos.
   *
   * @return Bounding box.
   *
   * @todo Implement: return a BoundingBox of ±0.5 around pos.
   */
  virtual BoundingBox boundingBox() const override;

  /**
   * @brief Create a heap-allocated copy of this point.
   * @return Pointer to a new Point (caller takes ownership).
   *
   * @todo Implement: return new Point(*this).
   */
  virtual Point * copy() const override;
};
