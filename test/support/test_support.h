#ifndef TEST_SUPPORT_H
#define TEST_SUPPORT_H

#include <stdint.h>

//yields one root pointed to by foreach_ctx
void roots_foreach(void (*cb)(intptr_t **item, void *ctx), void *cb_ctx, void *foreach_ctx);

#endif /*TEST_SUPPORT_H*/
