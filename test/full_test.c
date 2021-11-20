#include "incremental_gc.h"
#include "test_support.h"
#include <assert.h>
#include <stdlib.h>

/*
root -> [0|1|...|a-2|a-1]
         | |      |   |->[*|*|...|*|*]
         | |      |----->[*|*|...|*|*]
         | |
         | |------------>[*|*|...|*|*]
         |-------------->[*|*|...|*|*]
*/

int main(void) {
    struct gc gc;
    const size_t array_size = 10;
    const size_t mem_size = //1000;
        (array_size * array_size                    /*number of cells in array*/
        + array_size                                /*number of cells in root array*/
        + (array_size + 1) * GC_META_SIZE_WORDS)    /*overhead for each allocation*/
            * 3;                                    /*doubled for each semispace*/
    intptr_t memory[mem_size];
    gc_init(&gc, memory, mem_size);
    
    /*alloc root array of refs*/
    intptr_t *root = gc_alloc_ref_array(&gc, roots_foreach, &root, array_size);
    // gc_print_heap(&gc);
    
    intptr_t expected_values[array_size][array_size];
    
    for (int n = 0; n < 5000; ++n) {
        size_t i = rand() % array_size;
        intptr_t **array = (intptr_t**)root;
        gc_read_barrier(&gc, &array[i]);
        if (array[i] == NULL) {
            array[i] = gc_alloc_int_array(&gc, roots_foreach, &root, array_size);
            // printf("\n\n");
            // gc_print_heap(&gc);
            assert(array[i]);
            for (size_t j = 0; j < array_size; ++j) {
                intptr_t v = rand() % array_size;
                array[i][j] = v;
                expected_values[i][j] = v;
            }
        } else {
            for (size_t j = 0; j < array_size; ++j) {
                assert(array[i][j] == expected_values[i][j]);
            }
            array[i] = NULL;
        }
    }
    return 0;
}
