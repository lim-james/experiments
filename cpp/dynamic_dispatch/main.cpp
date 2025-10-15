#include <iostream>
#include <memory>

class A_non_virtual {
public:
    void action() { std::cout << "A\n"; }
};

class B_non_virtual: public A_non_virtual {
public:
    void action() { std::cout << "B\n"; }
};

class A_virtual {
public:
    virtual void action() { std::cout << "A\n"; }
};

class B_virtual: public A_virtual {
public:
    void action() override /* optional but recommended */ { 
        std::cout << "B\n"; 
    }
};


int main() {
    {
        std::cout << "Non virtual";
        std::cout << " // sizeof(B) = " << sizeof(B_non_virtual) << '\n';
        // returns 1, empty class -> minimum addressable size.

        std::unique_ptr<A_non_virtual> b = std::make_unique<B_non_virtual>();
        std::cout << "b->action() = ";
        b->action(); // prints "A"
    }

    {
        std::cout << "Virtual";
        std::cout << " // sizeof(B) = " << sizeof(B_virtual) << '\n';
        // returns 8, pointer size to v-table

        std::unique_ptr<A_virtual> b = std::make_unique<B_virtual>();
        std::cout << "b->action() = ";
        b->action(); // prints "B"
        std::cout << "b->A_virtual::action() = ";
        b->A_virtual::action(); // prints "A" no dynamic dispatch
    }

    return 0;
}

