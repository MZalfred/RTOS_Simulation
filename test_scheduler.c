#include "unity.h"
#include "schedule.h"

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
