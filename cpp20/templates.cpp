#include <iostream>

template <typename T> T add(T a, T b) { return a + b; }

template <typename T> void println(T a) { std::cout << a << '\n'; }
template <typename T, typename... args> void println(T a, args... b) {
  println(a);
  println(b...);
}

int main() {
  println(3);
  println(4, 5, 6, 7);
  std::cout << "4 + 5 = " << add(4, 5) << '\n';
  return 0;
}
