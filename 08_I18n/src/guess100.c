#include "config.h"

#include <errno.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libintl.h>

#define _(S) gettext(S)

static void die_eof(void) {
    fputs(_("Error: standard input was closed (EOF).\n"), stderr);
    exit(2);
}

static void trim_newlines_and_spaces(char *s) {
    size_t n = strlen(s);
    while (n > 0) {
        char c = s[n - 1];
        if (c == '\n' || c == '\r' || c == ' ' || c == '\t') {
            s[n - 1] = '\0';
            n--;
        } else {
            break;
        }
    }
    while (*s == ' ' || *s == '\t') {
        memmove(s, s + 1, strlen(s));
    }
}

static int read_line(char *buf, size_t cap) {
    errno = 0;
    if (fgets(buf, (int)cap, stdin) == NULL) {
        die_eof();
    }
    trim_newlines_and_spaces(buf);
    return 1;
}

static int ask_yes_no_greater_than(int mid) {
    char buf[128];

    for (;;) {
        printf(_("Is your number greater than %d? (Yes/No): "), mid);
        fflush(stdout);

        read_line(buf, sizeof(buf));

        if (strcmp(buf, "Yes") == 0) return 1;
        if (strcmp(buf, "No") == 0) return 0;

        fprintf(stderr, _("Invalid answer. Please type exactly \"Yes\" or \"No\".\n"));
    }
}

int main(void) {
    setlocale(LC_ALL, "");
    bindtextdomain(PACKAGE, LOCALEDIR);
    textdomain(PACKAGE);

    puts(_("Think of a number from 1 to 100."));
    printf(_("Press Enter when you're ready... "));
    fflush(stdout);

    char tmp[32];
    read_line(tmp, sizeof(tmp)); /* EOF here is an error by spec */

    int lo = 1;
    int hi = 100;

    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;

        int greater = ask_yes_no_greater_than(mid);
        if (greater) {
            lo = mid + 1;
        } else {
            hi = mid;
        }
    }

    printf(_("Your number is %d.\n"), lo);
    return 0;
}
