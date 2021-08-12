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
    //TODO check if everything already setup, if so, return right away
    if (!musicPlayer->begin())
    { // initialise the music player
        Serial.println(F("Couldn't find the sound output, do you have the right pins defined?"));
        while (1)
            delay(10);
    }

    Serial.println(F("sound output initialized"));
    musicPlayer->sineTest(0x44, 500); // Make a tone to indicate it's working

    // Set volume for left, right channels. lower numbers == louder volume!
    musicPlayer->setVolume(DEFAULTVOL, DEFAULTVOL);

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

    /************************* INITIALIZE STREAM */
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
    return true;
}

uint8_t InternetRadioStream::end(void)
{
    return 0;
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
            // push to mp3
            musicPlayer->playData(mp3buff, bytesread);

        }
    }
}

void InternetRadioStream::setVolume(uint8_t left, uint8_t right)
{
    musicPlayer->setVolume(left, right);
}