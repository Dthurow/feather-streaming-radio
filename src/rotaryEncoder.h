#include <Arduino.h>

class RotaryEncoder
{

public:
    RotaryEncoder(uint8_t channelA, uint8_t channelB);
    void initialize(void);
    int checkSelection(void);

private:
    int prevVal = 0;
    int newVal;
    unsigned int clockState = 0;
    unsigned int counterClockState = 0;
    //lookup table, first index is previous value
    //second index is current value
    //says if it's part of the sequence when moving
    //clockwise (1) or counterclockwise (-1)
    //didn't move (0) or skipped a value (2)
    int lookupTable[4][4] = {{0, -1, 1, 2},
                             {1, 0, 2, -1},
                             {-1, 2, 0, 1},
                             {2, 1, -1, 0}};
    uint8_t pin_encoder_a = 4;
    uint8_t pin_encoder_b = 5;
};