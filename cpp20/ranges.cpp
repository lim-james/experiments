#include <iostream>
#include <ranges>

int main() {
  auto is_odd = [](int n) { return n & 1; };
  auto square = [](int n) { return n * n; };

  // views - lightweight, non-owning (lazy)
  for (int i : std::views::iota(1, 10) | std::views::filter(is_odd) |
                   std::views::transform(square) | std::views::reverse)
    std::cout << i << ' ';

  std::cout << std::endl;

  return 0;
}
