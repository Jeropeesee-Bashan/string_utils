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

#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

char *next_line(struct str_slice *line)
{
    const char *end;

    if (line == NULL)
        return NULL;

    line->begin += line->size + 1;
    if (!strncmp(line->begin - 1, "\r\n", 2))
        line->begin += 1;
    end = strchr(line->begin, '\n');
    line->size = end ? (size_t)(end - line->begin) : 0;
    if (line->size && line->begin[line->size - 1] == '\r')
        line->size -= 1;

    return end ? line->begin : NULL;
}

struct str_slice *copy_slice(struct str_slice *dst, const struct str_slice *src)
{
    if (dst == NULL || src == NULL)
        return NULL;

    return (struct str_slice *)memcpy((void*)dst, (const void*)src,
                                      sizeof(struct str_slice));
}

char *lstrip_string_n(struct str_slice *str)
{
    size_t delta;

    if (str == NULL)
        return NULL;

    delta = strspn(str->begin, WHITESPACE_CHARS);
    if (delta > str->size) {
        str->begin += str->size;
        str->size = 0;
    } else {
        str->begin += delta;
        str->size -= delta;
    }

    return str->begin;
}

char *lstrip_string(const char *str, size_t *size)
{
    struct str_slice slice;
    char *result;

    if (str == NULL)
        return NULL;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    result = lstrip_string_n(&slice);
    if (size)
        *size = slice.size;
    return result;
}

size_t rstrip_string_n(const struct str_slice *str)
{
    size_t size;

    if (str == NULL)
        return 0;

    size = str->size;
    while (size && isspace(str->begin[size - 1]))
        size -= 1;

    return size;
}

size_t rstrip_string(const char *str)
{
    struct str_slice slice;

    if (str == NULL)
        return 0;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    return rstrip_string_n(&slice);
}

char *strip_string_n(struct str_slice *str)
{
    if (str == NULL)
        return NULL;

    str->begin = lstrip_string_n(str);
    str->size = rstrip_string_n(str);

    return str->begin;
}

char *strip_string(const char *str, size_t *size)
{
    struct str_slice slice;
    char *result;

    if (str == NULL || size == NULL)
        return NULL;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    result = strip_string_n(&slice);
    *size = slice.size;
    return result;
}

size_t split_string_n(const struct str_slice *str,
                      const char *pattern,
                      struct str_slice *list,
                      size_t list_max_size)
{
    struct str_slice str_;
    const char *l, *r;
    size_t pattern_len, count, spn;
    unsigned char end;

    if (str == NULL)
        return 0;

    if (pattern)
        pattern_len = strlen(pattern);

    memcpy((void*)&str_, (const void*)str, sizeof(struct str_slice));

    l = pattern ? str_.begin : strip_string_n(&str_);

    if (str_.size == 0)
        return 0;

    end = 0;
    count = 0;
    while (!end) {
        r = pattern ? strstr(l, pattern) : strpbrk(l, WHITESPACE_CHARS);

        if (r)
            spn = pattern ? pattern_len : strspn(r, WHITESPACE_CHARS);

        if (r && r + spn > str_.begin + str_.size) {
            r = pattern ? str_.begin + str_.size : r;
            end = 1;
        }

        if (!r) {
            r = str_.begin + str_.size;
            end = 1;
        }

        if (list && count < list_max_size) {
            list[count].begin = (char*)l;
            list[count].size = r - l;
        }

        if (r && !end)
            l = r + spn;

        count += 1;
    }

    return count;
}

size_t split_string(const char *str,
                    const char *pattern,
                    struct str_slice *list,
                    size_t list_max_size)
{
    struct str_slice slice;

    if (str == NULL)
        return 0;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    return split_string_n(&slice, pattern, list, list_max_size);
}

size_t copy_string_n(char *dst,
                     const struct str_slice *src,
                     size_t dst_size,
                     ptrdiff_t offset)
{
    struct str_slice src_;

    if (src == NULL || (dst && dst_size == 0))
        return 0;

    memcpy((void*)&src_, (const void*)src, sizeof(struct str_slice));

    if (offset + src_.size > dst_size - 1)
        src_.size = dst_size - offset - 1;

    if (dst)
        strncpy(dst + offset, src_.begin, src_.size);

    return src_.size;
}

size_t copy_string(char *dst,
                   const char *src,
                   size_t dst_size,
                   ptrdiff_t offset)
{
    struct str_slice slice;

    if (src == NULL)
        return 0;

    slice.begin = (char*)src;
    slice.size = strlen(src);

    return copy_string_n(dst, &slice, dst_size, offset);
}

char *join_string_pre_p(char *dst,
                        size_t dst_size,
                        const struct str_slice *list,
                        size_t list_size,
                        const char *prefix,
                        const char *postfix,
                        size_t *len)
{
    struct str_slice prefix_, postfix_;
    char *ptr;
    size_t i;
    ptrdiff_t offset;

    if (list == NULL)
        return NULL;

    if (prefix) {
        prefix_.begin = (char*)prefix;
        prefix_.size = strlen(prefix);
    }
    if (postfix) {
        postfix_.begin = (char*)postfix;
        postfix_.size = strlen(postfix);
    }

    for (ptr = dst, i = 0; i < list_size; i++) {
        offset = ptr - dst;
        if (prefix && i > 0)
            ptr += copy_string_n(dst, &prefix_, dst_size, offset);
        ptr += copy_string_n(dst, list + i, dst_size, offset);
        if (postfix && i < list_size - 1)
            ptr += copy_string_n(dst, &postfix_, dst_size, offset);
    }

    *ptr = '\0';
    if (len)
        *len = ptr - dst;
    return dst;
}

char *join_string_pre(char *dst,
                      size_t dst_size,
                      const struct str_slice *list,
                      size_t list_size,
                      const char *prefix,
                      size_t *len)
{
    return join_string_pre_p(dst, dst_size, list, list_size, prefix, NULL, len);
}

char *join_string_p(char *dst,
                    size_t dst_size,
                    const struct str_slice *list,
                    size_t list_size,
                    const char *postfx,
                    size_t *len)
{
    return join_string_pre_p(dst, dst_size, list, list_size, NULL, postfx, len);
}

char* join_string(char *dst,
                  size_t dst_size,
                  const struct str_slice *list,
                  size_t list_size,
                  size_t *len)
{
    return join_string_pre_p(dst, dst_size, list, list_size, NULL, NULL, len);
}

char *remove_whitespace_n(char *dst,
                          const struct str_slice *src,
                          size_t dst_size,
                          size_t *len)
{
    struct str_slice src_, part;
    const char *l, *r;
    size_t spn, idx;
    unsigned char end;

    if (src == NULL)
        return NULL;

    memcpy((void*)&src_, (const void*)src, sizeof(struct str_slice));

    idx = 0;
    end = 0;
    l = strip_string_n(&src_);
    while (!end) {
        r = strpbrk(l, WHITESPACE_CHARS);

        if (r)
            spn = strspn(r, WHITESPACE_CHARS);

        if (r && r + spn > src_.begin + src_.size)
            end = 1;

        if (!r) {
            r = src_.begin + src_.size;
            end = 1;
        }

        part.begin = (char*)l;
        part.size = r - l;
        idx += copy_string_n(dst, &part, dst_size, idx);

        if (r && !end)
            l = r + spn;
    }

    dst[idx] = '\0';

    if (len)
        *len = idx;
    return dst;
}

char *remove_whitespace(char *dst,
                        const char *src,
                        size_t dst_size,
                        size_t *len)
{
    struct str_slice slice;

    if (src == NULL)
        return NULL;

    slice.begin = (char*)src;
    slice.size = strlen(src);

    return remove_whitespace_n(dst, &slice, dst_size, len);
}

struct str_slice *split_string_n_alloc(const struct str_slice *str,
                                       const char *pattern,
                                       size_t *size)
{
    struct str_slice *result;
    size_t size_;

    if (str == NULL || size == NULL)
        return NULL;

    size_ = split_string_n(str, pattern, NULL, 0);
    if (size_ == 0)
        return NULL;

    result = (struct str_slice*)malloc(size_ * sizeof(struct str_slice));
    if (result == NULL)
        return NULL;

    *size = split_string_n(str, pattern, result, size_);
    return result;
}

struct str_slice *split_string_alloc(const char *str,
                                     const char *pattern,
                                     size_t *size)
{
    struct str_slice slice;

    if (str == NULL)
        return NULL;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    return split_string_n_alloc(&slice, pattern, size);
}

char *join_string_pre_p_alloc(const struct str_slice *list,
                               size_t list_size,
                               const char *pre,
                               const char *post)
{
    char *result;
    size_t len;

    if (list == NULL)
        return NULL;

    join_string_pre_p(NULL, 0, list, list_size, pre, post, &len);
    result = (char*)malloc(len + 1);
    if (result == NULL)
        return NULL;

    return join_string_pre_p(result, len + 1, list, list_size, pre, post, NULL);
}

char *join_string_pre_alloc(const struct str_slice *list,
                            size_t list_size,
                            const char *prefix)
{
    return join_string_pre_p_alloc(list, list_size, prefix, NULL);
}

char *join_string_p_alloc(const struct str_slice *list,
                           size_t list_size,
                           const char *postfix)
{
    return join_string_pre_p_alloc(list, list_size, NULL, postfix);
}

char *join_string_alloc(const struct str_slice *list, size_t list_size)
{
    return join_string_pre_p_alloc(list, list_size, NULL, NULL);
}

char *remove_whitespace_n_alloc(const struct str_slice *src)
{
    char *result;
    size_t len;

    if (src == NULL)
        return NULL;

    remove_whitespace_n(NULL, src, 0, &len);

    result = (char*)malloc(len + 1);
    if (result == NULL)
        return NULL;

    return remove_whitespace_n(result, src, len + 1, NULL);
}

char *remove_whitespace_alloc(const char *src)
{
    struct str_slice slice;

    if (src == NULL)
        return NULL;

    slice.begin = (char*)src;
    slice.size = strlen(src);

    return remove_whitespace_n_alloc(&slice);
}

char *copy_string_n_alloc(const struct str_slice *str)
{
    char *result;
    size_t len;

    if (str == NULL)
        return NULL;

    len = copy_string_n(NULL, str, 0, 0);
    result = (char*)malloc(len + 1);
    if (result == NULL)
        return NULL;

    copy_string_n(result, str, len + 1, 0);
    result[len] = '\0';

    return result;
}

char *copy_string_alloc(const char *str)
{
    struct str_slice slice;

    if (str == NULL)
        return NULL;

    slice.begin = (char*)str;
    slice.size = strlen(str);

    return copy_string_n_alloc(&slice);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */
