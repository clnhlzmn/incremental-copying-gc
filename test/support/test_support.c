#include "test_support.h"
#include <stdlib.h>

void roots_foreach(void (*cb)(intptr_t **item, void *ctx), void *cb_ctx, void *foreach_ctx) {
    intptr_t **it = foreach_ctx;
    if (it) {
        cb(it, cb_ctx);
    }
}
