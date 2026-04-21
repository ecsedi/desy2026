#include "rgb.h"
#include <iostream>

int main() {
  RGB color1; // default constructor test
  RGB color2(11,22,33);
  RGB color3 = color2; // copy constructor test
  std::cin >> color1; // stream input test
  std::cout << color1 << std::endl; // stream output test
  return 0;
}
