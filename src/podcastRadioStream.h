#ifndef PODCASTRADIOSTREAM_h
#define PODCASTRADIOSTREAM_h
#include "../inc/RadioStreamInterface.h"
#include "../inc/SoundOutputInterface.h"
#include <ESP8266WiFi.h>
#define EPISODE_URL_LENGTH 350

class PodcastRadioStream : public RadioStreamInterface
{
public:
    PodcastRadioStream(char *streamHost, char *streamPath, SoundOutputInterface *sound);
    /*!
    * @brief opens/starts anything needed for radio stream
    * @return Returns true everything is working
    */
    uint8_t begin(void);

    /*!
    * @brief closes/ends anything needed for radio stream
    * @return Returns true if everything finished correctly
    */
    uint8_t end(void);

    /*!
    * @brief plays some of the radio
    */
    void playRadio(void);

    /*!
    * @brief updates volume of radio
    */
    void setVolume(uint8_t left, uint8_t right);

private:
    uint8_t setupWifi();

    int initialized = 0;
    SoundOutputInterface *musicPlayer;
    char *ssid = "";
    char *password = "";
    char *host;
    char *path;
    char currentEpisodeURL[EPISODE_URL_LENGTH];

    const int httpPort = 80;
    const int httpsPort = 443;
    // Use WiFiClient class to create HTTP/TCP connection
    WiFiClientSecure feedClient;
    WiFiClientSecure episodeClient;
    // our little buffer of mp3 data
    uint8_t mp3buff[32]; // vs1053 likes 32 bytes at a time
};
#endif