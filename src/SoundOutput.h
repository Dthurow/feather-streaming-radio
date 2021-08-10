#include <Arduino.h>
#include <Adafruit_VS1053.h>
#include "../inc/SoundOutputInterface.h"

// These are the pins used
#define VS1053_RESET -1 // VS1053 reset pin (not used!)
#define VS1053_CS 16    // VS1053 chip select pin (output)
#define VS1053_DCS 15   // VS1053 Data/command select pin (output)
#define VS1053_DREQ 0   // VS1053 Data request, ideally an Interrupt pin

class SoundOutput : public SoundOutputInterface
{
public:
  uint8_t begin(void);
  void sineTest(uint8_t n, uint16_t ms);

  boolean readyForData(void);

  void playData(uint8_t *buffer, uint8_t buffsiz);

  void setVolume(uint8_t left, uint8_t right);

private:
  Adafruit_VS1053 musicPlayer = Adafruit_VS1053(VS1053_RESET, VS1053_CS, VS1053_DCS, VS1053_DREQ);
};