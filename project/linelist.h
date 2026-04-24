#pragma once

#include "canvas.h"
#include "line.h"
#include "transformation.h"

#include <vector>
#include <algorithm>
#include <vector>
#include <initializer_list>

/**
 * @brief An ordered, owning collection of Drawable objects.
 *
 * LineList is a vector of Line objects.
 *
 * LineList itself satisfies the Drawable interface.
 */
class LineList : public Drawable, public std::vector<Line> {

public:

  typedef std::vector<Line>::value_type value_type;
  typedef std::vector<Line>::size_type  size_type;

public:

  /** @brief Default constructor. Creates an empty list. */
  LineList() = default;

  /**
   * @brief Construct a list containing a single copy of @p item.
   * @param item Initial element.
   */
  explicit LineList(const Line & item) : std::vector<Line>(1, item) {
  }

  LineList(const LineList & ) = default;
  LineList(      LineList &&) = default;

  virtual ~LineList() override = default;

  LineList & operator = (const LineList & ) = default;
  LineList & operator = (      LineList &&) = default;

  /**
   * @brief Apply a transformation to every element in the list.
   * @param t Transformation to apply.
   * @return Reference to this list.
   */
  virtual LineList & transform(const Transformation & t) override {
    for (auto & item : *this) {
      item.transform(t);
    }
    return *this;
  }

  /**
   * @brief Draw all elements onto @p canvas in order.
   * @param canvas Target canvas.
   * @return Reference to @p canvas.
   */
  virtual Canvas & draw(Canvas & canvas) const override {
    for (auto & item : *this) {
      item.draw(canvas);
    }
    return canvas;
  }

  /**
   * @brief Compute the bounding box that encloses all elements.
   * @return Union of all element bounding boxes.
   */
  virtual BoundingBox boundingBox() const override {
    BoundingBox bbox;
    for (auto & item : *this) {
      bbox += item.boundingBox();
    }
    return bbox;
  }

  /**
   * @brief Create a heap-allocated deep copy of this list.
   * @return Pointer to a new LineList (caller takes ownership).
   */
  virtual LineList * copy() const override {
    return new LineList(*this);
  }

  LineList & operator += (const Line & l) {
    push_back(l);
    return *this;
  }

  LineList & operator += (const LineList & ll) {
    insert(end(), ll.begin(), ll.end());
    return *this;
  }
};

inline LineList operator + (const LineList & ll1, const LineList & ll2) {
  return LineList(ll1) += ll2;
}

inline LineList operator + (const LineList & ll, const Line & l) {
  return LineList(ll) += l;
}

inline LineList operator + (const Line & l, const LineList & ll) {
  return LineList(ll) += l;
}
