#include "../inc/SoundOutputInterface.h"
#include <stdint.h>
typedef bool boolean;


class TestSoundOutput : public SoundOutputInterface
{
public:
  uint8_t begin(void);
  void sineTest(uint8_t n, uint16_t ms);

  boolean readyForData(void);

  void playData(uint8_t *buffer, uint8_t buffsiz);

  void setVolume(uint8_t left, uint8_t right);
};