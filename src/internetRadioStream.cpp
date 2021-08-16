#include "internetRadioStream.h"
#define DEFAULTVOL 30

InternetRadioStream::InternetRadioStream(char *streamHost, char *streamPath, SoundOutputInterface *sound)
{
    musicPlayer = sound;
    host = streamHost;
    path = streamPath;
}

uint8_t InternetRadioStream::begin(void)
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
    }

    if (!setupWifi())
    {
        Serial.println("Could not connect to wifi");
        //something went wrong!
        return false;
    }

    initialized = 1;
    return true;
}

uint8_t InternetRadioStream::end(void)
{
    Serial.println("Called end");
    client.stop();
    return true;
}

void InternetRadioStream::playRadio(void)
{
    if (musicPlayer->readyForData())
    {
        
        //wants more data! check we have something available from the stream
        if (client.available() > 0)
        {
            // yea! read up to 32 bytes
            uint8_t bytesread = client.read(mp3buff, 32);
            // if (bytesread < 32)
            // {
            //     Serial.print("read byes: ");
            //     Serial.println(bytesread);
            // }

            // push to mp3
            musicPlayer->playData(mp3buff, bytesread);
        }
    }
}

void InternetRadioStream::setVolume(uint8_t left, uint8_t right)
{
    musicPlayer->setVolume(left, right);
}

uint8_t InternetRadioStream::setupWifi()
{
    //check if need to setup wifi
    wl_status_t curStat = WiFi.status();
    if (curStat != WL_CONNECTED && curStat != WL_IDLE_STATUS)
    {
        Serial.print("Connecting to SSID ");
        Serial.println(ssid);
        WiFi.begin(ssid, password);

        while (WiFi.status() != WL_CONNECTED)
        {
            delay(500);
            Serial.print(".");
        }

        Serial.println("WiFi connected");
        Serial.println("IP address: ");
        Serial.println(WiFi.localIP());
    }

    /************************* INITIALIZE STREAM */
    if (client.available() <= 0 || !client.connected())
    {
        Serial.print("connecting to ");
        Serial.println(host);

        if (!client.connect(host, httpPort))
        {
            Serial.println("Connection failed");
            return -1;
        }

        // We now create a URI for the request
        Serial.print("Requesting URL: ");
        Serial.println(path);

        // This will send the request to the server
        client.print(String("GET ") + path + " HTTP/1.1\r\n" +
                     "Host: " + host + "\r\n" +
                     "Connection: close\r\n\r\n");
    }
}