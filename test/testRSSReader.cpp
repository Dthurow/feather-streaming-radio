
#include "./unity/unity.h"
#include "../src/rssReader.h"
#include "testWifi.h"



void setUp(void)
{
    
}

void tearDown(void)
{
}

void test_goToThisText_should_readChars_until_FindGivenText(void)
{
    //arrange
    const char * text = "test";
    WiFiClient *client = new WiFiClient(text, 4);

    RSSReader rss = RSSReader(client);

    //act
    TEST_ASSERT_EQUAL(true, rss.goToThisText("es"));

    //assert
    TEST_ASSERT_EQUAL(3, client->index);
}

void test_goToThisText_should_returnFalse_when_CantFindGiventText(void)
{
    //arrange
    const char * text = "test";
    WiFiClient *client = new WiFiClient(text, 4);

    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(false, rss.goToThisText("ab"));
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_goToThisText_should_readChars_until_FindGivenText);
    RUN_TEST(test_goToThisText_should_returnFalse_when_CantFindGiventText);
    return UNITY_END();
}
