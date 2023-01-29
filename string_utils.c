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

#include "string_utils.h"

#define NON_WHITESPACE_LOOP(init_vars, string, string_len, iter_vars, body)\
{\
const char *begin, *end, *stripped;\
init_vars;\
string_len = string_length_n(string, string_len);\
stripped = lstrip_string_n(string, string_len);\
for (begin = stripped;\
     begin != NULL;\
     (iter_vars), begin = strpnbrk(end, WHITESPACE_CHARS))\
{\
    end = strpbrk(begin, WHITESPACE_CHARS);\
    if (end == NULL) {\
        end = string + string_len;\
    }\
    body\
}\
}

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

char *strpnbrk(const char *string, const char *accept)
{
    string += strspn(string, accept);
    return *string ? (char*)string : NULL;
}

size_t string_length_n(const char *string, size_t max_length)
{
    const char *null_char;

    if (string == NULL) return 0;

    null_char = (char*)memchr((void*)string, '\0', max_length + 1);
    if (null_char == NULL) return max_length;
    return null_char - string;
}

size_t string_length(const char *string)
{
    return string ? strlen(string) : 0;
}

const char *lstrip_string_n(const char *string, size_t max_string_len)
{
    const char *begin;

    if (string == NULL) return NULL;

    max_string_len = string_length_n(string, max_string_len);
    begin = string;

    string = strpnbrk(string, WHITESPACE_CHARS);
    if (string == NULL) return NULL;
    if (max_string_len > (size_t)(string - begin))
        begin = string;
    else
        begin = NULL;

    return begin;
}

const char *lstrip_string(const char *string)
{
    return lstrip_string_n(string, string_length(string));
}

const char *rstrip_string_n(const char *string, size_t max_string_len)
{
    const char *end_;

    if (string == NULL) return NULL;

    max_string_len = string_length_n(string, max_string_len);

    NON_WHITESPACE_LOOP(
        end_ = NULL, string, max_string_len, end_ = end,
        ;
    )

    return end_;
}

const char *rstrip_string(const char *string)
{
    return rstrip_string_n(string, string_length(string));
}

void strip_string_n(const char *string,
                    size_t string_len,
                    const char **begin,
                    const char **end)
{
    const char *result;
    size_t offset;

    result = lstrip_string_n(string, string_len);
    offset = result - string;
    result = rstrip_string_n(string + offset, string_len - offset);

    if (begin != NULL)
        *begin = string + offset;
    if (end != NULL)
        *end = result;
}

void strip_string(const char *string, const char **begin, const char **end)
{
    strip_string_n(string, string_length(string), begin, end);
}

size_t split_string_n(const char *string,
                      size_t string_len,
                      const char *pattern,
                      size_t pattern_len,
                      struct Slice *list,
                      size_t list_size)
{
    const char *begin;
    const char *end;
    size_t i;

    string_len = string_length_n(string, string_len);
    pattern_len = string_length_n(string, pattern_len);

    if (pattern_len == 0) return 0;

    for (begin = string, end = NULL, i = 0;
         end != string + string_len;
         begin = end + pattern_len, i++)
    {
        end = strstr(begin, pattern);
        if (end == NULL)
            end = string + string_len;
        if (list == NULL) continue;
        list[i].begin = begin - string;
        list[i].end = end - string;
        if (list_size == i + 1) break;
    }

    return i;
}

size_t split_string(const char *string,
                    const char *pattern,
                    struct Slice *list,
                    size_t list_size)
{
    return split_string_n(string,
                          string_length(string),
                          pattern,
                          string_length(pattern),
                          list,
                          list_size);
}

size_t split_string_whitespace_n(const char *string,
                                 size_t string_len,
                                 struct Slice *list,
                                 size_t list_size)
{
    size_t i;

    NON_WHITESPACE_LOOP(
        (i = 0), string, string_len, i++,
        if (list == NULL) continue;
        list[i].begin = begin - string;
        list[i].end = end - string;
        if (list_size == i + 1) break;
    )

    return i;
}

size_t split_string_whitespace(const char *string,
                               struct Slice *list,
                               size_t list_size)
{
    return split_string_whitespace_n(string,
                                     string_length(string),
                                     list,
                                     list_size);
}

size_t copy_string_n(char *dest,
                     const char *source,
                     size_t size,
                     size_t source_len,
                     ptrdiff_t dest_offset)
{
    size_t new_len;

    source_len = string_length_n(source, source_len);

    if (size == 0 || dest == NULL) return source_len;

    new_len = (source_len > size - 1) ? size - 1 : source_len;
    if (new_len > 0)
        memcpy(dest + dest_offset, source, new_len);

    return new_len;
}

size_t copy_string(char *dest,
                   const char *source,
                   size_t size,
                   ptrdiff_t dest_offset)
{
    return copy_string_n(dest,
                         source,
                         size,
                         string_length(source),
                         dest_offset);
}

size_t join_string_n(char *dest,
                     const struct Slices *list,
                     size_t size,
                     const char *postfix,
                     size_t postfix_len,
                     const char *prefix,
                     size_t prefix_len)
{
    size_t i;
    int j;

    if (list == NULL ||
        list->origin == NULL ||
        (dest == NULL && size > 0))
    {
        return 0;
    }

    postfix_len = string_length_n(postfix, postfix_len);
    prefix_len = string_length_n(postfix, postfix_len);
    j = 0;

    for (i = 0; i < list->size; i++) {
        if (prefix != NULL) {
            if (i == 0) continue;
            j += copy_string_n(dest, prefix, size ? size - j : 0, prefix_len, j);
        }
        j += copy_string_n(dest,
                           list->origin + list->data[i].begin,
                           size ? size - j : 0,
                           list->data[i].end - list->data[i].begin,
                           j);
        if (postfix != NULL) {
            if (i == list->size - 1) continue;
            j += copy_string_n(dest, postfix, size ? size - j : 0, postfix_len, j);
        }
    }

    if (dest != NULL)
        dest[j] = '\0';

    return j;
}

size_t join_string(char *dest,
                   const struct Slices *list,
                   size_t size,
                   const char *postfix,
                   const char *prefix)
{
    return join_string_n(dest,
                         list,
                         size,
                         postfix,
                         string_length(postfix),
                         prefix,
                         string_length(prefix));
}

size_t remove_whitespace_n(char *dest,
                           const char *source,
                           size_t size,
                           size_t source_len)
{
    size_t i;

    if (source_len > size - 1)
        source_len = size - 1;

    NON_WHITESPACE_LOOP(
        i = 0,
        source,
        source_len,
        i += copy_string_n(dest, begin, size ? size - i : 0, end - begin, i),
        ;
    )
    if (dest != NULL)
        dest[i] = '\0';

    return i;
}

size_t remove_whitespace(char *dest,
                         const char *source,
                         size_t size)
{
    return remove_whitespace_n(dest, source, size, string_length(source));
}

void delete_string_slice_list(struct Slices *list)
{
    free((void*)list->data);
    free((void*)list);
}

struct Slices *split_string_n_alloc(const char *string,
                                    size_t string_len,
                                    const char *pattern,
                                    size_t pattern_len)
{
    struct Slices *list;

    list = (struct Slices *)malloc(sizeof(struct Slices));
    list->origin = string;
    if (list == NULL) return NULL;
    list->origin = string;
    list->size = split_string_n(string,
                                string_len,
                                pattern,
                                pattern_len,
                                NULL,
                                0);
    if (list->size == 0) {
        free((void*)list);
        return NULL;
    }
    list->data = (struct Slice*)malloc(list->size * sizeof(struct Slice));
    if (list->data == NULL) {
        delete_string_slice_list(list);
        return NULL;
    }

    split_string_n(string,
                   string_len,
                   pattern,
                   pattern_len,
                   list->data,
                   list->size);
    return list;
}

struct Slices *split_string_alloc(const char *string,
                                  const char *pattern)
{
    return split_string_n_alloc(string,
                                string_length(string),
                                pattern,
                                string_length(pattern));
}

struct Slices *split_string_whitespace_n_alloc(const char *string,
                                               size_t string_len)
{
    struct Slices *list;

    list = (struct Slices*)malloc(sizeof(struct Slices));
    if (list == NULL) return NULL;
    list->origin = string;
    list->size = split_string_whitespace_n(string, string_len, NULL, 0);
    if (list->size == 0) {
        free((void*)list);
        return NULL;
    }

    list->data = (struct Slice*)malloc(list->size * sizeof(struct Slice));
    if (list->data == NULL) {
        delete_string_slice_list(list);
        return NULL;
    }
    split_string_whitespace_n(string, string_len, list->data, list->size);
    return list;
}

struct Slices *split_string_whitespace_alloc(const char *string)
{
    return split_string_whitespace_n_alloc(string, string_length(string));
}

char *copy_string_n_alloc(const char *source, size_t source_len)
{
    char *new_string;
    size_t new_string_len;

    new_string_len = string_length_n(source, source_len);
    new_string = (char*)malloc(new_string_len + 1);
    if (new_string == NULL) return NULL;
    memcpy(new_string, source, new_string_len);
    new_string[new_string_len] = '\0';

    return new_string;
}

char *copy_string_alloc(const char *source)
{
    return copy_string_n_alloc(source, string_length(source));
}

char *join_string_n_alloc(const struct Slices *list,
                          const char *postfix,
                          size_t postfix_len,
                          const char *prefix,
                          size_t prefix_len)
{
    char *new_string;
    size_t new_string_len;

    new_string_len = join_string_n(NULL,
                                   list,
                                   0,
                                   postfix,
                                   postfix_len,
                                   prefix,
                                   prefix_len);
    new_string = (char*)malloc(new_string_len + 1);
    if (new_string == NULL) return NULL;
    join_string_n(new_string,
                  list,
                  new_string_len + 1,
                  postfix,
                  postfix_len,
                  prefix,
                  prefix_len);
    return new_string;
}

char *join_string_alloc(const struct Slices *list,
                        const char *postfix,
                        const char *prefix)
{
    return join_string_n_alloc(list,
                               postfix,
                               string_length(postfix),
                               prefix,
                               string_length(prefix));
}

char *remove_whitespace_n_alloc(const char *source, size_t source_len)
{
    char *new_string;
    size_t new_string_len;

    new_string_len = remove_whitespace_n(NULL, source, 0, source_len);
    new_string = (char*)malloc(new_string_len + 1);
    if (new_string == NULL) return NULL;
    remove_whitespace_n(new_string, source, new_string_len + 1, source_len);

    return new_string;
}

char *remove_whitespace_alloc(const char *source)
{
    return remove_whitespace_n_alloc(source, string_length(source));
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
