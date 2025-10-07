#include <compare>

struct Point {
  int x, y;
  auto operator<=>(const Point &) const = default;
};

int main() {
  Point p1{1, 1}, p2{1, 2};

  if (p1 == p2) {
    // valid, p1 == p2
  }

  if (p1 < p2) {
    // valid, p2 > p1
  }

  auto result = p1 <=> p2;
  if (result > 0) {
    // valid p1 > p2
  }

  if (result == std::strong_ordering::less) {
    // vcalid p1 < p2
  }

  return 0;
}
