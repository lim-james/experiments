#include <iostream>
#include <memory>
#include <utility>

int main() {
    // default init
    std::unique_ptr<int> a(new int(1));
    std::cout << "a: " << a << ": " << *a << '\n';


    // move ownership
    std::unique_ptr<int> b = std::move(a);
    // std::unique_ptr<int> b = a; // compilation error: copy constructor delete
    // std::cout << a << ": " << *a << '\n'; // runtime error: segmentation fault bcos dealloc
    std::cout << "a: " << a << '\n'; // nullptr
    std::cout << "b: " << b << ": " << *b << '\n';


    // transfer ownership
    std::unique_ptr<int> c(b.release());
    std::cout << "b: " << b << '\n';
    std::cout << "c: " << c << ": " << *c << '\n';


    // sizeof
    std::cout << "sizeof unique_ptr " << sizeof(std::unique_ptr<int>) << '\n';


    // swap 
    std::unique_ptr<int> d(new int(2));
    std::cout << "d: " << d << ": " << *d << '\n';
    c.swap(d);
    std::cout << "c: " << c << ": " << *c << '\n';
    std::cout << "d: " << d << ": " << *d << '\n';


    // double release
    a = std::make_unique<int>(1);
    std::cout << "a: " << a << ": " << *a << '\n';


    return 0;
}
