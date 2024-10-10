#include <iostream>

template <typename T> T add(T a, T b) { return a + b; }

int main() {
  std::cout << "4 + 5 = " << add(4, 5) << '\n';
  return 0;
}
