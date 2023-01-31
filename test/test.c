#include <greatest.h>
#include <string_utils.h>

#include "strip_string_test/strip_string.h"
#include "split_string_test/split_string.h"
#include "split_string_whitespace_test/split_string_whitespace.h"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
        GREATEST_MAIN_BEGIN();

        RUN_SUITE(strip_string_test);
        RUN_SUITE(split_string_test);
        RUN_SUITE(split_string_whitespace_test);

        GREATEST_MAIN_END();
}
