#include <iostream>
#include <memory>
#include <string>

int main() {
    std::cout << "all units are represented in bytes\n";

    std::cout << "=== PRIMITIVES\n";
    std::cout << "char        = " << sizeof(char) << '\n';
    std::cout << "int         = " << sizeof(int) << '\n';
    std::cout << "uint        = " << sizeof(unsigned int) << '\n';
    std::cout << "size_t      = " << sizeof(size_t) << '\n';
    std::cout << "float       = " << sizeof(float) << '\n';
    std::cout << "double      = " << sizeof(double) << '\n';
    std::cout << "long        = " << sizeof(long) << '\n';
    std::cout << "long long   = " << sizeof(long long) << '\n';
    std::cout << "nullptr     = " << sizeof(nullptr) << '\n';

    std::cout << "\n=== PRIMITIVE ARRAYS\n";
    std::cout << "int[1]   = " << sizeof(int[1]) << '\n';
    std::cout << "int[5]   = " << sizeof(int[5]) << '\n';
    std::cout << "int[10]  = " << sizeof(int[10]) << '\n';

    std::cout << "\n=== STRINGS\n";
    std::cout << "std::string = " << sizeof(std::string) << '\n'; // 24 is interesting
    std::cout << "hello world = " << sizeof("hello world") << '\n'; 
    std::cout << "hello world = " << sizeof(std::string("hello world")) << '\n'; 

    std::cout << "\n=== RAW POINTERS\n";
    std::cout << "int*    = " << sizeof(int*) << '\n';
    std::cout << "double* = " << sizeof(double*) << '\n';
    std::cout << "char*   = " << sizeof(char*) << '\n';
    std::cout << "void*   = " << sizeof(void*) << '\n';
    std::cout << "all same, depends on system - 32/64 bit\n";

    std::cout << "\n=== SMART POINTERS\n";
    std::cout << "unique ptr = " << sizeof(std::unique_ptr<int>) << '\n';
    std::cout << "shared ptr = " << sizeof(std::shared_ptr<int>) << '\n';
    // unique ptr = 8 vs  shared_ptr = 16, findings recorded in README
    std::cout << "weak ptr   = " << sizeof(std::weak_ptr<int>) << '\n';


    return 0;
}
