#ifndef RadioStreamInterface_h
#define RadioStreamInterface_h
#include <stdint.h>

class RadioStreamInterface
{
public:
    /*!
    * @brief opens/starts anything needed for radio stream
    * @return Returns true everything is working
    */
    virtual uint8_t begin(void);

    /*!
    * @brief closes/ends anything needed for radio stream
    * @return Returns true if everything finished correctly
    */
    virtual uint8_t end(void);

    /*!
    * @brief plays some of the radio
    */
    virtual void playRadio(void);

    /*!
    * @brief updates volume of radio
    */
    virtual void setVolume(uint8_t left, uint8_t right);
};

#endif