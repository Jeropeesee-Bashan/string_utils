#ifndef SPLIT_STRING_H_
#define SPLIT_STRING_H_

#include "./greatest/greatest.h"

#include "../string_utils.h"

TEST correct_split(void)
{
    const char to_split[] = "one,two,three";
    struct str_slice elements[3];
    size_t actual_size;

    actual_size = split_string(to_split, ",", elements, 3);

    ASSERT_EQ(actual_size, 3);
    ASSERT_EQ(elements[0].begin, to_split);
    ASSERT_EQ(elements[0].size, 3);
    ASSERT_EQ(elements[1].begin, to_split + 4);
    ASSERT_EQ(elements[1].size, 3);
    ASSERT_EQ(elements[2].begin, to_split + 8);
    ASSERT_EQ(elements[2].size, 5);
    PASS();
}

TEST correct_list_size_for_splitting_with_null_list(void)
{
    const char to_split[] = "This|is|a|long|line|we|are|going|to|split";
    size_t actual_size;

    actual_size = split_string(to_split, "|", NULL, 0);

    ASSERT_EQ(actual_size, 10);
    PASS();
}

TEST correct_split_beginning_separator(void)
{
        const char to_split[] = "_one_two_three";
        struct str_slice elements[4];
        size_t actual_size;

        actual_size = split_string(to_split, "_", elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 0);
        ASSERT_EQ(elements[1].begin, to_split + 1);
        ASSERT_EQ(elements[1].size, 3);
        ASSERT_EQ(elements[2].begin, to_split + 5);
        ASSERT_EQ(elements[2].size, 3);
        ASSERT_EQ(elements[3].begin, to_split + 9);
        ASSERT_EQ(elements[3].size, 5);
        PASS();
}

TEST correct_split_ending_separator(void)
{
        const char to_split[] = "one_two_three_";
        struct str_slice elements[4];
        size_t actual_size;

        actual_size = split_string(to_split, "_", elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 3);
        ASSERT_EQ(elements[1].begin, to_split + 4);
        ASSERT_EQ(elements[1].size, 3);
        ASSERT_EQ(elements[2].begin, to_split + 8);
        ASSERT_EQ(elements[2].size, 5);
        ASSERT_EQ(elements[3].begin, to_split + 14);
        ASSERT_EQ(elements[3].size, 0);
        PASS();
}

TEST correct_split_multiple_char_separator(void)
{
        const char to_split[] = " hjskhf skbasxxf sbdfxkbasiuxhe sdfxcbascvb";
        struct str_slice elements[4];
        size_t actual_size;

        actual_size = split_string(to_split, "bas", elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 10);
        ASSERT_EQ(elements[1].begin, to_split + 13);
        ASSERT_EQ(elements[1].size, 10);
        ASSERT_EQ(elements[2].begin, to_split + 26);
        ASSERT_EQ(elements[2].size, 11);
        ASSERT_EQ(elements[3].begin, to_split + 40);
        ASSERT_EQ(elements[3].size, 3);
        PASS();
}

TEST correct_split_multiple_single_char_separator(void)
{
        const char to_split[] = "  one two   three     four   ";
        struct str_slice elements[4];
        size_t actual_size;

        actual_size = split_string(to_split, "   ", elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 9);
        ASSERT_EQ(elements[1].begin, to_split + 12);
        ASSERT_EQ(elements[1].size, 5);
        ASSERT_EQ(elements[2].begin, to_split + 20);
        ASSERT_EQ(elements[2].size, 6);
        ASSERT_EQ(elements[3].begin, to_split + 29);
        ASSERT_EQ(elements[3].size, 0);
        PASS();
}

TEST correct_split_whitespace(void)
{
        const char to_split[] = "foo\n   \t\v\fbar  \n  baz";
        struct str_slice elements[3];
        size_t actual_size;

        actual_size = split_string(to_split, NULL, elements, 3);

        ASSERT_EQ(actual_size, 3);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 3);
        ASSERT_EQ(elements[1].begin, to_split + 10);
        ASSERT_EQ(elements[1].size, 3);
        ASSERT_EQ(elements[2].begin, to_split + 18);
        ASSERT_EQ(elements[2].size, 3);
        PASS();
}

TEST correct_split_whitespace_beginning(void)
{
        const char to_split[] = "\r\n    hello world";
        struct str_slice elements[2];
        size_t actual_size;

        actual_size = split_string(to_split, NULL, elements, 2);

        ASSERT_EQ(actual_size, 2);
        ASSERT_EQ(elements[0].begin, to_split + 6);
        ASSERT_EQ(elements[0].size, 5);
        ASSERT_EQ(elements[1].begin, to_split + 12);
        ASSERT_EQ(elements[1].size, 5);
        PASS();
}

TEST correct_split_whitespace_ending(void)
{
        const char to_split[] = "hello world   \r\n";
        struct str_slice elements[2];
        size_t actual_size;

        actual_size = split_string(to_split, NULL, elements, 2);

        ASSERT_EQ(actual_size, 2);
        ASSERT_EQ(elements[0].begin, to_split);
        ASSERT_EQ(elements[0].size, 5);
        ASSERT_EQ(elements[1].begin, to_split + 6);
        ASSERT_EQ(elements[1].size, 5);
        PASS();
}

TEST correct_whitespace_only_split(void)
{
        const char to_split[] = "\n\n\f\f\v\v\r\r\t\t  ";
        struct str_slice element = {0};
        size_t actual_size;

        actual_size = split_string(to_split, NULL, &element, 1);

        /* element will not be assigned */
        ASSERT_EQ(element.begin, NULL);
        ASSERT_EQ(element.size, 0);
        ASSERT_EQ(actual_size, 0);
        PASS();
}

TEST correct_string_slice_split(void)
{
    const char to_split[] = "junkjunkJuNkJU,  NK  ,  lol,  ol,  junkJUNKjuNK";
    struct str_slice slice;
    struct str_slice elements[3];
    size_t actual_size;

    slice.begin = (char*)to_split + 21;
    slice.size = 13;

    actual_size = split_string_n(&slice, ",  ", elements, 3);

    ASSERT_EQ(actual_size, 3);
    ASSERT_EQ(elements[0].begin, to_split + 21);
    ASSERT_EQ(elements[0].size, 0);
    ASSERT_EQ(elements[1].begin, to_split + 24);
    ASSERT_EQ(elements[1].size, 3);
    ASSERT_EQ(elements[2].begin, to_split + 30);
    ASSERT_EQ(elements[2].size, 4);
    PASS();
}

#endif /* SPLIT_STRING_H_ */
