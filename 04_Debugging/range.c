// range.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <limits.h>

long long g_start = 0;
long long g_stop  = 0;
long long g_step  = 0;
long long g_current = 0;
long long g_index = 0; // номер элемента прогрессии (1-based)

// Простейший help
static void usage(const char *prog)
{
    fprintf(stderr,
            "Usage:\n"
            "  %s N           # prints 0..N-1\n"
            "  %s M N         # prints M..N-1\n"
            "  %s M N S       # prints M, M+S, ... while value < N (S>0) or > N (S<0)\n",
            prog, prog, prog);
}

// Аккуратный парсинг long long
static int parse_ll(const char *s, long long *out)
{
    char *end = NULL;
    errno = 0;
    long long v = strtoll(s, &end, 10);

    if (errno != 0 || end == s || *end != '\0') {
        return 0;
    }
    *out = v;
    return 1;
}

static void print_value(long long value)
{
    printf("%lld\n", value);
}

int main(int argc, char **argv)
{
    long long start, stop, step;

    if (argc == 1 || argc > 4) {
        usage(argv[0]);
        return (argc == 1) ? 0 : 1;
    }

    if (argc == 2) {
        // range(N) -> 0..N-1
        if (!parse_ll(argv[1], &stop)) {
            fprintf(stderr, "Invalid N\n");
            return 1;
        }
        start = 0;
        step  = 1;
    } else if (argc == 3) {
        // range(M, N) -> M..N-1
        if (!parse_ll(argv[1], &start) || !parse_ll(argv[2], &stop)) {
            fprintf(stderr, "Invalid M or N\n");
            return 1;
        }
        step = 1;
    } else {
        // argc == 4: range(M, N, S)
        if (!parse_ll(argv[1], &start) ||
            !parse_ll(argv[2], &stop)  ||
            !parse_ll(argv[3], &step)) {
            fprintf(stderr, "Invalid M, N or S\n");
            return 1;
        }
    }

    if (step == 0) {
        fprintf(stderr, "Step must not be 0\n");
        return 1;
    }

    g_start = start;
    g_stop  = stop;
    g_step  = step;
    g_index = 0;

    if (step > 0) {
        for (long long v = start; v < stop; v += step) {
            g_current = v;
            g_index++;              // нумерация элементов с 1
            print_value(v);
        }
    } else {
        for (long long v = start; v > stop; v += step) {
            g_current = v;
            g_index++;
            print_value(v);
        }
    }

    return 0;
}
