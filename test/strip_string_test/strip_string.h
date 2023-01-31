static const char string[] = "    \v\n\n  a   hello\r\n   \nasdase\ts\ndasf     \r\n";

TEST correct_lstrip(void)
{
        const char * const result = lstrip_string_n(string + 10,
                                                    sizeof(string) - 11);

        ASSERT_EQ('h', *result);        
        PASS();
}

TEST correct_whitespace_only_lstrip(void)
{
        const char * const result = lstrip_string_n(string, 6);

        ASSERT_EQ(NULL, result);
        PASS();
}

TEST unchanged_result_for_lstrip(void)
{
        const char * const result = lstrip_string_n(string + 9, 7);

        ASSERT_EQ('a', *result);
        PASS();
}

TEST zero_lengthed_lstrip(void)
{
        const char * const result = lstrip_string_n(string, 0);

        ASSERT_EQ(NULL, result);
        PASS();
}

TEST correct_rstrip(void)
{
        const char * const result = rstrip_string_n(string + 24, 7);

        ASSERT_EQ('e', *(result - 1));
        PASS();
}

TEST correct_whitespace_only_rstrip(void)
{
        const char * const result = rstrip_string_n(string + 4, 3);

        ASSERT_EQ(NULL, result);
        PASS();
}

TEST unchanged_result_for_rstrip(void)
{
        const char * const result = rstrip_string_n(string + 33, 4);

        ASSERT_EQ('f', *(result - 1));
        PASS();
}

TEST zero_lengthed_rstrip(void)
{
        const char * const result = rstrip_string_n(string, 0);

        ASSERT_EQ(NULL, result);
        PASS();
}

SUITE(strip_string_test) {
        RUN_TEST(correct_lstrip);
        RUN_TEST(correct_whitespace_only_lstrip);
        RUN_TEST(unchanged_result_for_lstrip);
        RUN_TEST(zero_lengthed_lstrip);
        RUN_TEST(correct_rstrip);
        RUN_TEST(correct_whitespace_only_rstrip);
        RUN_TEST(unchanged_result_for_rstrip);
        RUN_TEST(zero_lengthed_rstrip);
}
