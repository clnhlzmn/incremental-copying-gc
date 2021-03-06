
#include <stdio.h>
#include <assert.h>
#include "incremental_gc.h"

//forwards yields one root pointed to by root
void roots_foreach(void (*cb)(intptr_t **item, void *ctx), void *cb_ctx, void *foreach_ctx) {
    intptr_t **it = foreach_ctx;
    cb(it, cb_ctx);
}

#define MEM_SIZE (100)

intptr_t mem[MEM_SIZE];

#define OBJ_SIZE (3)

#define INT_DATA ((intptr_t)-1)

int main(void) {
    return 0;
    //memory for gc
    struct gc gc_inst;
    //gc instance
    gc_init(&gc_inst, mem, MEM_SIZE);
    for (int repeat = 0; repeat < 500; ++repeat) {
        //printf("%d", __LINE__);
        //alloc one ref cell (no roots yet)
        intptr_t *root = NULL;
        /*printf("main: &root = %p\r\n", &root);*/
        root = gc_alloc_ref_array(&gc_inst, roots_foreach, &root, OBJ_SIZE);
        assert(root);
        //printf("%d", __LINE__);
        assert(gc_get_size(root) == OBJ_SIZE);
        //printf("%d", __LINE__);
        //store a value in non ref cell
        for (int i = 0; i < OBJ_SIZE; ++i) {
            root[i] = (intptr_t)gc_alloc_int_array(&gc_inst, roots_foreach, &root, OBJ_SIZE);
            assert(root[i]);
            assert(gc_get_size((intptr_t*)root[i]) == OBJ_SIZE);
            for (unsigned j = 0; j < OBJ_SIZE; ++j) {
                ((intptr_t*)root[i])[j] = INT_DATA;
            }
        }
        //allocate a bunch
        for (int i = 0; i < 10000; ++i) {
            //alloc chunks of 10 cells, no refs
            intptr_t *a = gc_alloc_int_array(&gc_inst, roots_foreach, &root, OBJ_SIZE);
            assert(a);
            assert(gc_get_size(a) == OBJ_SIZE);
            /*printf("%d : %d\r\n", __LINE__, i);*/
            //overwrite memory a little
            for (int j = 0; j < 10; ++j) {
                a[j] = j;
                //std::cout << __LINE__ << ":" << i << std::endl; 
            }
        }
        //check that our two allocations survived
        assert(root);
        for (int i = 0; i < OBJ_SIZE; ++i) {
            assert(root[i]);
            assert(gc_get_size((intptr_t*)root[i]) == OBJ_SIZE);
            gc_read_barrier(&gc_inst,(intptr_t **) &root[i]);
            for (unsigned j = 0; j < OBJ_SIZE; ++j) {
                assert(((intptr_t*)root[i])[j] == INT_DATA);
            }
        }
    }
    char c = getc(stdin);
    (void)c;
}
