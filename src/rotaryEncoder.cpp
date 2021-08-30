#include "rotaryEncoder.h"



RotaryEncoder::RotaryEncoder(uint8_t channelA, uint8_t channelB){
    pin_encoder_a = channelA;
    pin_encoder_b = channelB;
}

void RotaryEncoder::initialize() {
  pinMode(pin_encoder_a, INPUT_PULLUP);
  pinMode(pin_encoder_b, INPUT_PULLUP);

  int valA = digitalRead(pin_encoder_a);
  int valB = digitalRead(pin_encoder_b);
  prevVal = (valA << 1) + valB;

}

int RotaryEncoder::checkSelection() {
  int valA = digitalRead(pin_encoder_a);
  int valB = digitalRead(pin_encoder_b);
  int returnVal = 0;
  newVal = (valA << 1) + valB;
  
  int info = lookupTable[prevVal][newVal];


  if (info == 1){
    clockState |= (1 << newVal); //set the bit to 1
  }
  else if (info == -1){
    counterClockState |= (1 << newVal);
  }
  else if (info == 2){
    Serial.println("skipped a value");
  }

  if (prevVal != newVal && newVal == 3){
    //changed to the non moving state, lets figure out what direction we went!

    //for each clockwise and counterclockwise, the encoder state goes through 4 distinct states
    //make sure it's gone through at least 3 of those (and assume if one is missing it's because I didn't read fast enough)
    if (clockState == 0b1011 || clockState == 0b1101 || clockState == 0b1110 || clockState == 0b1111){
      Serial.println("Result was clockwise");
      returnVal = 1;
    }
    else if (counterClockState == 0b1011 || counterClockState == 0b1101 || counterClockState == 0b1110 || counterClockState == 0b1111){
      Serial.println("Result was COUNTER clockwise");
      returnVal = -1;
    }
    
    clockState = 0;
    counterClockState = 0;
    
  }
  
  prevVal = newVal;

  return returnVal;
}