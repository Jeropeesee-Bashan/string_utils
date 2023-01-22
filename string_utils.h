#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#define WHITESPACE_CHARS "\t\n\v\f\r "

#include <string.h> /* All the neccessary functions */
#include <stddef.h> /* size_t, ptrdiff_t */
#include <stdlib.h> /* malloc, free */

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

struct Slice {
    size_t begin;
    size_t end;
};

struct StringSliceList {
    const char *string;
    struct Slice *data;
    size_t size;
};

char *strpnbrk(const char *string, const char *accept);

size_t string_length_n(const char *string, size_t max_length);

size_t string_length(const char *string);

const char *lstrip_string_n(const char *string, size_t max_string_len);

const char *lstrip_string(const char *string);

const char *rstrip_string_n(const char *string, size_t max_string_len);

const char *rstrip_string(const char *string);

void strip_string_n(const char *string,
                    size_t string_len,
                    const char **begin,
                    const char **end);

void strip_string(const char *string, const char **begin, const char **end);

size_t split_string_n(const char *string,
                      size_t string_len,
                      const char *pattern,
                      size_t pattern_len,
                      struct Slice *list,
                      size_t list_size);

size_t split_string(const char *string,
                    const char *pattern,
                    struct Slice *list,
                    size_t list_size);

size_t split_string_whitespace_n(const char *string,
                                 size_t string_len,
                                 struct Slice *list,
                                 size_t list_size);

size_t split_string_whitespace(const char *string,
                               struct Slice *list,
                               size_t list_size);

size_t copy_string_n(char *dest,
                     const char *source,
                     size_t size,
                     size_t source_len,
                     ptrdiff_t dest_offset);

size_t copy_string(char *dest,
                   const char *source,
                   size_t size,
                   ptrdiff_t dest_offset);

size_t join_string_n(char *dest,
                     const struct StringSliceList *list,
                     size_t size,
                     const char *postfix,
                     size_t postfix_len,
                     const char *prefix,
                     size_t prefix_len);

size_t join_string(char *dest,
                   const struct StringSliceList *list,
                   size_t size,
                   const char *postfix,
                   const char *prefix);

size_t remove_whitespace_n(char *dest,
                           const char *source,
                           size_t size,
                           size_t source_len);

size_t remove_whitespace(char *dest,
                         const char *source,
                         size_t size);

#ifdef STRING_UTILS_ALLOC

struct StringSliceList *split_string_n_alloc(const char *string,
                                             size_t string_len,
                                             const char *pattern,
                                             size_t pattern_len);

struct StringSliceList *split_string_alloc(const char *string,
                                           const char *pattern);

struct StringSliceList *split_string_whitespace_n_alloc(const char *string,
                                                        size_t string_len);

struct StringSliceList *split_string_whitespace_alloc(const char *string);

char *copy_string_alloc_n(const char *source, size_t source_len);

char *copy_string_alloc(const char *source);

char *join_string_n_alloc(const struct StringSliceList *list,
                          const char *postfix,
                          size_t postfix_len,
                          const char *prefix,
                          size_t prefix_len);

char *join_string_alloc(const struct StringSliceList *list,
                        const char *postfix,
                        const char *prefix);

char *remove_whitespace_n_alloc(const char *source, size_t source_len);

char *remove_whitespace_alloc(const char *source);

void delete_string_slice_list(struct StringSliceList *list);

#endif /* STRING_UTILS_ALLOC */

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STRING_UTILS_H_ */
