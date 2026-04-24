#include "linelist.h"
#include <numbers> // C++ 20 feature, needed for pi

constexpr double DEG = std::numbers::pi / 180.0;

LineList koch;

void grow(const Line & line, int depth) {

  if (depth < 1) {
    koch += line;
    return;
  }

  double third = 1.0/3.0;

  // Translate the starting point of the segment to the origin:
  Transformation t1 = Transformation::translate(-line.from);

  // Translate back to the starting point of the segment:
  Transformation t2 = Transformation::translate( line.from);

  // Shrink:
  Transformation s1 = Transformation::scale(third);

  // First line segment:
  line1 = s1 * t1 * line;

  // Translate by third of the original segment length:
  Transformation t3 = Transformation::translate((line.to-line.from)*third);

  // Rotate 60 degrees anti-clockwise:
  Transformation r1 = Transformation::rotate(60*DEG);

  line2 = t3 * r1 * s1 * t1 * line;

  // Rotate 60 degrees clockwise:
  Transformation r2 = Transformation::rotate(-60*DEG);
  // Translate:
  Transformation t4 = Transformation::translate(line2.to);

  line3 = t4 * r2 * s1 * t1 * line;

  Transformation t5 = Transformation::translate(lin3.to);
  line4 = t5 * s1 * t1 * line;

  grow(t2*line1, depth-1);
  grow(t2*line2, depth-1);
  grow(t2*line3, depth-1);
  grow(t2*line4, depth-1);
}

int main() {
  grow(Line({0,0}, {0,1}, RGB::black, 2));
  auto bbox        = koch.boundingBox() * 1.05;
  auto screen_size = bbox.screenSize(1000000);
  Canvas canvas(screen_size.width, screen_size.height, RGB::white);
  auto ts = Transformation::toScreen(bbox, canvas.width(), canvas.height());
  canvas << ts * koch;
  std::cout << canvas;
  return 0;
}
