#include "greet.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int fail(const char *msg) {
    fprintf(stderr, "FAIL: %s\n", msg);
    return 1;
}

int main(void) {
    char *s1 = greet_build("Hello", "Ada");
    if (!s1) return fail("allocation failed");
    if (strcmp(s1, "Hello, Ada!") != 0) {
        free(s1);
        return fail("unexpected greeting for Ada");
    }
    free(s1);

    char *s2 = greet_build("Hello", NULL);
    if (!s2) return fail("allocation failed");
    if (strcmp(s2, "Hello, friend!") != 0) {
        free(s2);
        return fail("unexpected greeting for default name");
    }
    free(s2);

    return 0;
}
