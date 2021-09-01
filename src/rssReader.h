#ifndef RSSREADER_h
#define RSSREADER_h

#ifdef TEST
#include "../test/fakes/testWifi.h"
#include "../test/fakes/testSerial.h"
#else
#include <ESP8266WiFi.h>
#endif
#include <stdint.h>

class RSSReader
{
public:
    RSSReader(WiFiClient *client);

    uint8_t getNextEpisode(char *urlBuffer, int length);
    uint8_t goToThisText(const char *text);
    uint8_t readUntil(char * buffer, int length, char delim);

    private:
        WiFiClient *feed;

};

#endif