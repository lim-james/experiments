#include "weak_pointer.h"

template<typename T>
weak_pointer<T>::~weak_pointer() {
    if (ptr_ == nullptr)
        return;

    --control_block_->weak_count;
    // delete
}

template<typename T>
weak_pointer<T>::weak_pointer(const weak_pointer<T>& wp) {
    ptr_ = wp.ptr_;
    control_block_ = wp.control_block_;
    ++control_block_->weak_count;
}

template<typename T>
weak_pointer<T>::weak_pointer(weak_pointer<T>&& wp) {
    if (this != &wp) {
        ptr_ = wp.ptr_;
        control_block_ = wp.control_block_;

        wp.ptr_ = nullptr;
        wp.control_block_ = nullptr;
    }
}


template<typename T>
weak_pointer<T>& weak_pointer<T>::operator=(const weak_pointer<T>&) {
    ptr_ = wp.ptr_;
    control_block_ = wp.control_block_;
    ++control_block_->weak_count;
}

template<typename T>
weak_pointer<T>& weak_pointer<T>::operator=(weak_pointer<T>&&) {
    if (this != &wp) {
        ptr_ = wp.ptr_;
        control_block_ = wp.control_block_;

        wp.ptr_ = nullptr;
        wp.control_block_ = nullptr;
    }
}

template<typename T>
T& weak_pointer<T>::operator*();

template<typename T, typename ...Args>
[[nodiscard]]weak_pointer<T> make_weak(Args&&... args);
