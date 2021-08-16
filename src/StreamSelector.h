#include "../inc/RadioStreamInterface.h"
#define MAX_NUMBER_OF_STREAMS 15

class StreamSelector
{
public:

    StreamSelector(int initialSelection, int numberOfStreams);

    /*!
    * @brief Includes the given strm in the options
    */
    void AddStream(RadioStreamInterface *strm, int index);

    /*!
    * @brief Updates to the stream at the given index
    * @return true if update was successful
    */
    uint8_t ChangeStreamTo(int index);

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
    RadioStreamInterface *StreamOptions [MAX_NUMBER_OF_STREAMS];
    RadioStreamInterface *CurrentStream = nullptr;
    int StreamIndex;
    int StreamOptionsLength;

};