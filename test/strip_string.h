#ifndef STRIP_STRING_H_
#define STRIP_STRING_H_

#include "./greatest/greatest.h"

#include "../string_utils.h"

static const char string[] = "    \v\n\n  a   hello\r\n   \nasdase\ts\ndasf     \r\n";

TEST correct_lstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string + 10;
        slice.size = sizeof(string) - 11;
        slice.begin = lstrip_string_n(&slice);

        ASSERT_EQ('h', *slice.begin);
        ASSERT_EQ(slice.size, sizeof(string) - 14);
        PASS();
}

TEST correct_whitespace_only_lstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string;
        slice.size = 6;
        slice.begin = lstrip_string_n(&slice);

        ASSERT_EQ(slice.size, 0);
        PASS();
}

TEST unchanged_result_for_lstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string + 9;
        slice.size = 7;
        slice.begin = lstrip_string_n(&slice);

        ASSERT_EQ(slice.begin, string + 9);
        ASSERT_EQ(slice.size, 7);
        PASS();
}

TEST zero_lengthed_lstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string;
        slice.size = 0;
        slice.begin = lstrip_string_n(&slice);

        ASSERT_EQ(slice.begin, string);
        ASSERT_EQ(slice.size, 0);
        PASS();
}

TEST correct_rstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string + 24;
        slice.size = 7;
        slice.size = rstrip_string_n(&slice);

        ASSERT_EQ(slice.begin, string + 24);
        ASSERT_EQ(slice.size, 6);
        PASS();
}

TEST correct_whitespace_only_rstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string + 4;
        slice.size = 3;
        slice.size = rstrip_string_n(&slice);

        ASSERT_EQ(slice.size, 0);
        PASS();
}

TEST unchanged_result_for_rstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string + 33;
        slice.size = 4;
        slice.size = rstrip_string_n(&slice);

        ASSERT_EQ(slice.begin, string + 33);
        ASSERT_EQ(slice.size, 4);
        PASS();
}

TEST zero_lengthed_rstrip(void)
{
        struct str_slice slice;

        slice.begin = (char*)string;
        slice.size = 0;
        slice.size = rstrip_string_n(&slice);

        ASSERT_EQ(slice.begin, string);
        ASSERT_EQ(slice.size, 0);
        PASS();
}

#endif /* STRIP_STRING_H_ */
