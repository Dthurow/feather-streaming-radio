
#include "./unity/unity.h"
#include "../src/rssReader.h"
#include "./fakes/testWifi.h"
#include "testRSSReader.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_goToThisText_should_readChars_until_FindGivenText(void)
{
    //arrange
    const char *text = "test";
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
    const char *text = "test";
    WiFiClient *client = new WiFiClient(text, 4);

    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(false, rss.goToThisText("ab"));
}

void test_goToThisText_should_handleXML(void)
{

    //arrange
    WiFiClient *client = new WiFiClient(longXML, longXMLLength);

    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(true, rss.goToThisText("<enclosure"));

    //assert
    TEST_ASSERT_EQUAL(' ', client->read());
}

void test_readUntil_should_fillBufferUntilDelim(void)
{
    //arrange
    const char *text = "test";
    const char *expected = "te";
    char buffer[32];
    WiFiClient *client = new WiFiClient(text, 4);
    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(true, rss.readUntil(buffer, 32, 's'));

    for (int i = 0; expected[i] != '\0'; i++)
    {
        TEST_ASSERT_EQUAL(expected[i], buffer[i]);
    }
    TEST_ASSERT_EQUAL('\0', buffer[2]);
}

void test_readUntil_should_returnEmptyBufferAndFalse_when_DelimNotFound(void)
{

    //arrange
    const char *text = "12345678901234567890AndTestingAA";
    
    char buffer[32];
    WiFiClient *client = new WiFiClient(text, 32);
    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(false, rss.readUntil(buffer, 32, 'X'));

    TEST_ASSERT_EQUAL('\0', buffer[0]);
}

void test_readUntil_should_loopThroughBuffer_until_delimFound(void)
{
    //arrange
    const char *text = "12345678901234567890AndTestingX";
    const char *expected = "AndTesting";
    char buffer[11];
    WiFiClient *client = new WiFiClient(text, 31);
    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(true, rss.readUntil(buffer, 11, 'X'));

    for (int i = 0; expected[i] != '\0'; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(expected[i], buffer[i]);
    }
    TEST_ASSERT_EQUAL('\0', buffer[10]);
}

void test_getNextEpisode_should_returnURLfromXMLFeed(void){

    //arrange
    WiFiClient *client = new  WiFiClient(longXML, longXMLLength);

    RSSReader rss = RSSReader(client);
    const char *expected = "https://dts.podtrac.com/redirect.mp3/stitcher.simplecastaudio.com/3bb687b0-04af-4257-90f1-39eef4e631b6/episodes/6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc/audio/128/default.mp3?aid=rss_feed&awCollectionId=3bb687b0-04af-4257-90f1-39eef4e631b6&awEpisodeId=6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc&feed=BqbsxVfO";

    //act & assert
    char buffer[350];
    TEST_ASSERT_EQUAL(true, rss.getNextEpisode(buffer, 350));

    //assert
    for (int i = 0; expected[i] != '\0'; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(expected[i], buffer[i]);
    }
}

void test_getNextEpisode_should_returnEpisodeURLInOrder(void){

    //arrange
    WiFiClient *client = new  WiFiClient(longXML, longXMLLength);

    RSSReader rss = RSSReader(client);
    const char *expected = "https://dts.podtrac.com/redirect.mp3/stitcher.simplecastaudio.com/3bb687b0-04af-4257-90f1-39eef4e631b6/episodes/6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc/audio/128/default.mp3?aid=rss_feed&awCollectionId=3bb687b0-04af-4257-90f1-39eef4e631b6&awEpisodeId=6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc&feed=BqbsxVfO";

    //act & assert
    char buffer[350];
    TEST_ASSERT_EQUAL(true, rss.getNextEpisode(buffer, 350));

    //assert
    for (int i = 0; expected[i] != '\0'; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(expected[i], buffer[i]);
    }


    const char *expected1 = "https://dts.podtrac.com/redirect.mp3/stitcher.simplecastaudio.com/3bb687b0-04af-4257-90f1-39eef4e631b6/episodes/7bf56032-b2b7-4e7c-a767-ad4c6f890887/audio/128/default.mp3?aid=rss_feed&awCollectionId=3bb687b0-04af-4257-90f1-39eef4e631b6&awEpisodeId=7bf56032-b2b7-4e7c-a767-ad4c6f890887&feed=BqbsxVfO";

    //act & assert
    TEST_ASSERT_EQUAL(true, rss.getNextEpisode(buffer, 350));

    //assert
    for (int i = 0; expected1[i] != '\0'; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(expected1[i], buffer[i]);
    }
}


int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_goToThisText_should_readChars_until_FindGivenText);
    RUN_TEST(test_goToThisText_should_returnFalse_when_CantFindGiventText);
    RUN_TEST(test_goToThisText_should_handleXML);
    RUN_TEST(test_readUntil_should_fillBufferUntilDelim);
    RUN_TEST(test_readUntil_should_returnEmptyBufferAndFalse_when_DelimNotFound);
    RUN_TEST(test_readUntil_should_loopThroughBuffer_until_delimFound);
    RUN_TEST(test_getNextEpisode_should_returnURLfromXMLFeed);
    RUN_TEST(test_getNextEpisode_should_returnEpisodeURLInOrder);
    return UNITY_END();
}
