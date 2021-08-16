#include "../inc/RadioStreamInterface.h"
#include "StreamSelector.h"
#include <SPI.h>

StreamSelector::StreamSelector(int initialSelection, int numberOfStreams)
{
    StreamIndex = initialSelection;
    StreamOptionsLength = numberOfStreams < MAX_NUMBER_OF_STREAMS ? numberOfStreams : MAX_NUMBER_OF_STREAMS;
}

uint8_t StreamSelector::ChangeStreamTo(int index)
{
    StreamIndex = index % StreamOptionsLength;
    return updateToNewStream();
}

/*!
    * @brief Includes the given strm in the options
    */
void StreamSelector::AddStream(RadioStreamInterface *strm, int index)
{
    if (index >= StreamOptionsLength)
    {
        //if the index is outside of the originally planned bounds
        //either update the bounds (if under the max number of streams)
        //or loop and overwrite the older streams
        if (StreamOptionsLength < MAX_NUMBER_OF_STREAMS)
        {
            index = StreamOptionsLength;
            StreamOptionsLength++;
        }
        else
        {
            StreamOptionsLength = MAX_NUMBER_OF_STREAMS;
            index = index % StreamOptionsLength;
        }
    }
    StreamOptions[index] = strm;
    if (index == StreamIndex)
    {
        Serial.println("updating to new stream");
        updateToNewStream();
    }
}

/*!
    * @brief check if we need to update stream selection
    */
void StreamSelector::CheckSelection(void)
{
    //check knob or whatever
    bool changed = false;
    if (changed)
    {
        //TODO update index to new value
        updateToNewStream();
    }
}

/*!
    * @brief plays current stream
    */
void StreamSelector::PlayCurrentStream(void)
{
    if (CurrentStream)
    {
        CurrentStream->playRadio();
    }
    else
    {
        Serial.println("It's null!");
    }
}

uint8_t StreamSelector::updateToNewStream(void)
{
    if (CurrentStream)
    {
        CurrentStream->end();
    }
    Serial.print("setting stream to ");
    Serial.println(StreamIndex);

    CurrentStream = StreamOptions[StreamIndex];
    if (!CurrentStream)
    {
        Serial.println("It's still a nullptr!");
        return false;
    }
    Serial.println("calling begin");
    return CurrentStream->begin();
}

void StreamSelector::SetVolume(uint8_t left, uint8_t right)
{

    CurrentStream->setVolume(left, right);
}