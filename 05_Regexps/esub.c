#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>

static void die_regex(int rc, regex_t *re) {
    char buf[256];
    regerror(rc, re, buf, sizeof(buf));
    fprintf(stderr, "regex error: %s\n", buf);
    exit(1);
}

int main(int argc, char **argv) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s REGEXP SUBST [STRING]\n", argv[0]);
        return 1;
    }

    const char *pattern = argv[1];
    const char *subst   = argv[2];

    char input[8192];
    if (argc >= 4) {
        strncpy(input, argv[3], sizeof(input)-1);
        input[sizeof(input)-1] = 0;
    } else {
        if (!fgets(input, sizeof(input), stdin)) return 0;
        input[strcspn(input, "\n")] = 0;
    }

    regex_t re;
    int rc = regcomp(&re, pattern, REG_EXTENDED);
    if (rc != 0) die_regex(rc, &re);

    regmatch_t pm[10];
    rc = regexec(&re, input, 10, pm, 0);
    if (rc == REG_NOMATCH) {
        printf("%s\n", input);
        regfree(&re);
        return 0;
    }
    if (rc != 0) die_regex(rc, &re);

    char out[32768];
    out[0] = 0;

    strncat(out, input, pm[0].rm_so);

    for (size_t i = 0; i < strlen(subst); ++i) {
        if (subst[i] == '\\') {
            ++i;
            if (i >= strlen(subst)) {
                fprintf(stderr, "error: stray backslash\n");
                exit(1);
            }

            if (subst[i] == '\\') {
                strcat(out, "\\");
            } else if (isdigit((unsigned char)subst[i])) {
                int k = subst[i] - '0';
                if (pm[k].rm_so < 0) {
                    fprintf(stderr, "error: backref %d does not exist\n", k);
                    exit(1);
                }
                int len = pm[k].rm_eo - pm[k].rm_so;
                strncat(out, input + pm[k].rm_so, len);
            } else {
                fprintf(stderr, "error: bad escape\n");
                exit(1);
            }

        } else {
            size_t l = strlen(out);
            out[l] = subst[i];
            out[l+1] = 0;
        }
    }

    strcat(out, input + pm[0].rm_eo);

    printf("%s\n", out);

    regfree(&re);
    return 0;
}
