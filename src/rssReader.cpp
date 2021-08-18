#include "rssReader.h"
#ifdef TEST
testSerial Serial = testSerial();
#endif

RSSReader::RSSReader(WiFiClient *client)
{
    feed = client;
}

uint8_t RSSReader::goToThisText(const char *text)
{
    //read chars from the feed until it gets to and consumes the given text

    int matchIndex = 0;
    while (text[matchIndex] != '\0')
    {
        char c = feed->read();
        if (c == -1){
            Serial.println("No more to read");
            return false;
        }
        if (text[matchIndex] == c)
        {
            Serial.println("Found match, incrementing");
            matchIndex++;
        }
        else
        {
            Serial.print("Got to "); Serial.print(matchIndex); Serial.println(" but found mismatch, resetting");
            matchIndex = 0;
        }
    }

    return true;
}