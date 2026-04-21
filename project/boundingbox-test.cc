#include "boundingbox.h"
#include <iostream>

int main() {
  BoundingBox bb{{0,0},{1,1},{0,1},{1,0}};
  for (int i = 0; i < 10; ++i) {
    std::cout << bb << std::endl;
    if (i%2) {
      bb += Position(i,i);
    }
    else {
      bb += Position(-i,-i);
    }
  }
  return 0;
}
