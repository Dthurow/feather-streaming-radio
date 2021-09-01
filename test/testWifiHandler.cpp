
#include "./unity/unity.h"
#include "../src/wifiHandler.h"
#include "./header_overrides/ESP8266WiFi.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_getHost_should_removeHTTP(void)
{
    //arrange
    TEST_IGNORE_MESSAGE("IMPLEMENT ME");

    //act & assert
   
}

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_getHost_should_removeHTTP);
    return UNITY_END();
}