#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <rhash.h>

#ifdef USE_READLINE
#include <readline/readline.h>
#include <readline/history.h>
#endif


static void print_hex(const unsigned char *digest, size_t len) {
    char buf[256];
    int out_len = rhash_print_bytes(buf, digest, len, RHPR_HEX);
    printf("%s\n", buf);
}

static void print_base64(const unsigned char *digest, size_t len) {
    char buf[256];
    int out_len = rhash_print_bytes(buf, digest, len, RHPR_BASE64);
    printf("%s\n", buf);
}

static int algo_from_name(const char *name) {
    if (strcasecmp(name, "md5") == 0) return RHASH_MD5;
    if (strcasecmp(name, "sha1") == 0) return RHASH_SHA1;
    if (strcasecmp(name, "tth") == 0) return RHASH_TTH;
    return 0;
}

static void process(const char *algo_name, const char *input) {
    int algo = algo_from_name(algo_name);
    if (!algo) {
        fprintf(stderr, "Unknown algorithm: %s\n", algo_name);
        return;
    }

    unsigned char digest[64];
    size_t digest_len = rhash_get_digest_size(algo);

    if (input[0] == '"') {
        const char *str = input + 1;
        size_t l = strlen(str);
        if (l > 0 && str[l-1] == '"')
            ((char*)str)[l-1] = 0;
        rhash_msg(algo, str, strlen(str), digest);
    } else {
        if (rhash_file(algo, input, digest) < 0) {
            perror("File error");
            return;
        }
    }

    if (isupper((unsigned char)algo_name[0]))
        print_hex(digest, digest_len);
    
    else
        print_base64(digest, digest_len);
}

int main(void) {
    rhash_library_init();

    char *line = NULL;
#ifndef USE_READLINE
    size_t n = 0;
#endif

    for (;;) {
#ifdef USE_READLINE
        line = readline("rhasher> ");
        if (!line) break;
        if (*line) add_history(line);
#else
        printf("rhasher> ");
        if (getline(&line, &n, stdin) < 0)
            break;
        line[strcspn(line, "\n")] = 0;
#endif

        char *algo = strtok(line, " ");
        char *arg  = strtok(NULL, " ");
        if (!algo || !arg) {
            fprintf(stderr, "Format: <algo> <file|\"string\">\n");
#ifndef USE_READLINE
            continue;
#else
            free(line);
            continue;
#endif
        }

        process(algo, arg);

#ifdef USE_READLINE
        free(line);
#endif
    }

#ifndef USE_READLINE
    free(line);
#endif
    return 0;
}
