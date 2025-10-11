#include <iostream>

int main() {
    std::cout << "=== Basic construction/destruction\n";
    {
        unique_ptr<int> p1(new int);
        assert(p1);
        std::cout << "p1 : " << *p1;
    }
    std::cout << "=== Exited scope\n\n";
}
