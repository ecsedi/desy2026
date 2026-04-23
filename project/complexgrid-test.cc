#include "complexgrid.h"
#include "canvas.h"
#include <iostream>

int main() {

  ComplexGrid grid({-2,-2},{2,2},16);
  Canvas      canvas(grid.width(), grid.height());

  std::cout << grid << std::endl;
  std::cout << "--------------------------------" << std::endl;

  for (ComplexGrid::size_type y = 0; y < grid.height(); ++y) {
    std::cout << (y ? "\n" : "");
    for (ComplexGrid::size_type x = 0; x < grid.width(); ++x) {
      std::cout << (x ? " " : "") << grid(x,y);
    }
  }
  std::cout << std::endl;

  return 0;
}
