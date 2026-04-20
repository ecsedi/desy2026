#include <iostream>

class komplex {

public:

  typedef double value_type;

private:

  value_type re;
  value_type im;

public:

  // default constructor AUTOMATIC
  komplex(/* komplex * this */) : re(0), im(0) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }

  komplex(/* komplex * this, */ value_type re0, value_type im0) : re(re0), im(im0) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }

  // copy constructor AUTOMATIC
  komplex(/* komplex * this, */ const komplex & original) : re(original.re), im(original.im) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }

  // DELETING A CONSTRUCTOR
  // komplex(const komplex & original) = delete;

  // destructor AUTOMATIC
  ~komplex(/* komplex * this */) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }

  // assignment operator AUTOMATIC
  // a = (b = (c = d)); a.operator=(b.operator=(c.operator=(d)));
  komplex & operator = (const komplex & right_side) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
    re = right_side.re;
    im = right_side.im;
    return *this;
  }

  // getter method for the real part
  value_type real(/* const komplex * this */) const {
    return re;
  }

  // getter method for the imaginary part
  value_type imag(/* const komplex * this */) const {
    return im;
  }

  // setter method for the real part
  void real(value_type r) {
    re = r;
  }

  // setter method for the imaginary part
  void imag(value_type i) {
    im = i;
  }
};

komplex operator + (const komplex & left, const komplex & right) {
  return komplex{left.real()+right.real(), left.imag()+right.imag()};
}

// std::cout << z; operator<<(std::cout,z);
std::ostream & operator << (std::ostream & os, const komplex & z) {
  return os << z.real() << " " << z.imag();
}

void f(komplex z) {
  std::cout << __PRETTY_FUNCTION__ << std::endl << &z << std::endl;
}

void g(const komplex & z) {
  std::cout << __PRETTY_FUNCTION__ << std::endl << &z << std::endl;
}

int main() {

  komplex a;
  a.real(1);
  a.imag(2);
  komplex b{10,20};
  komplex d = b;
  std::cout << &a << std::endl;
  std::cout << &b << std::endl;
  std::cout << &d << std::endl;
  f(a);
  g(a);
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
