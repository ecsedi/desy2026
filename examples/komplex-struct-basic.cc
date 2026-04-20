#include <iostream>

struct komplex {
  double re;
  double im;
};

komplex operator + (komplex left, komplex right) {
  return komplex{left.re+right.re, left.im+right.im};
}

// std::cout << z; operator<<(std::cout,z);
std::ostream & operator << (std::ostream & os, komplex z) {
  return os << z.re << " " << z.im;
}

int main() {

  komplex a;
  a.re = 1;
  a.im = 2;
  komplex b{10,20};
  komplex d = b;

  std::cout << &a << std::endl;
  std::cout << &b << std::endl;
  std::cout << &d << std::endl;

  d = a;

  komplex c = a+b;
  std::cout << a << " + " << b << " = " << c << std::endl;

  //std::cout
  //<< a.re << " " << a.im
  //<< " + "
  //<< b.re << " " << b.im
  //<< " = "
  //<< c.re << " " << c.im
  //<< std::endl;

  return 0;
}
