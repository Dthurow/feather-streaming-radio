
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
    const char *longXML = R"(<rss xmlns:atom="http://www.w3.org/2005/Atom" xmlns:content="http://purl.org/rss/1.0/modules/content/" xmlns:googleplay="http://www.google.com/schemas/play-podcasts/1.0" xmlns:itunes="http://www.itunes.com/dtds/podcast-1.0.dtd" version="2.0">
<channel>
<atom:link href="https://feeds.simplecast.com/BqbsxVfO" rel="self" title="MP3 Audio" type="application/atom+xml"/>
<atom:link xmlns="http://www.w3.org/2005/Atom" href="https://simplecast.superfeedr.com/" rel="hub"/>
<generator>https://simplecast.com</generator>
<title>99% Invisible</title>
<description>Design is everywhere in our lives, perhaps most importantly in the places where we've just stopped noticing. 99% Invisible is a weekly exploration of the process and power of design and architecture. From award winning producer Roman Mars. Learn more at 99percentinvisible.org.</description>
<copyright>Copyright © 2017 Roman Mars. All rights reserved.</copyright>
<language>en-us</language>
<pubDate>Tue, 17 Aug 2021 22:47:20 +0000</pubDate>
<lastBuildDate>Tue, 17 Aug 2021 22:47:37 +0000</lastBuildDate>
<image>
<link>https://99percentinvisible.org</link>
<title>99% Invisible</title>
<url>https://image.simplecastcdn.com/images/5b7d8c77-15ba-4eff-a999-2e725db21db5/c43e134f-15e6-41ae-9a2e-5e57cf761473/3000x3000/stitcher-cover-99percentinvisible-3000x3000-r2021-final.jpg?aid=rss_feed</url>
</image>
<link>https://99percentinvisible.org</link>
<itunes:type>episodic</itunes:type>
<itunes:summary>Design is everywhere in our lives, perhaps most importantly in the places where we've just stopped noticing. 99% Invisible is a weekly exploration of the process and power of design and architecture. From award winning producer Roman Mars. Learn more at 99percentinvisible.org.</itunes:summary>
<itunes:author>Roman Mars</itunes:author>
<itunes:explicit>no</itunes:explicit>
<itunes:image href="https://image.simplecastcdn.com/images/5b7d8c77-15ba-4eff-a999-2e725db21db5/c43e134f-15e6-41ae-9a2e-5e57cf761473/3000x3000/stitcher-cover-99percentinvisible-3000x3000-r2021-final.jpg?aid=rss_feed"/>
<itunes:new-feed-url>https://feeds.99percentinvisible.org/99percentinvisible</itunes:new-feed-url>
<itunes:owner>
<itunes:name>Roman Mars</itunes:name>
<itunes:email>roman@99pi.org</itunes:email>
</itunes:owner>
<itunes:category text="Arts">
<itunes:category text="Design"/>
</itunes:category>
<item>
<guid isPermaLink="false">32057125-c218-43f6-90a1-b9488e0dcadd</guid>
<title>455- A Field Guide to Water</title>
<description>
<![CDATA[ <p>What does water mean to you? In this feature, author Bonnie Tsui (<i>Why We Swim</i>), actress Joy Bryant, submarine pilot Erika Bergman, figure skater Elladj Baldé, 85-year-old synchronized swimmer Barbara Eison-White, professional mermaid Olivia Gonzales, and others share stories about the many ways water influences our lives.</p><p>From <a href="https://www.popupmagazine.com/">Pop-Up Magazine</a>, creators of this<a href="https://www.popupmagazine.com/fieldguide/"> Field Guide series</a>: "We recommend listening outside, near water if you can. Head to the ocean if you’re on the coast. Or walk to a nearby pond or creek. Sit by a fountain at a park. Or just pour yourself a glass of water."</p><p>Plus, an excerpt of <a href="https://www.stitcher.com/show/periodic-talks-1995038/episode/roman-mars-on-the-anatomy-of-a-good-story-w-michelle-fournet-roman-mars-pedro-pascal-200230334"><i>Roman Mars On The Anatomy Of A Good Story (w/ Michelle Fournet, Roman Mars, Pedro Pascal)</i></a>, part of the Periodic Talks podcast. It's a show about what gets people curious, from virtual experiences to celestial bodies, with Gillian Jacobs (Community, Netflix's LOVE) and Diona Reasonover (NCIS)</p><p><a href="https://99percentinvisible.org/?p=37869&post_type=episode">A Field Guide to Water</a></p> ]]>
</description>
<pubDate>Tue, 17 Aug 2021 22:47:20 +0000</pubDate>
<author>roman@99pi.org (Periodic Talks, Pop Up Magazine)</author>
<link>https://99percentinvisible.org</link>
<content:encoded>
<![CDATA[ <p>What does water mean to you? In this feature, author Bonnie Tsui (<i>Why We Swim</i>), actress Joy Bryant, submarine pilot Erika Bergman, figure skater Elladj Baldé, 85-year-old synchronized swimmer Barbara Eison-White, professional mermaid Olivia Gonzales, and others share stories about the many ways water influences our lives.</p><p>From <a href="https://www.popupmagazine.com/">Pop-Up Magazine</a>, creators of this<a href="https://www.popupmagazine.com/fieldguide/"> Field Guide series</a>: "We recommend listening outside, near water if you can. Head to the ocean if you’re on the coast. Or walk to a nearby pond or creek. Sit by a fountain at a park. Or just pour yourself a glass of water."</p><p>Plus, an excerpt of <a href="https://www.stitcher.com/show/periodic-talks-1995038/episode/roman-mars-on-the-anatomy-of-a-good-story-w-michelle-fournet-roman-mars-pedro-pascal-200230334"><i>Roman Mars On The Anatomy Of A Good Story (w/ Michelle Fournet, Roman Mars, Pedro Pascal)</i></a>, part of the Periodic Talks podcast. It's a show about what gets people curious, from virtual experiences to celestial bodies, with Gillian Jacobs (Community, Netflix's LOVE) and Diona Reasonover (NCIS)</p><p><a href="https://99percentinvisible.org/?p=37869&post_type=episode">A Field Guide to Water</a></p> ]]>
</content:encoded>
<enclosure length="33663866" type="audio/mpeg" url="https://dts.podtrac.com/redirect.mp3/stitcher.simplecastaudio.com/3bb687b0-04af-4257-90f1-39eef4e631b6/episodes/6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc/audio/128/default.mp3?aid=rss_feed&awCollectionId=3bb687b0-04af-4257-90f1-39eef4e631b6&awEpisodeId=6a89a2a2-2399-4a5f-a4cd-8ffdc75898cc&feed=BqbsxVfO"/>
<itunes:title>455- A Field Guide to Water</itunes:title>
<itunes:author>Periodic Talks, Pop Up Magazine</itunes:author>
<itunes:duration>00:34:57</itunes:duration>
<itunes:summary>What does water mean to you? In this feature, author Bonnie Tsui (Why We Swim), actress Joy Bryant, submarine pilot Erika Bergman, figure skater Elladj Baldé, 85-year-old synchronized swimmer Barbara Eison-White, professional mermaid Olivia Gonzales, and others share stories about the many ways water influences our lives.</itunes:summary>
<itunes:subtitle>What does water mean to you? In this feature, author Bonnie Tsui (Why We Swim), actress Joy Bryant, submarine pilot Erika Bergman, figure skater Elladj Baldé, 85-year-old synchronized swimmer Barbara Eison-White, professional mermaid Olivia Gonzales, and others share stories about the many ways water influences our lives.</itunes:subtitle>
<itunes:keywords>gillian jacobs, water, pop-up magazine, bonnie tsui, diona reasonover</itunes:keywords>
<itunes:explicit>no</itunes:explicit>
<itunes:episodeType>full</itunes:episodeType>
</item>)";

    WiFiClient *client = new WiFiClient(longXML, 6707);

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

void test_readUntil_should_returnFullBuffer_when_DelimNotFound(void)
{

    //arrange
    const char *text = "12345678901234567890AndTestingAA";
    const char *expected = "2345678901234567890AndTestingAA"; //buffer is 32, need room for null byte at end
    char buffer[32];
    WiFiClient *client = new WiFiClient(text, 32);
    RSSReader rss = RSSReader(client);

    //act & assert
    TEST_ASSERT_EQUAL(true, rss.readUntil(buffer, 32, 'X'));

    for (int i = 0; i < 32; i++)
    {
        TEST_ASSERT_EQUAL_HEX8(expected[i], buffer[i]);
    }
    TEST_ASSERT_EQUAL('\0', buffer[31]);
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

int main(void)
{
    UNITY_BEGIN();
    RUN_TEST(test_goToThisText_should_readChars_until_FindGivenText);
    RUN_TEST(test_goToThisText_should_returnFalse_when_CantFindGiventText);
    RUN_TEST(test_goToThisText_should_handleXML);
    RUN_TEST(test_readUntil_should_fillBufferUntilDelim);
    RUN_TEST(test_readUntil_should_returnFullBuffer_when_DelimNotFound);
    RUN_TEST(test_readUntil_should_loopThroughBuffer_until_delimFound);
    return UNITY_END();
}
