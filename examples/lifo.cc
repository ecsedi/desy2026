#include <iostream>
#include <algorithm>
#include <stdexcept>

template <typename T>
class LIFO {

public:

  typedef T      value_type;
  typedef size_t size_type;

private:

  size_type   store_size;
  size_type   store_capacity;
  value_type *store;

public:

  LIFO() = delete;

  explicit LIFO(size_type capacity)
  : store_size(0), store_capacity(capacity), store(new value_type [capacity]) {
  }

  LIFO(const LIFO & other)
  :
  store_size(other.store_size),
  store_capacity(other.store_capacity),
  store(new value_type [store_capacity]) {
    //for (size_type i = 0; i < store_size; ++i) {
    //  store[i] = other.store[i];
    //}
    std::copy(other.store, other.store+other.store_size, store);
  }

  ~LIFO() {
    delete [] store;
  }

  LIFO & operator = (const LIFO & other) {
    if (this == &other) {
      return *this;
    }
    if (store_capacity != other.store_capacity) {
      delete [] store;
      store_capacity = other.store_capacity;
      store          = new value_type [store_capacity];
    }
    store_size = other.store_size;
    std::copy(other.store, other.store+other.store_size, store);
    return *this;
  }

  bool empty() const {
    return store_size == 0;
  }

  bool full() const {
    return store_size == store_capacity;
  }

  size_type size() const {
    return store_size;
  }

  size_type capacity() const {
    return store_capacity;
  }

  void push(const value_type & item) {
    if (full()) {
      throw std::runtime_error("Stack full");
    }
    store[store_size] = item;
    ++store_size;
  }

  value_type pop() {
    if (empty()) {
      throw std::runtime_error("Stack empty");
    }
    --store_size;
    return store[store_size];
  }

  const value_type & operator [] (size_type offset) const {
    return store[offset];
  }

  value_type & operator [] (size_type offset) {
    return store[offset];
  }

  value_type at(size_type offset) const {
    if (offset >= store_size) {
      throw std::runtime_error("Index out of limits");
    }
    return store[offset];
  }

  value_type & at(size_type offset) {
    if (offset >= store_size) {
      throw std::runtime_error("Index out of limits");
    }
    return store[offset];
  }
};

int main() {
  LIFO<double> stack(4);
  LIFO<double>::value_type input;
  try {
    while (true) {
      std::cin >> input;
      stack.push(input);
    }
  }
  catch (std::runtime_error & error) {
    std::cerr << "ERROR: " << error.what() << std::endl;
  }
  std::cout << "stack[3]=" << stack[3] << std::endl;
  stack[3] = 333;
  while (!stack.empty()) {
    std::cout << stack.pop() << std::endl;
  }
  return 0;
}
