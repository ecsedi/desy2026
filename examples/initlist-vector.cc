#include <iostream>
#include <vector>
#include <initializer_list>

void func(std::initializer_list<int> intlist) {
  for (auto i : intlist) {
    std::cout << i << std::endl;
  }
}

int main() {
  std::vector<int> v;
  v.reserve(100);
  for (int i = 0; i < 10; ++i) {
    std::cout << "Size of v is " << v.size() << std::endl;
    std::cout << "Capacity of v is " << v.capacity() << std::endl;
    v.push_back(i);
  }
  for (std::vector<int>::size_type i = 0; i < v.size(); ++i) {
    std::cout << "v["<< i << "]=" << v[i] << std::endl;
  }
  // range based loop - loop variable is a reference
  for (auto & item : v) {
    item *= 2;
  }
  // range based loop - loop variable is a copy
  for (auto item : v) {
    std::cout << item << std::endl;
  }
  func({ 99, 88, 77, 66, 55, 44, 33, 22, 11 });
  return 0;
}
