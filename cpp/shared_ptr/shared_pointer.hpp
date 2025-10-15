#include "shared_pointer.h"

#include <iostream>
#include <utility>

template<typename T>
shared_pointer<T>::shared_pointer() {
    ptr_ = new T;
    control_block_ = new control_block{1};
}

template<typename T>
shared_pointer<T>::shared_pointer(T* ptr): ptr_(ptr) {
    if (ptr_ != nullptr) {
        std::cout << "constructor\n";
        control_block_ = new control_block{1};
    }
}

template<typename T>
shared_pointer<T>::~shared_pointer() {
    if (ptr_ == nullptr)
        return;

    --control_block_->strong_count;
    std::cout << "deref // count = " << control_block_->strong_count << '\n';
    if (control_block_->strong_count == 0) {
        delete ptr_;
        std::cout << "destruct\n";
    }
}

template<typename T>
shared_pointer<T>::shared_pointer(const shared_pointer& other)
    : ptr_(other.ptr_) 
    , control_block_(other.control_block_) {
    ++control_block_->strong_count;
    std::cout << "copy // count = " << control_block_->strong_count << '\n';
}

template<typename T>
shared_pointer<T>::shared_pointer(shared_pointer&& other) {
    if (this != &other) {
        std::cout << "move\n";
        ptr_ = other.ptr_;
        control_block_ = other.control_block_;

        other.ptr_ = nullptr;
        other.control_block_ = nullptr;
        std::cout << "moved\n";
    }
}

template<typename T>
shared_pointer<T>& shared_pointer<T>::operator=(const shared_pointer& other) {
    std::cout << "copy\n";
    ptr_ = other.ptr_;
    control_block_ = other.control_block_;
    ++control_block_->strong_count;
    return *this;
}

template<typename T>
shared_pointer<T>& shared_pointer<T>::operator=(shared_pointer&& other) {
    if (this == &other)
        return *this;

    std::cout << "move\n";
    ptr_ = other.ptr_;
    control_block_ = other.control_block_;

    other.ptr_ = nullptr;
    other.control_block_ = nullptr;

    return *this;
}

template<typename T>
T shared_pointer<T>::operator*() const {
    return *ptr_;
}

template<typename T, typename ...Args>
[[nodiscard]] shared_pointer<T> make_shared(Args&&... args) {
    return shared_pointer<T>(new T(std::forward<Args>(args)...));
}
