#include <iostream>

template <typename T>
class komplex {

public:

  typedef T value_type;

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

typedef komplex<int> myKomplex;

template <typename T>
komplex<T> operator + (const komplex<T> & left, const komplex<T> & right) {
  return komplex<T>{left.real()+right.real(), left.imag()+right.imag()};
}

// std::cout << z; operator<<(std::cout,z);
template <typename T>
std::ostream & operator << (std::ostream & os, const komplex<T> & z) {
  return os << z.real() << " " << z.imag();
}

template <typename T>
void f(komplex<T> z) {
  std::cout << __PRETTY_FUNCTION__ << std::endl << &z << std::endl;
}

template <typename T>
void g(const komplex<T> & z) {
  std::cout << __PRETTY_FUNCTION__ << std::endl << &z << std::endl;
}

int main() {

  myKomplex a;
  a.real(1);
  a.imag(2);
  myKomplex b{10,20};
  myKomplex d = b;
  std::cout << &a << std::endl;
  std::cout << &b << std::endl;
  std::cout << &d << std::endl;
  f(a);
  g(a);
  d = a;

  myKomplex c = a+b;
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
