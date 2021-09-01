#ifndef ESP8266WIFI_H
#define ESP8266WIFI_H

class WiFiClientSecure{

};

class WiFiClient
{
public:
    WiFiClient(const char *text, int length);
    int read();
    int index = 0;

private:
    const char * mytext;
    int textLength;
};
#endif