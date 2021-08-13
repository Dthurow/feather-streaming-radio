
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include "SoundOutput.h"
#include "internetRadioStream.h"
#include "SDRadioStream.h"
#include "StreamSelector.h"

char *ssid = "";
const char *password = "";

//  http://ice6.somafm.com/groovesalad-128-mp3
char *host = "ice6.somafm.com";
char *path = "/groovesalad-128-mp3";
int httpPort = 80;

#define VOLUME_KNOB A0
#define ON_OFF_SWITCH 4

int lastvol = 30;
RadioStreamInterface * radioStream1 = new InternetRadioStream(host, path, new SoundOutput());
RadioStreamInterface * radioStream2 = new SDRadioStream(new SoundOutput());
StreamSelector *selector;

void setup()
{
  Serial.begin(115200);

  Serial.println("\n\nAdafruit VS1053 Feather WiFi Radio");

  selector = new StreamSelector(0, 2);

  selector->AddStream(radioStream1, 0);
  selector->AddStream(radioStream2, 1);

  Serial.println("setting on off switch");
  //set on-off switch pin mode
  // don't use an IRQ, we'll hand-feed
  pinMode(ON_OFF_SWITCH, INPUT_PULLUP);
}


int loopcounter = 0;
int buttonHasLifted = 1;
int running = 1;

//return 1 if the button has been pressed, 0 otherwise
//function limits so it only returns 1 once per button press
//so polling works
int buttonPressed()
{
  int rawVal = digitalRead(ON_OFF_SWITCH);

  if (rawVal)
  {
    //button is not pressed
    buttonHasLifted = 1;
  }
  else
  {
    //button is pressed
    if (buttonHasLifted)
    {
      buttonHasLifted = 0; //don't return 1 again until the button has been lifted
      return 1;
    }
  }

  return 0;
}

void loop()
{
  if (buttonPressed())
  {
    //toggle running variable
    running = !running;
  }
  if (!running)
  {
    yield();
    return;
  }

  loopcounter++;

  selector->PlayCurrentStream();

  if (loopcounter >= 1000)
  {
    loopcounter = 0;
    // adjust volume!
    int vol = 0;
    vol = analogRead(VOLUME_KNOB);
    vol = map(vol, 0, 1023, 0, 50);
    if (abs(vol - lastvol) > 3)
    {
      Serial.println(vol);
      lastvol = vol;
      selector->SetVolume(lastvol, lastvol);
    }
  }
}