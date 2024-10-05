#include <concepts>
#include <iostream>
#include <string>
#include <vector>

template <typename T>
concept Integral = std::is_integral<T>::value;
template <typename T>
concept SignedIntegral = Integral<T> && std::is_signed<T>::value;
template <typename T>
concept UnsignedIntegral = Integral<T> && !SignedIntegral<T>;

template <typename T>
concept String = std::is_same<T, std::string>::value;

template <typename T>
concept Addable = Integral<T> || String<T>;

template <typename T>
concept Iterable = requires(T t) {
  { t.begin() } -> std::input_iterator;
  { t.end() } -> std::input_iterator;
};

template <Addable T> T add(T a, T b) { return a + b; }
template <SignedIntegral T> T negate(T a) { return -a; }
template <UnsignedIntegral T> T mul2(T a) { return a << 1; }

template <Iterable T> void printAll(T container) {
  for (const auto &item : container) {
    std::cout << item << " ";
  }
  std::cout << std::endl;
}

int main() {
  std::cout << add(3, 4) << std::endl;
  std::cout << negate(10) << std::endl;
  std::cout << mul2((unsigned)3) << std::endl;

  std::string a = "Jam";
  std::string b = "es";
  std::cout << add(a, b) << std::endl;

  std::vector<int> v;
  for (int i = 0; i < 5; ++i)
    v.push_back(i);
  printAll(v);

  return 0;
}
