
#include "./unity/unity.h"
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))
#define BUFFER_MAX_SIZE 1000


void setUp(void)
{
    
}

void tearDown(void)
{
}

void test_first_test(void)
{
    TEST_IGNORE_MESSAGE("implement me!");
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_first_test);
    return UNITY_END();
}
