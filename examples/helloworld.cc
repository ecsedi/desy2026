#include <iostream>

struct mystruct {
  int    a;
  double b;
};

int add(int left_side, int right_side) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  int result = left_side + right_side;
  return result;
}

double add(double left_side, double right_side) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  double result = left_side + right_side;
  return result;
}

mystruct add(mystruct left_side, mystruct right_side) {
  std::cout << __PRETTY_FUNCTION__ << std::endl;
  mystruct result;
  result.a = add(left_side.a, right_side.a);
  result.b = add(left_side.b, right_side.b);
  return result;
}

mystruct operator + (mystruct left_side, mystruct right_side) {
  mystruct result;
  result.a = left_side.a + right_side.a;
  result.b = left_side.b + right_side.b;
  return result;
}

mystruct operator + (mystruct left_side, int right_side) {
  mystruct result;
  result.a = left_side.a + right_side;
  return result;
}

mystruct x;
mystruct y;

int main() {
  std::cout << "Hello World!" << std::endl;
  x.a = 1;
  x.b = 2;
  y.a = 10;
  y.b = 20;
  //x + y;
  mystruct z = add(x,y);
  //x + y + z;
  //add(add(x,y),z);
  int x;
  
  return 0;
}
