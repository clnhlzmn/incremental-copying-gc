#include "incremental_gc.h"
#include <assert.h>

int main(void) {
    struct gc gc_instance;
    const size_t size = 10;
    intptr_t mem[size];
    assert(gc_init(&gc_instance, mem, size) == 0);
    return 0;
}
