#include <iostream>
#include <cassert>
#include <utility>


class Object {
public:
    Object() { std::cout << "Object constructed.\n"; }
    ~Object() { std::cout << "Object destructed.\n"; }
    Object(const Object&) { std::cout << "Object copy.\n"; }
    Object(Object&&) { std::cout << "Object move.\n"; }

    Object& operator=(const Object&) { 
        std::cout << "Object copy assign.\n";
        return *this;
    }

    Object& operator=(Object&&) { 
        std::cout << "Object move assign.\n";
        return *this;
    }
};

template<typename T>
class unique_pointer {
private:

    T* ptr_ = nullptr;

public:

    unique_pointer(T* ptr): ptr_(ptr) {}

    unique_pointer(const unique_pointer&) = delete; // copy constructor

    unique_pointer(unique_pointer&& up) { // move constructor
        ptr_ = up.ptr_; 
        up.ptr_ = nullptr;
    }

    void operator=(const unique_pointer&) = delete; // copy assignment

    unique_pointer& operator=(unique_pointer&& up) { // move assignment
        ptr_ = up.ptr_; 
        up.ptr_ = nullptr;
        return this;
    }

    friend std::ostream& operator<<(
        std::ostream& stream, 
        const unique_pointer& up
    ) {
        stream << up.ptr_;
        return stream;
    }

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

template<typename T, typename ... Args>
unique_pointer<T> make_unique(Args&&... args) {
    return unique_pointer<T>(new T(std::forward<Args>(args)...));
}

int main() {
    std::cout << "sizeof = ";
    {
        assert(sizeof(unique_pointer<int>) == 8);
    }
    std::cout << "SUCCESS\n";


    std::cout << "=== Basic construction/destruction\n";
    {
        unique_pointer<int> a(new int{5});
        assert(*a == 5);
    }


    std::cout << "=== get\n";
    {
        unique_pointer<int> a(new int{5});
        assert(a.get() != nullptr);
    }


    std::cout << "=== Release ownership\n";
    {
        unique_pointer<int> a(new int{5});
        unique_pointer<int> b(a.release());
        assert(a.get() == nullptr);
        assert(*b == 5);
    }


    std::cout << "=== Replace managed object\n";
    {
        unique_pointer<int> a(new int{5});
        a.reset(new int(6));
        assert(*a == 6);
    }


    std::cout << "=== Swap managed object\n";
    {
        unique_pointer<int> a(new int{5});
        unique_pointer<int> b(new int{7});
        a.swap(b);
        assert(*a == 7);
        assert(*b == 5);
    }


    std::cout << "=== copy object\n";
    {
        unique_pointer<int> a(new int{5});
        // unique_pointer<int> b(a); // should be illegal
        // unique_pointer<int> c = a; // should be illegal
    }


    std::cout << "=== move object\n";
    {
        unique_pointer<int> a(new int{5});
        std::cout << "a[" << a << "] " << *a << '\n';
        unique_pointer<int> b(std::move(a)); 
        std::cout << "moved to -> b[" << b << "] " << *b << '\n';
        unique_pointer<int> c = std::move(b);
        std::cout << "moved to -> c[" << c << "] " << *c << '\n';
    }


    std::cout << "=== make unique\n";
    {
        unique_pointer<int> a = make_unique<int>(1);
        assert(*a == 1);

        unique_pointer<Object> b = make_unique<Object>();
    }

}
