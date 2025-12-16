#include <stdio.h>
#include <string.h>

int main(void) {
    const char *s = "Привет, Ekaterina!";
    if (strcmp(s, "Привет, Ekaterina!") != 0) {
        fprintf(stderr, "FAIL i18n\n");
        return 1;
    }
    return 0;
}
