#ifndef RSSREADER_h
#define RSSREADER_h

#ifdef TEST
#include "../test/testWifi.h"
#include "../test/testSerial.h"
#else
#include <ESP8266WiFi.h>
#endif
#include <stdint.h>

class RSSReader
{
public:
    RSSReader(WiFiClient *client);

    char * getNextEpisode();
    uint8_t goToThisText(const char *text);

    private:
        WiFiClient *feed;

};

#endif