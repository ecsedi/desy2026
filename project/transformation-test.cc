#include "position.h"
#include "boundingbox.h"
#include "transformation.h"
#include "canvas.h"
#include <iostream>

int main() {
  Canvas         canvas(800, 600);
  Position       p1(  0,  0);
  Position       p2(800,600);
  BoundingBox    bbox(p1, p2);
  Transformation toScreen = Transformation::toScreen(bbox, canvas.width(), canvas.height());
  std::cout << toScreen << std::endl;

  /* Should produce:
   *   1  0   0
   *   0 -1 600
   *   0  0   1
   */

  return 0;
}
