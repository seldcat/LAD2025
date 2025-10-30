#define _XOPEN_SOURCE 700

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

/* Коды ошибок (используем в тестах) */
#define ERR_USAGE       1
#define ERR_IN_OPEN     2
#define ERR_OUT_OPEN    3
#define ERR_IN_STAT     4
#define ERR_READ        5
#define ERR_WRITE       6
#define ERR_CLOSE_OUT   7
#define ERR_CLOSE_IN    8
#define ERR_UNLINK_OUT  9
#define ERR_UNLINK_IN   10

static void print_usage(const char *prog)
{
    fprintf(stderr, "Usage: %s infile outfile\n", prog);
}

/*
 * Безопасное перемещение:
 * 1) открыть infile (read-only),
 * 2) создать/очистить outfile с правами как у infile,
 * 3) поблочно копировать данные,
 * 4) fsync + закрыть outfile,
 * 5) закрыть infile,
 * 6) unlink(infile).
 */
int main(int argc, char *argv[])
{
    const char *src;
    const char *dst;
    int in_fd = -1;
    int out_fd = -1;
    struct stat st;
    int rc = 0;
    int out_created = 0;

    if (argc != 3) {
        print_usage(argv[0]);
        return ERR_USAGE;
    }

    src = argv[1];
    dst = argv[2];

    if (strcmp(src, dst) == 0) {
        fprintf(stderr, "move: source and destination must be different\n");
        return ERR_USAGE;
    }

    in_fd = open(src, O_RDONLY);
    if (in_fd < 0) {
        perror("move: open input");
        return ERR_IN_OPEN;
    }

    if (fstat(in_fd, &st) < 0) {
        perror("move: fstat input");
        rc = ERR_IN_STAT;
        goto cleanup;
    }

    out_fd = open(dst, O_WRONLY | O_CREAT | O_TRUNC, st.st_mode & 0777);
    if (out_fd < 0) {
        perror("move: open output");
        rc = ERR_OUT_OPEN;
        goto cleanup;
    }
    out_created = 1;

    {
        char buf[64 * 1024];
        ssize_t nread;

        while ((nread = read(in_fd, buf, sizeof(buf))) > 0) {
            ssize_t total_written = 0;
            while (total_written < nread) {
                ssize_t nw = write(out_fd, buf + total_written, (size_t)(nread - total_written));
                if (nw < 0) {
                    perror("move: write");
                    rc = ERR_WRITE;
                    goto cleanup;
                }
                total_written += nw;
            }
        }

        if (nread < 0) {
            perror("move: read");
            rc = ERR_READ;
            goto cleanup;
        }
    }

    if (fsync(out_fd) < 0) {
        perror("move: fsync output");
        rc = ERR_WRITE;
        goto cleanup;
    }

    if (close(out_fd) < 0) {
        perror("move: close output");
        out_fd = -1;
        rc = ERR_CLOSE_OUT;
        goto cleanup;
    }
    out_fd = -1;

    if (close(in_fd) < 0) {
        perror("move: close input");
        in_fd = -1;
        rc = ERR_CLOSE_IN;
        goto cleanup;
    }
    in_fd = -1;

    if (unlink(src) < 0) {
        perror("move: unlink input");
        rc = ERR_UNLINK_IN;
        goto cleanup;
    }

    return 0;

cleanup:

    if (out_fd >= 0) {
        if (close(out_fd) < 0) {
            perror("move: cleanup close output");
            if (rc == 0) {
                rc = ERR_CLOSE_OUT;
            }
        }
    }

    if (out_created && rc != ERR_UNLINK_IN) {
        if (unlink(dst) < 0) {
            perror("move: cleanup unlink output");
            if (rc == 0) {
                rc = ERR_UNLINK_OUT;
            }
        }
    }

    if (in_fd >= 0) {
        if (close(in_fd) < 0) {
            perror("move: cleanup close input");
            if (rc == 0) {
                rc = ERR_CLOSE_IN;
            }
        }
    }

    return rc;
}
