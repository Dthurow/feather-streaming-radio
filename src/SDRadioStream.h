#include "../inc/RadioStreamInterface.h"
#include "../inc/SoundOutputInterface.h"
#include <SD.h>
#define MAX_TRACKLIST_LENGTH 50

class SDRadioStream : public RadioStreamInterface
{
public:
    SDRadioStream(SoundOutputInterface *sound, char * folderName = "/");
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
    int initialized = 0;
    void findTrackList(File dir);
    boolean isMP3File(const char *fileName);
    unsigned long mp3_ID3Jumper(File mp3);

    SoundOutputInterface *musicPlayer;
    // our little buffer of mp3 data
    uint8_t mp3buff[MP3_BUFFER_LENGTH]; // vs1053 likes 32 bytes at a time
    File currentTrack;             //!< File that is currently playing
    String trackList[MAX_TRACKLIST_LENGTH];
    int trackListIndex = 0;
    int trackListLength;
    char * streamFolder;
};