#include <stdio.h>
#include "unity.h"

void app_main(void)
{
    printf("Running tests with [Matrix] tag");
    UNITY_BEGIN();
    unity_run_tests_by_tag("[Matrix]", false);
//    unity_run_tests_by_tag("[Canvas]", false);
    UNITY_END();
}
