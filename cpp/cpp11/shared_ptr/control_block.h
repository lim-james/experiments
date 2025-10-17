#ifndef CONTROL_BLOCK
#define CONTROL_BLOCK

#include <stddef.h>

struct control_block {
    size_t strong_count;
    size_t weak_count;
};

#endif
