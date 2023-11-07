#include "./greatest/greatest.h"

#include "./split_string.h"

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

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
        GREATEST_MAIN_BEGIN();

        RUN_SUITE(split_string_test);

        GREATEST_MAIN_END();
}
