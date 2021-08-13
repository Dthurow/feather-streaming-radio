#include "../inc/RadioStreamInterface.h"
#include "StreamSelector.h"
#include <SPI.h>

StreamSelector::StreamSelector(int initialSelection, int numberOfStreams)
{
    StreamIndex = initialSelection;
    StreamOptionsLength = numberOfStreams;
    StreamOptions = new RadioStreamInterface *[numberOfStreams];

}

void StreamSelector::ChangeStreamTo(int index){
    StreamIndex = index;
    updateToNewStream();
}

/*!
    * @brief Includes the given strm in the options
    */
void StreamSelector::AddStream(RadioStreamInterface *strm, int index)
{
    StreamOptions[index] = strm;
    if (index == StreamIndex){
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
    if (changed){
        //TODO update index to new value
        updateToNewStream();
    }

}

/*!
    * @brief plays current stream
    */
void StreamSelector::PlayCurrentStream(void)
{
    //Serial.println("in play current stream");
    if (CurrentStream){
        //Serial.println("going to call playRadio");
    CurrentStream->playRadio();

    }
    else{
        Serial.println("It's null!");
    }
}

uint8_t StreamSelector::updateToNewStream(void)
{
    //CurrentStream->end();
    Serial.print("setting stream to ");
    Serial.println(StreamIndex);
    CurrentStream = StreamOptions[StreamIndex];
    if (!CurrentStream){
        Serial.println("It's still a nullptr!");
    }
    Serial.println("calling begin");
    return CurrentStream->begin();
    
    
}

void StreamSelector::SetVolume(uint8_t left, uint8_t right){

    CurrentStream->setVolume(left, right);
}