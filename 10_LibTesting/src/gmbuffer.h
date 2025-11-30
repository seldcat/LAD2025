#ifndef GMBUFFER_H
#define GMBUFFER_H

#include <stdlib.h>
#include <string.h>


#define GM_INIT(buf) \
    do { (buf)->data = NULL; (buf)->len = 0; (buf)->cap = 0; } while (0)

#define GM_FREE(buf) \
    do { free((buf)->data); (buf)->data = NULL; } while (0)

int gm_reserve(void **ptr, size_t *cap, size_t need);

#endif
