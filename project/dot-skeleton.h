#pragma once

#include "line.h"
#include "position.h"
#include "drawable.h"
#include "boundingbox.h"
#include "transformation.h"

/**
 * @brief A filled circular dot drawable.
 *
 * Renders as a zero-length Line segment with the given diameter, which
 * produces a disk of the specified size centered at @c pos.
 */
class Dot : public Drawable {

public:

  /** @brief Color type (alias for the canvas pixel type, RGB). */
  typedef Canvas::value_type color_type;

  Position   pos;    ///< Center position of the dot.
  color_type color;  ///< Dot color.
  double     size;   ///< Dot diameter in canvas units.

  /** @brief Default constructor. */
  Dot() = default;

  /**
   * @brief Construct a dot at a given position.
   * @param position  Center position.
   * @param dot_color Dot color (default black).
   * @param diameter  Dot diameter in canvas units (default 1).
   */
  Dot(
    const Position   & position,
    const color_type & dot_color = color_type(0,0,0),
    double             diameter  = 1
  );

  virtual ~Dot() override = default;

  /**
   * @brief Draw the dot as a degenerate (zero-length) line segment.
   * @param canvas Target canvas.
   * @return Reference to @p canvas.
   *
   * @todo Implement: construct a Line from pos to pos with color and size,
   *       call its draw(), and return the result.
   */
  virtual Canvas & draw(Canvas & canvas) const override;

  /**
   * @brief Apply a transformation to the dot's center position.
   * @param t Transformation to apply.
   * @return Reference to this dot.
   *
   * @todo Implement: apply t to pos, return *this.
   */
  virtual Dot & transform(const Transformation & t) override;

  /**
   * @brief Compute the bounding box of this dot.
   *
   * Returns a box of side @c size centered on @c pos.
   *
   * @return Bounding box.
   *
   * @todo Implement: return BoundingBox with corners at pos ± size/2.
   */
  virtual BoundingBox boundingBox() const override;

  /**
   * @brief Create a heap-allocated copy of this dot.
   * @return Pointer to a new Dot (caller takes ownership).
   *
   * @todo Implement: return new Dot(*this).
   */
  virtual Dot * copy() const override;
};
