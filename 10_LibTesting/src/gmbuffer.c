#include "gmbuffer.h"

int gm_reserve(void **ptr, size_t *cap, size_t need)
{
    if (*cap >= need)
        return 0;

    size_t new_cap = (*cap == 0) ? 8 : *cap;
    while (new_cap < need)
        new_cap *= 2;

    void *tmp = realloc(*ptr, new_cap);
    if (!tmp)
        return -1;

    *ptr = tmp;
    *cap = new_cap;
    return 0;
}
