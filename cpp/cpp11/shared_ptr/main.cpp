#include <utility>

#include "shared_pointer.h"

int main() {
    {
        shared_pointer<int> a;
        shared_pointer<int> b{a};
        shared_pointer<int> c{b};
        shared_pointer<int> d{std::move(a)};

        // std::cout << *a << '\n'; // not allowed
    }

    {
        shared_pointer<int> a = make_shared<int>(5);
        shared_pointer<int> b{a};
    }

    return 0;   
}
