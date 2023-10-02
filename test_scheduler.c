#include "unity.h"
#include "scheduler.h"  // Replace "schedule.h" with the correct header file if needed

extern Task *tasks;  // Declare the tasks array as extern, to make sure the linker uses the one defined in your other C file.

void setUp(void) {
    // Initialize some tasks here, if needed
}

void tearDown(void) {
    // Clean up tasks here, if needed
}

void test_task1_priority(void) {
    TEST_ASSERT_EQUAL(1, tasks[0].priority);
}

void test_task2_priority(void) {
    TEST_ASSERT_EQUAL(2, tasks[1].priority);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_task1_priority);
    RUN_TEST(test_task2_priority);
    return UNITY_END();
}
