#ifndef TESTWIFI_h
#define TESTWIFI_h

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