#include "../inc/SoundOutputInterface.h"
#include <Adafruit_VS1053.h>
#include "SoundOutput.h"

//define all methods out of line for consistency. Must put at least one. Reason:
//the compiler has to put the (one and only one) vtable for a class into some object file or the other. 
//it puts it into the object file for the translation unit where the definition of the first 
//non-pure-virtual out-of-line virtual member function is present. 
//if there is no such definition, it errors out with a missing vtable error


  /*!
   * @brief Initialize communication and (hard) reset the chip.
   * @return Returns true if sound output is ready to begin
   */
  uint8_t SoundOutput::begin(void){
    return musicPlayer.begin();
  }

/*!
   * @brief Generate a sine-wave test signal
   * @param n Defines the sine test to use
   * @param ms Delay (in ms)
   */
  void SoundOutput::sineTest(uint8_t n, uint16_t ms){
    musicPlayer.sineTest(n, ms);
  }

/*!
   * @brief Test if ready for more data
   * @return Returns true if it is ready for data
   */
  boolean SoundOutput::readyForData(void){
    return musicPlayer.readyForData();
  }

/*!
   * @brief Decode and play the contents of the supplied buffer
   * @param buffer Buffer to decode and play
   * @param buffsiz Size to decode and play
   */
  void SoundOutput::playData(uint8_t *buffer, uint8_t buffsiz){
    musicPlayer.playData(buffer, buffsiz);
  }

  /*!
   * @brief Set the output volume for the chip
   * @param left Desired left channel volume
   * @param right Desired right channel volume
   */
  void SoundOutput::setVolume(uint8_t left, uint8_t right){
    musicPlayer.setVolume(left, right);
  }

