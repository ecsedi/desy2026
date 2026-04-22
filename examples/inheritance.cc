#include <iostream>

class Base {
private:
  int base_i1;
  int base_i2;
public:
  Base() : base_i1(1), base_i2(2) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Base(int i1, int i2) : base_i1(i1), base_i2(i2) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Base(const Base & other) : base_i1(other.base_i1), base_i2(other.base_i2) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  ~Base() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Base & operator = (const Base & other) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
    base_i1 = other.base_i1;
    base_i2 = other.base_i2;
    return *this;
  }
  void func() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
};

class Derived : public Base {
public:
  Derived() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Derived(int i1, int i2) : Base(i1, i2) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Derived(const Derived & other) : Base(other) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  ~Derived() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  Derived & operator = (const Derived & other) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
    return *this;
  }
  void func() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
    Base::func();
  }
};

int main() {
  Derived d1;
  Derived d2(11,22);
  d1.func();
  return 0;
}
