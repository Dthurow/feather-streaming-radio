#include "../inc/RadioStreamInterface.h"

class StreamSelector
{
public:

    StreamSelector(int initialSelection, int numberOfStreams);

    /*!
    * @brief Includes the given strm in the options
    */
    void AddStream(RadioStreamInterface *strm, int index);

    void ChangeStreamTo(int index);

    /*!
    * @brief check if we need to update stream selection
    */
    void CheckSelection(void);

    /*!
    * @brief plays current stream
    */
    void PlayCurrentStream(void);

    void SetVolume(uint8_t left, uint8_t right);

private:
    uint8_t updateToNewStream();
    RadioStreamInterface **StreamOptions;
    RadioStreamInterface *CurrentStream = nullptr;
    int StreamIndex;
    int StreamOptionsLength;

};