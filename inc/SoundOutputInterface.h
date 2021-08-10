#ifndef SoundOutputInterface_h
#define SoundOutputInterface_h
#include <Arduino.h>

class SoundOutputInterface
{
public:
  /*!
   * @brief Initialize communication and (hard) reset the chip.
   * @return Returns true if a VS1053 is found
   */
  virtual uint8_t begin(void);
  /*!
   * @brief Generate a sine-wave test signal
   * @param n Defines the sine test to use
   * @param ms Delay (in ms)
   */
  virtual void sineTest(uint8_t n, uint16_t ms);
  /*!
   * @brief Test if ready for more data
   * @return Returns true if it is ready for data
   */
  virtual boolean readyForData(void);

  /*!
   * @brief Decode and play the contents of the supplied buffer
   * @param buffer Buffer to decode and play
   * @param buffsiz Size to decode and play
   */
  virtual void playData(uint8_t *buffer, uint8_t buffsiz);

  /*!
   * @brief Set the output volume for the chip
   * @param left Desired left channel volume
   * @param right Desired right channel volume
   */
  virtual void setVolume(uint8_t left, uint8_t right);
};

#endif
