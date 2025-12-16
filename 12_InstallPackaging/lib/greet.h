#ifndef GREET_H
#define GREET_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @file greet.h
 * @brief Public API of libgreet.
 */

/**
 * @brief Build greeting string "Hello, <name>!" (localized message handled by caller).
 *
 * The returned pointer must be freed by the caller with free(3).
 *
 * @param prefix Greeting prefix (already localized), e.g. "Hello"
 * @param name   Person name (may be NULL/empty)
 * @return Newly allocated string on success, NULL on allocation error.
 */
char *greet_build(const char *prefix, const char *name);

#ifdef __cplusplus
}
#endif

#endif
