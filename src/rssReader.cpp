#include "rssReader.h"
#ifdef TEST
testSerial Serial = testSerial();
#endif

RSSReader::RSSReader(WiFiClient *client)
{
    feed = client;
}

uint8_t RSSReader::getNextEpisode(char *urlBuffer, int length)
{
    //read through the feed until get to a item
    if (goToThisText("<item>"))
    {
        //Serial.println("Found item");
        //read through the feed until get to an enclosure
        if (goToThisText("<enclosure"))
        {
            //Serial.println("Found enclosure");
            //read through the feed until get to the URL in the enclosure
            if (goToThisText("url=\""))
            {
                //Serial.println("Found URL");
                //read the URL
                //return the URL
                return readUntil(urlBuffer, length, '"');
            }
        }
    }
    return false;
}

//fills buffer with data from feed until it reaches the delimiter char
//or the end of the feed, whatever comes first
uint8_t RSSReader::readUntil(char *buffer, int length, char delim)
{
    int insertIndex = 0;
    int headerIndex = 0;
    char circularBuffer[length + 1];

    char c = feed->read();
    while (c != -1 && c != delim)
    {
        // Serial.print("setting ");
        // Serial.print(insertIndex);
        // Serial.print(" to ");
        // Serial.println(c);
        circularBuffer[insertIndex] = c;
        //update index, loop around the buffer if needed
        //leaving one char for null byte
        insertIndex++;
        insertIndex %= length;
        if (insertIndex == headerIndex)
        {

            headerIndex++;
            headerIndex %= length;
            //Serial.print("updated header index to ");Serial.println(headerIndex);
        }
        c = feed->read();
    }

    if (c == -1)
    {
        //the feed ended before I found my delim
        //set the buffer to empty and return false
        buffer[0] = '\0';
        return false;
    }

    // Serial.print("setting ");
    // Serial.print(insertIndex);
    // Serial.print(" to null");
    circularBuffer[insertIndex] = '\0'; //null terminate

    int cirIndex = headerIndex;
    int index = 0;
    while (circularBuffer[cirIndex] != '\0')
    {
        // Serial.print("setting ");
        // Serial.print(index);
        // Serial.print(" to ");
        // Serial.println(circularBuffer[cirIndex]);
        buffer[index] = circularBuffer[cirIndex];
        cirIndex++;
        cirIndex %= (length);
        index++;
    }

    // Serial.print("setting ");
    // Serial.print(index);
    // Serial.print(" to null");
    buffer[index] = '\0'; //null terminate

    return true;
}

uint8_t RSSReader::goToThisText(const char *text)
{
    //read chars from the feed until it gets to and consumes the given text

    int matchIndex = 0;
    while (text[matchIndex] != '\0')
    {
        char c = feed->read();
        //Serial.print(c);
        //if (c < 0x20 || c > 0x7E)
        if (c == -1)
        {
            //non printable characters
            //Serial.println("No more to read");
            return false;
        }
        if (text[matchIndex] == c)
        {
            // if (matchIndex > 1)
            // {
            //     Serial.println("Found match, incrementing");
            // }
            matchIndex++;
        }
        else
        {
            // if (matchIndex > 1)
            // {
            //     Serial.print("Got to ");
            //     Serial.print(matchIndex);
            //     Serial.println(" but found mismatch, resetting");
            // }

            matchIndex = 0;
        }
    }

    return true;
}