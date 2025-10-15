#ifndef SHARED_POINTER_H
#define SHARED_POINTER_H

#include "control_block.h"

template<typename T>
class shared_pointer {
private:

    T* ptr_;
    control_block* control_block_;

public:

    shared_pointer();
    shared_pointer(T* ptr);

    ~shared_pointer();

    shared_pointer(const shared_pointer& other);
    shared_pointer(shared_pointer&& other);

    shared_pointer& operator=(const shared_pointer& other);
    shared_pointer& operator=(shared_pointer&& other);

    T operator*() const;
};

template<typename T, typename ...Args>
[[nodiscard]] shared_pointer<T> make_shared(Args&&... args);

#include "shared_pointer.hpp"

#endif
