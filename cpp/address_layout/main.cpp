#include <iostream>

class Object {
private:
    unsigned char id_;
public:
    Object(unsigned char id): id_(id) { 
        std::cout << "CONSTRUCT " << (int)id_ << '\n'; 
    }

    Object(const Object& cp): id_(cp.id_) {
        std::cout << "COPY " << (int)id_ << '\n';
    }

    Object(Object&& mv): id_(mv.id_) {
        std::cout << "MOVE " << (int)id_ << '\n';
    }

    ~Object() { std::cout << "DESTRUCT " << (int)id_ << '\n'; }
};

class Container {
private: 
    Object a_, b_, c_;
public:
    Container(Object a, Object b, Object c): a_(a), b_(b), c_(c) {}
};

void fn(const Object& a, const Object& b, const Object& c) {}

int main() {
    {
        int a;
        int b=67;

        std::cout << "a: " << &a << '\n';
        std::cout << "b: " << &b << '\n'; // grows downwards
    }
    std::cout << std::endl;

    {
        std::cout << "Object size " << sizeof(Object) << '\n';
        Object a{1}; // 1 byte
        Object b{2};

        std::cout << "a: " << &a << '\n';
        std::cout << "b: " << &b << '\n';
    }
    std::cout << std::endl;

    {
        fn(Object{1}, Object{2}, Object{3});
    }
    std::cout << std::endl;

    {
        Container{Object{1}, Object{2}, Object{3}};
    }
    std::cout << std::endl;

    {
        Object* a = new Object{1};
        Object* b = new Object{2};
        std::cout << "a: " << &a << '\n';
        std::cout << "b: " << &b << '\n';

        delete b;
        delete a;
    }

    return 0;
}
