#include "rssReader.h"
#ifdef TEST
testSerial Serial = testSerial();
#endif

RSSReader::RSSReader(WiFiClient *client)
{
    feed = client;
}

char *RSSReader::getNextEpisode()
{
}

//fills buffer with data from feed until it reaches the delimiter char
uint8_t RSSReader::readUntil(char *buffer, int length, char delim)
{
    int insertIndex = 0;
    int headerIndex = 0;
    char circularBuffer[length+1];

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
        if (insertIndex == headerIndex){
            
            headerIndex++;
            headerIndex %= length;
            //Serial.print("updated header index to ");Serial.println(headerIndex);
            
        }
        c = feed->read();
    }
    // Serial.print("setting ");
    // Serial.print(insertIndex);
    // Serial.print(" to null");
    circularBuffer[insertIndex] = '\0'; //null terminate

    int cirIndex = headerIndex;
    int index = 0;
    while (circularBuffer[cirIndex] != '\0'){
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
        if (c == -1)
        {
            //Serial.println("No more to read");
            return false;
        }
        if (text[matchIndex] == c)
        {
            //Serial.println("Found match, incrementing");
            matchIndex++;
        }
        else
        {
            //Serial.print("Got to ");
            //Serial.print(matchIndex);
            //Serial.println(" but found mismatch, resetting");
            matchIndex = 0;
        }
    }

    return true;
}