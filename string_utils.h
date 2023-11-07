/*
 * string_utils
 * Copyright (C) 2023 Andrey Kulenko
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef STRING_UTILS_H_
#define STRING_UTILS_H_

#define WHITESPACE_CHARS "\t\n\v\f\r "

#include <stddef.h> /* size_t */

struct str_slice {
    char *begin;
    size_t size;
};

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

char *next_line(struct str_slice *line);

char *lstrip_string_n(struct str_slice *str);
char *lstrip_string(const char *str, size_t *size);
size_t rstrip_string_n(const struct str_slice *str);
size_t rstrip_string(const char *str);
char *strip_string_n(struct str_slice *str);
char *strip_string(const char *str, size_t *size);

size_t split_string_n(const struct str_slice *str,
                      const char *pattern,
                      struct str_slice *list,
                      size_t list_max_size);
size_t split_string(const char *str,
                    const char *pattern,
                    struct str_slice *list,
                    size_t list_max_size);

size_t copy_string_n(char *dst,
                     const struct str_slice *src,
                     size_t dst_size,
                     ptrdiff_t offset);
size_t copy_string(char *dst,
                   const char *src,
                   size_t dst_size,
                   ptrdiff_t offset);

char *join_string_pre_p(char *dst,
                        size_t dst_size,
                        const struct str_slice *list,
                        size_t list_size,
                        const char *prefix,
                        const char *postfix,
                        size_t *len);
char *join_string_pre(char *dst,
                      size_t dst_size,
                      const struct str_slice *list,
                      size_t list_size,
                      const char *prefix,
                      size_t *len);
char *join_string_p(char *dst,
                    size_t dst_size,
                    const struct str_slice *list,
                    size_t list_size,
                    const char *postfix,
                    size_t *len);
char *join_string(char *dst,
                  size_t dst_size,
                  const struct str_slice *list,
                  size_t list_size,
                  size_t *len);

char *remove_whitespace_n(char *dst,
                          const struct str_slice *src,
                          size_t dst_size,
                          size_t *out_len);
char *remove_whitespace(char *dst,
                        const char *src,
                        size_t size,
                        size_t *out_len);

struct str_slice *split_string_n_alloc(const struct str_slice *str,
                                       const char *pattern,
                                       size_t *size);
struct str_slice *split_string_alloc(const char *str,
                                     const char *pattern,
                                     size_t *size);

char *join_string_pre_p_alloc(const struct str_slice *list,
                               size_t list_size,
                               const char *prefix,
                               const char *postfix);
char *join_string_pre_alloc(const struct str_slice *list,
                            size_t list_size,
                            const char *prefix);
char *join_string_p_alloc(const struct str_slice *list,
                           size_t list_size,
                           const char *postfix);
char *join_string_alloc(const struct str_slice *list, size_t list_size);

char *remove_whitespace_n_alloc(const struct str_slice *src);
char *remove_whitespace_alloc(const char *src);

char *copy_string_n_alloc(const struct str_slice *str);
char *copy_string_alloc(const char *str);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* STRING_UTILS_H_ */
