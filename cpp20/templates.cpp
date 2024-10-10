#include <concepts>
#include <iostream>
#include <ostream>

template <typename T>
concept Addable = requires(T a, T b) {
  { a + b } -> std::convertible_to<T>;
};
template <typename T>
concept Printable = requires(T a) {
  { std::cout << a } -> std::convertible_to<std::ostream &>;
};

template <Addable T> T add(T a, T b) { return a + b; }

template <Printable T> void println(T a) { std::cout << a << '\n'; }
template <Printable T, Printable... args> void println(T a, args... b) {
  println(a);
  println(b...);
}

int main() {
  println(3);
  println(4, 5, 6, 7);
  std::cout << "4 + 5 = " << add(4, 5) << '\n';
  return 0;
}
