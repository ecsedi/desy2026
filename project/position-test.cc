#include "position.h"
#include <iostream>

int main() {

  Position p1;
  Position p2(1,2);
  Position p3(Position::complex(3,4));
  Position p4 = (p2+p3)*4/2;
  std::cout << p4 << std::endl;
  return 0;
}
