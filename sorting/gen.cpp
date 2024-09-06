#include <iostream>
#include <time.h>
#include <cstdlib>

void print(int n, int lo, int hi) {
    srand(time(NULL));

    std::cout << n << std::endl;
    int dt = hi - lo;
    while (n-- > 0) std::cout << rand() % dt + lo << " ";

    std::cout << std::endl;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        for (int i = 1; i < argc; ++i) {
            int n = atoi(argv[i]);
            print(n, 0, n);
        }
        return 0;
    }

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

    print(n, lo, hi);

    return 0;
}
