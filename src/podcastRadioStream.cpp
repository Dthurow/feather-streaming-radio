#include "podcastRadioStream.h"
#include "rssReader.h"
#define DEFAULTVOL 30
#ifdef TEST
testSerial Serial = testSerial();
#endif

PodcastRadioStream::PodcastRadioStream(char *streamHost, char *streamPath, SoundOutputInterface *sound)
{
    musicPlayer = sound;
    host = streamHost;
    path = streamPath;
}

uint8_t PodcastRadioStream::begin(void)
{

    if (!musicPlayer->begin())
    { // initialise the music player
        Serial.println(F("Couldn't find the sound output, do you have the right pins defined?"));
        return false;
    }

    if (initialized == 0)
    {

        // Set volume for left, right channels. lower numbers == louder volume!
        musicPlayer->setVolume(DEFAULTVOL, DEFAULTVOL);
        initialized = 1;
    }

    if (!setupWifi())
    {
        Serial.println("Could not connect to wifi");
        //something went wrong!
        return false;
    }

    //TODO process RSS feed until I find the first episode to play
    Serial.println("Setting up RSSreader");
    RSSReader reader = RSSReader(&feedClient);

    Serial.println("Finding episode");
    if (reader.getNextEpisode(currentEpisodeURL, EPISODE_URL_LENGTH))
    {
        Serial.print("Found episode URL: ");
        Serial.println(currentEpisodeURL);



    }
    else
    {
        Serial.println("Could not get next episode");
        return false;
    }

    return true;
}

uint8_t PodcastRadioStream::end(void)
{
    //TODO implement me!
    return false;
}

void PodcastRadioStream::playRadio(void)
{

    //TODO implement me
}

void PodcastRadioStream::setVolume(uint8_t left, uint8_t right)
{
    musicPlayer->setVolume(left, right);
}

uint8_t PodcastRadioStream::setupWifi()
{
    //TODO need to abstract this out for internetradio and podcasts
    //also so if the WIFI is bad I don't retry every single time

    //check if need to setup wifi
    wl_status_t curStat = WiFi.status();
    if (curStat != WL_CONNECTED && curStat != WL_IDLE_STATUS)
    {
        Serial.print("Connecting to SSID ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);
        int waitTime = 15;
        while (waitTime > 0 && WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
            waitTime--;
        }
        if (waitTime <= 0)
        {
            Serial.println("Timeout on connecting to wifi");
            return false;
        }

        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    /************************* INITIALIZE STREAM */
    if (feedClient.available() <= 0 || !feedClient.connected())
    {
        Serial.print("connecting to ");
        Serial.println(host);
        feedClient.setInsecure();
        if (!feedClient.connect(host, httpsPort))
        {
            Serial.println("Connection failed");
            return false;
        }

        // We now create a URI for the request
        Serial.print("Requesting URL: ");
        Serial.println(path);

        // This will send the request to the server
        feedClient.print(String("GET ") + path + " HTTP/1.1\r\n" +
                         "Host: " + host + "\r\n" +
                         "Connection: close\r\n\r\n");
    }

    return true;
}