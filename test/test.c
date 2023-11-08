#include "./greatest/greatest.h"

#include "./split_string.h"
#include "./strip_string.h"

SUITE(split_string_test) {
        RUN_TEST(correct_list_size_for_splitting_with_null_list);
        RUN_TEST(correct_split);
        RUN_TEST(correct_split_beginning_separator);
        RUN_TEST(correct_split_ending_separator);
        RUN_TEST(correct_split_multiple_char_separator);
        RUN_TEST(correct_split_multiple_single_char_separator);
        RUN_TEST(correct_split_whitespace);
        RUN_TEST(correct_split_whitespace_beginning);
        RUN_TEST(correct_split_whitespace_ending);
        RUN_TEST(correct_whitespace_only_split);
        RUN_TEST(correct_string_slice_split);
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

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
        GREATEST_MAIN_BEGIN();

        RUN_SUITE(split_string_test);
        RUN_SUITE(strip_string_test);

        GREATEST_MAIN_END();
}
