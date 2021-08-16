#include "SDRadioStream.h"
#define DEFAULTVOL 30
#define CARDCS 2 // Card chip select pin
#define DIMENSION_OF_ARRAY(a) (sizeof(a) / sizeof(a[0]))
#include <stdint.h>

SDRadioStream::SDRadioStream(SoundOutputInterface *sound, char *folderName)
{
    musicPlayer = sound;
    streamFolder = folderName;
}

uint8_t SDRadioStream::begin(void)
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

    if (!SD.begin(CARDCS))
    {
        Serial.println(F("SD failed, or not present"));
       return false;
    }
    Serial.println("SD OK!");

    if (initialized == 0)
    {
        Serial.println("Finding tracks");
        findTrackList(SD.open(streamFolder));

        for (int i = 0; i < trackListLength; i++)
        {
            Serial.println(trackList[i]);
        }

        if (trackList[0] != "")
        {

            //found at least one track, open it up
            currentTrack = SD.open(trackList[0]);
            Serial.print("Now playing: ");
            Serial.println(trackList[trackListIndex]);

            //if statement and function calls pulled from Adafruit_VS1053.cpp
            // We know we have a valid file. Check if .mp3
            // If so, check for ID3 tag and jump it if present.
            if (isMP3File(trackList[0].c_str()))
            {
                currentTrack.seek(mp3_ID3Jumper(currentTrack));
            }
        }
        else{
            Serial.println("no tracks found!");
            return false;
        }
    }
    initialized = 1;
    return true;
}

uint8_t SDRadioStream::end(void)
{
    return 0;
}

void SDRadioStream::playRadio(void)
{

    if (musicPlayer->readyForData())
    {
        int bytesread = currentTrack.read(mp3buff, MP3_BUFFER_LENGTH);
        if (bytesread == 0)
        {

            currentTrack.close();
            trackListIndex = (trackListIndex + 1) % trackListLength; // loop thru the tracks

            currentTrack = SD.open(trackList[trackListIndex]);

            Serial.print("Now playing: ");
            Serial.println(trackList[trackListIndex]);

            //if statement and function calls pulled from Adafruit_VS1053.cpp
            // We know we have a valid file. Check if .mp3
            // If so, check for ID3 tag and jump it if present.
            if (isMP3File(trackList[0].c_str()))
            {
                currentTrack.seek(mp3_ID3Jumper(currentTrack));
            }
            bytesread = currentTrack.read(mp3buff, MP3_BUFFER_LENGTH);
        }

        //Serial.println("ready!");
        musicPlayer->playData(mp3buff, bytesread);
        //Serial.println("stream!");
    }
}

void SDRadioStream::setVolume(uint8_t left, uint8_t right)
{
    musicPlayer->setVolume(left, right);
}

void SDRadioStream::findTrackList(File dir)
{
    int songCount = 0;
    while (true)
    {
        File entry = dir.openNextFile();
        if (!entry)
        {
            // no more files
            dir.rewindDirectory();
            break;
        }
        if (!entry.isDirectory())
        {
            trackList[songCount] = entry.fullName();
            songCount++;
            if (songCount == MAX_TRACKLIST_LENGTH)
            {
                //can't add any more songs w/o an overflow
                entry.close();
                break;
            }
        }
        entry.close();
    }

    trackListLength = songCount;
   
}

//copied from Adafruit_VS1053.cpp
// Just checks to see if the name ends in ".mp3"
boolean SDRadioStream::isMP3File(const char *fileName)
{
    return (strlen(fileName) > 4) &&
           !strcasecmp(fileName + strlen(fileName) - 4, ".mp3");
}

//copied from Adafruit_VS1053.cpp
unsigned long SDRadioStream::mp3_ID3Jumper(File mp3)
{

    char tag[4];
    uint32_t start;
    unsigned long current;

    start = 0;
    if (mp3)
    {
        current = mp3.position();
        if (mp3.seek(0))
        {
            if (mp3.read((uint8_t *)tag, 3))
            {
                tag[3] = '\0';
                if (!strcmp(tag, "ID3"))
                {
                    if (mp3.seek(6))
                    {
                        start = 0ul;
                        for (byte i = 0; i < 4; i++)
                        {
                            start <<= 7;
                            start |= (0x7F & mp3.read());
                        }
                    }
                    else
                    {
                        // Serial.println("Second seek failed?");
                    }
                }
                else
                {
                    // Serial.println("It wasn't the damn TAG.");
                }
            }
            else
            {
                // Serial.println("Read for the tag failed");
            }
        }
        else
        {
            // Serial.println("Seek failed? How can seek fail?");
        }
        mp3.seek(current); // Put you things away like you found 'em.
    }
    else
    {
        // Serial.println("They handed us a NULL file!");
    }
    // Serial.print("Jumper returning: "); Serial.println(start);
    return start;
}