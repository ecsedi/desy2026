#include <iostream>

class Base {
private:
  int base_data;
public:
  Base() : base_data(1) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual ~Base() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  void method_1() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  void method_2() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual void method_3() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual void method_4() = 0; // abstract method
};

class Derived : public Base {
private:
  int derived_data;
public:
  Derived() : derived_data(2) {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual ~Derived() override {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  void method_2() {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual void method_3() override {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
  virtual void method_4() override {
    std::cout << __PRETTY_FUNCTION__ << " " << this << std::endl;
  }
};

void func(Base & param) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  param.method_1();
  param.method_2();
  param.method_3();
  param.method_4();
  std::cout << __PRETTY_FUNCTION__ << std::endl;
}

int main() {
  /*
  Derived derived_object;
  derived_object.method_1();
  derived_object.method_2();
  derived_object.method_3();
  derived_object.method_4();
  func(derived_object);
  */
  Base * ptr = new Derived;
  delete ptr;
  return 0;
}
