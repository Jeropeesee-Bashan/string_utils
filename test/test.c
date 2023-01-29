#include <greatest.h>
#include <string_utils.h>

#include "strip_string_test/strip_string.h"

GREATEST_MAIN_DEFS();

int main(int argc, char *argv[])
{
        GREATEST_MAIN_BEGIN();

        RUN_SUITE(strip_string_test);

        GREATEST_MAIN_END();
}
