#include "line.h"
#include "dot.h"

int main() {
  Canvas canvas(800, 400, RGB::white);
  Dot  dot1({400,   0}, RGB::yellow , 100);
  Dot  dot2({400, 400}, RGB::magenta, 100);
  Line line1({100,100}, {700,100}, RGB::red,   80);
  Line line2({100,200}, {700,200}, RGB::green, 80);
  Line line3({100,300}, {700,300}, RGB::blue,  80);
  canvas << dot1 << dot2 << line1 << line2 << line3;
  std::cout << canvas;
  return 0;
}
