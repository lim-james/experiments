# Shared pointer

In my mind it should be similar to unique_ptr with the exception that now we
keep track of the reference count and only delete managed object when all have
released reference.
