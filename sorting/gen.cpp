#include <iostream>
#include <time.h>

int main() {

    int n = 0;
    do {
        std::cout << "n: ";
        std::cin >> n;
    } while (n <= 0);

    int lo = 0;
    std::cout << "min (incl): ";
    std::cin >> lo;

    int hi = 0;
    do {
        std::cout << "max (excl): ";
        std::cin >> hi;
    } while (hi <= lo);

    srand(time(NULL));

    std::cout << n << std::endl;
    int dt = hi - lo;
    while (n-- > 0) std::cout << rand() % dt + lo << " ";

    std::cout << std::endl;

    return 0;
}
