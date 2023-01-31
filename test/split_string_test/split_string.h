TEST correct_split(void)
{
        const char to_split[] = "one,two,three";
        struct Slice elements[3];
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     ",", 1, elements, 3);
        ASSERT_EQ(actual_size, 3);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 3);
        ASSERT_EQ(elements[1].begin, 4);
        ASSERT_EQ(elements[1].end, 7);
        ASSERT_EQ(elements[2].begin, 8);
        ASSERT_EQ(elements[2].end, 13);
        PASS();
}

TEST correct_list_size_for_null_list(void)
{
        const char to_split[] = "This|is|a|long|line|we|are|going|to|split";
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     "|", 1, NULL, 0);

        ASSERT_EQ(actual_size, 10);
        PASS();
}

TEST correct_split_beginning_separator(void)
{
        const char to_split[] = "_one_two_three";
        struct Slice elements[4];
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     "_", 1, elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 0);
        ASSERT_EQ(elements[1].begin, 1);
        ASSERT_EQ(elements[1].end, 4);
        ASSERT_EQ(elements[2].begin, 5);
        ASSERT_EQ(elements[2].end, 8);
        ASSERT_EQ(elements[3].begin, 9);
        ASSERT_EQ(elements[3].end, 14);
        PASS();
}

TEST correct_split_ending_separator(void)
{
        const char to_split[] = "one_two_three_";
        struct Slice elements[4];
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     "_", 1, elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 3);
        ASSERT_EQ(elements[1].begin, 4);
        ASSERT_EQ(elements[1].end, 7);
        ASSERT_EQ(elements[2].begin, 8);
        ASSERT_EQ(elements[2].end, 13);
        ASSERT_EQ(elements[3].begin, 14);
        ASSERT_EQ(elements[3].end, 14);
        PASS();
}

TEST correct_split_multiple_char_separator(void)
{
        const char to_split[] = " hjskhf skbasxxf sbdfxkbasiuxhe sdfxcbascvb";
        struct Slice elements[4];
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     "bas", 3, elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 10);
        ASSERT_EQ(elements[1].begin, 13);
        ASSERT_EQ(elements[1].end, 23);
        ASSERT_EQ(elements[2].begin, 26);
        ASSERT_EQ(elements[2].end, 37);
        ASSERT_EQ(elements[3].begin, 40);
        ASSERT_EQ(elements[3].end, 43);
        PASS();
}

TEST correct_split_multiple_single_char_separator(void)
{
        const char to_split[] = "  one two   three     four   ";
        struct Slice elements[4];
        size_t actual_size;

        actual_size = split_string_n(to_split, sizeof(to_split) - 1,
                                     "   ", 3, elements, 4);

        ASSERT_EQ(actual_size, 4);
        ASSERT_EQ(elements[0].begin, 0);
        ASSERT_EQ(elements[0].end, 9);
        ASSERT_EQ(elements[1].begin, 12);
        ASSERT_EQ(elements[1].end, 17);
        ASSERT_EQ(elements[2].begin, 20);
        ASSERT_EQ(elements[2].end, 26);
        ASSERT_EQ(elements[3].begin, 29);
        ASSERT_EQ(elements[3].end, 29);
        PASS();
}

SUITE(split_string_test) {
        RUN_TEST(correct_list_size_for_null_list);
        RUN_TEST(correct_split);
        RUN_TEST(correct_split_beginning_separator);
        RUN_TEST(correct_split_ending_separator);
        RUN_TEST(correct_split_multiple_char_separator);
        RUN_TEST(correct_split_multiple_single_char_separator);
}
