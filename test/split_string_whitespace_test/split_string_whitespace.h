TEST correct_list_size_for_null_list_for_split_string_whitespace(void)
{
        const char to_split[] = "      \t\tone    two   three  \v\fa\nbc  d\n\t   ";
        size_t actual_size;

        actual_size = split_string_whitespace_n(to_split, sizeof(to_split) - 1,
                                                NULL, 0);

        ASSERT_EQ(actual_size, 6);
        PASS();
}

TEST correct_split_whitespace(void)
{
        const char to_split[] = "foo\n   \t\v\fbar  \n  baz";
        struct Slice elements[3];
        size_t actual_size;

        actual_size = split_string_whitespace_n(to_split, sizeof(to_split) - 1,
                                                elements, 3);

        ASSERT_EQ(actual_size, 3);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 3);
        ASSERT_EQ(elements[1].begin, 10);
        ASSERT_EQ(elements[1].end, 13);
        ASSERT_EQ(elements[2].begin, 18);
        ASSERT_EQ(elements[2].end, 21);
        PASS();
}

TEST correct_split_whitespace_beginning(void)
{
        const char to_split[] = "\r\n    hello world";
        struct Slice elements[2];
        size_t actual_size;

        actual_size = split_string_whitespace_n(to_split, sizeof(to_split) - 1,
                                                elements, 2);

        ASSERT_EQ(actual_size, 2);
        ASSERT_EQ(elements[0].begin, 6);
        ASSERT_EQ(elements[0].end, 11);
        ASSERT_EQ(elements[1].begin, 12);
        ASSERT_EQ(elements[1].end, 17);
        PASS();
}

TEST correct_split_whitespace_ending(void)
{
        const char to_split[] = "hello world   \r\n";
        struct Slice elements[2];
        size_t actual_size;

        actual_size = split_string_whitespace_n(to_split, sizeof(to_split) - 1,
                                                elements, 2);

        ASSERT_EQ(actual_size, 2);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 5);
        ASSERT_EQ(elements[1].begin, 6);
        ASSERT_EQ(elements[1].end, 11);
        PASS();
}

TEST correct_whitespace_only_split_whitespace(void)
{
        const char to_split[] = "\n\n\f\f\v\v\r\r\t\t  ";
        struct Slice element;
        size_t actual_size;

        actual_size = split_string_whitespace_n(to_split, sizeof(to_split) - 1,
                                                &element, 1);

        /* element will not be assigned */
        ASSERT_EQ(actual_size, 0);
        PASS();
}

SUITE(split_string_whitespace_test) {
        RUN_TEST(correct_list_size_for_null_list_for_split_string_whitespace);
        RUN_TEST(correct_split_whitespace);
        RUN_TEST(correct_split_whitespace_beginning);
        RUN_TEST(correct_split_whitespace_ending);
        RUN_TEST(correct_whitespace_only_split_whitespace);
}
