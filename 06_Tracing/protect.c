#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>
#include <errno.h>
#include <stdio.h>

typedef int (*unlink_func_t)(const char *pathname);
typedef int (*remove_func_t)(const char *pathname);

static unlink_func_t real_unlink = NULL;
static remove_func_t real_remove = NULL;

static void init_real_functions(void)
{
    if (!real_unlink) {
        real_unlink = (unlink_func_t)dlsym(RTLD_NEXT, "unlink");
        if (!real_unlink) {
            fprintf(stderr, "protect.so: failed to resolve real unlink: %s\n", dlerror());
        }
    }
    if (!real_remove) {
        real_remove = (remove_func_t)dlsym(RTLD_NEXT, "remove");
        if (!real_remove) {
            fprintf(stderr, "protect.so: failed to resolve real remove: %s\n", dlerror());
        }
    }
}

static int should_protect(const char *pathname)
{
    if (!pathname) return 0;
    return strstr(pathname, "PROTECT") != NULL;
}

int unlink(const char *pathname)
{
    init_real_functions();

    if (should_protect(pathname)) {
        errno = EACCES;
        return -1;
    }

    if (!real_unlink) {
        errno = EIO;
        return -1;
    }

    return real_unlink(pathname);
}

int remove(const char *pathname)
{
    init_real_functions();

    if (should_protect(pathname)) {
        errno = EACCES;
        return -1;
    }

    if (!real_remove) {
        errno = EIO;
        return -1;
    }

    return real_remove(pathname);
}
