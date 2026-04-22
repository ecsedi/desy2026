#include "matrix.h"
#include <iostream>

int main() {
  Matrix<double> m1(3,4,5.0);
  std::cout << m1.rows() << " x " << m1.cols() << "\n" << m1 << std::endl;
  try {
    Matrix<double> m2(3,4,{1,2,3,4});
  }
  catch (std::invalid_argument & error) {
    std::cerr << error.what() << std::endl;
  }
  return 0;
}
