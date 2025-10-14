#include <iostream>
#include <string>
#include <memory>
#include <utility>

int main() {
    {
        std::string a = "hello";

        // just curious i'd imagine its similar to vector
        // 24 - 3 * 8
        std::cout << "sizeof a " << sizeof(a) << '\n'; 

        std::string b = std::move(a);

        std::cout << "a: " << a << '\n';
        std::cout << "b: " << b << '\n';
    }


    {
        int* a = new int{1};
        int* b = std::move(a);
        std::cout << *b << '\n';
    }

}
