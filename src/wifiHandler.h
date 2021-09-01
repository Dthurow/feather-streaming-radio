#include <ESP8266WiFi.h>

class WifiHandler{
public:
    void SetupWifi();
    void ConnectToURL(const char* fullURL, WiFiClient *client);

private:
    bool wifiConnectionGood;
};