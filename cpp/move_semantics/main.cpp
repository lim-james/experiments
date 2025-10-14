#include <iostream>
#include <string>
#include <memory>
#include <utility>

class Object {
private:
    int i_ = 0; 

public:

    Object(int i): i_(i) {}
    ~Object() {}

    // copy 
    Object(const Object& other) {
        i_ = other.i_;
    }

    Object& operator=(const Object& other) {
        i_ = other.i_;
        return *this;
    }

    // move 
    Object(Object&& other) {
        if (this != &other)
            i_ = other.i_;
            other.i_ = 0; 
    }


    Object& operator=(Object&& other) {
        if (this == &other)
            return *this;
        i_ = other.i_;
        other.i_ = 0;
        return *this;
    }

    int get() const {
        return i_;
    }

};

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
        std::cout << "a: " << a << ' ' << *a << '\n';
        std::cout << "b: " << b << ' ' << *b << '\n';
    }

    {
        int a = std::move(5);
        std::cout << a << '\n';
    }

    {
        Object a{5};
        std::cout << "a: " << a.get() << '\n';
        Object b{std::move(a)};
        std::cout << "a: " << a.get() << '\n'; 
        std::cout << "b: " << b.get() << '\n';
    }

    {
        const Object a{5};
        std::cout << "a: " << a.get() << '\n';
        Object b{std::move(a)}; // fails silently, performs copy
        std::cout << "a: " << a.get() << '\n'; 
        std::cout << "b: " << b.get() << '\n';
    }

    {
        const std::unique_ptr<int> a{new int{5}};
        std::cout << "a: " << *a << '\n';
        // a.reset(new int{10}); // not allowed
        // not allowed copy constructor deleted
        // const std::unique_ptr<int> b{std::move(a)};
    }

}
