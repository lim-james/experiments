#include <iostream>
#include <cassert>

template<typename T>
class unique_pointer {
private:

    T* ptr_ = nullptr;

public:

    unique_pointer(T* ptr): ptr_(ptr) {}

    ~unique_pointer() {
        delete ptr_;
    }

    T* get() {
        return ptr_;
    }

    T* release() {
        T* t = ptr_;
        ptr_ = nullptr;
        return t;
    }

    void reset(T* ptr) {
        delete ptr_;
        ptr_ = ptr;
    }
    
    void swap(unique_pointer& other) {
        T* t = other.ptr_;
        other.ptr_ = ptr_;
        ptr_ = t;
    }

    T operator*() {
        return *ptr_;
    }
};

int main() {
    std::cout << "=== Basic construction/destruction\n";
    {
        unique_pointer<int> p1(new int(5));
        //assert(p1);
        assert(*p1 == 5);
    }


    std::cout << "=== get\n";
    {
        unique_pointer<int> p1(new int(5));
        assert(p1.get() != nullptr);
    }


    std::cout << "=== Release ownership\n";
    {
        unique_pointer<int> p1(new int(5));
        unique_pointer<int> p2(p1.release());
        assert(p1.get() == nullptr);
        assert(*p2 == 5);
    }


    std::cout << "=== Replace managed object\n";
    {
        unique_pointer<int> p1(new int(5));
        p1.reset(new int(6));
        assert(*p1 == 6);
    }


    std::cout << "=== Swap managed object\n";
    {
        unique_pointer<int> p1(new int(5));
        unique_pointer<int> p2(new int(7));
        p1.swap(p2);
        assert(*p1 == 7);
        assert(*p2 == 5);
    }
}
