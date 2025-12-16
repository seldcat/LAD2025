/**
 * @file greet.c
 * @brief Implementation of libgreet.
 */

#include "greet.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *greet_build(const char *prefix, const char *name) {
    if (!prefix) prefix = "Hello";

    const char *n = (name && name[0]) ? name : "friend";

    size_t need = strlen(prefix) + 2 /* ", " */ + strlen(n) + 2 /* "!" + \0 */;
    char *out = (char *)malloc(need);
    if (!out) return NULL;

    snprintf(out, need, "%s, %s!", prefix, n);
    return out;
}
