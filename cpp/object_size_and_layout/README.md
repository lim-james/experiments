# Object size & layout

## Initial thoughts

I want to know if there are unique properties of how much memory each object is
taking up. Feel it is important that I am aware of the size of my primitives,
pointers, ds etc

## Findings
`sizeof` returns size in bytes. 
Smallest addressable unit is 1 byte (char)

raw pointers are all same, because they're just pointers. (8 bytes because im on
a 64 bit system)

### `sizeof("hello world") = 12` vs `sizeof(std::string("hello world")) = 24`
24 I understand, 8 for capacity, 8 for size, 8 for pointer. but 12 because well 
12 chars in 'hello world'. 

if 8 for pointer, does that mean strings are heap allocated? there seems to be
something about small string optimization (SSO) that i should look into. But
from what I'm reading, it seems like if a string is short enough, std::string
has a local member buffer to store its content on the stack. This is to avoid
malloc. I should test this.


### `sizeof(unique_ptr) = 8` vs `sizeof(shared_ptr) = 16` 
[cppreference/shared_ptr](https://en.cppreference.com/w/cpp/memory/shared_ptr.html)
`shared_ptr` holds **2** pointers 1. stored pointer, 2. pointer to control
block. The control block holds 
* either a pointer to the managed object or the managed object itself;
* the deleter (type-erased);
* the allocator (type-erased);
* the number of `shared_ptrs` that own the managed object;
* the number of `weak_ptrs` that refer to the managed object.
> copied from cpp website but i like to refer to it here too.

### `sizeof(weak_ptr) = 16` 
initial thoughts before reading documentation: you definitely need a pointer to
the managed object, the destructor needs to be able to decrement the reference
count for weak_ptrs in the control block so it needs the pointer to the control
block too.
[cppreference/weak_ptr](https://en.cppreference.com/w/cpp/memory/weak_ptr.html)
ok i'm right. i found this note interesting "It is not possible to access the 
stored pointer in a weak_ptr without locking it into a shared_ptr" I believe
this refers to `.get()`


## Resources

[cppreference/types](https://en.cppreference.com/w/cpp/language/types.html)
