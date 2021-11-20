#include "incremental_gc.h"
#include "test_support.h"
#include <assert.h>

int main(void) {
    struct gc gc_instance;
    const size_t size = 10;
    intptr_t mem[size];
    gc_init(&gc_instance, mem, size);
    intptr_t *root = NULL;
    intptr_t *ptr = gc_alloc_int_array(&gc_instance, roots_foreach, root, 1);
    assert(ptr);
    return 0;
}
