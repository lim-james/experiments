#ifndef WEAK_POINTER_H
#define WEAK_POINTER_H

#include "control_block.h"

template<typename T>
class weak_pointer<T> {
private:
    
    T* ptr_;
    control_block* control_block_;

public:

    weak_pointer() = delete;

    ~weak_pointer();

    weak_pointer(const weak_pointer&);
    weak_pointer(weak_pointer&&);

    weak_pointer& operator=(const weak_pointer&);
    weak_pointer& operator=(weak_pointer&&);

    T& operator*();
};

template<typename T, typename ...Args>
[[nodiscard]]weak_pointer make_weak(Args&&... args);

#include "weak_pointer.hpp"

#endif
