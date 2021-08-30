
// include SPI, MP3 and SD libraries
#include <SPI.h>
#include "SoundOutput.h"
#include "internetRadioStream.h"
#include "SDRadioStream.h"
#include "StreamSelector.h"
#include "rotaryEncoder.h"
#define DEFAULTVOL 30

#define VOLUME_KNOB A0
#define ROTARY_ENCODER_CHANNEL_A 4
#define ROTARY_ENCODER_CHANNEL_B 5

int lastvol = DEFAULTVOL;

SoundOutput sound = SoundOutput();

/*-----UPDATE STREAM LIST AND LENGTH HERE----*/
int StreamLength = 4;
// http://ice6.somafm.com/groovesalad-128-mp3
//http://ice2.somafm.com/seventies-128-mp3
RadioStreamInterface *radioStream1 = new InternetRadioStream("ice6.somafm.com", "/groovesalad-128-mp3", &sound);
RadioStreamInterface *radioStream2 = new SDRadioStream(&sound, "/myradio");
RadioStreamInterface *radioStream3 = new InternetRadioStream("ice2.somafm.com", "/seventies-128-mp3", &sound);
RadioStreamInterface *radioStream4 = new SDRadioStream(&sound, "/anotherradio");

/* ------------------------------------------*/

StreamSelector *selector;
RotaryEncoder *rotary;

void setup()
{
  Serial.begin(115200);

  Serial.println("\n\nAdafruit VS1053 Feather WiFi Radio");

  selector = new StreamSelector(0, StreamLength);

  /* ADD NEW STREAMS HERE */
  selector->AddStream(radioStream1, 0);
  selector->AddStream(radioStream2, 1);
  selector->AddStream(radioStream3, 2);
  selector->AddStream(radioStream4, 3);
  /*---------------------*/

  Serial.println("Setting up rotary encoder");
  rotary = new RotaryEncoder(ROTARY_ENCODER_CHANNEL_A, ROTARY_ENCODER_CHANNEL_B);
  rotary->initialize();
}

int loopcounter = 0;
int running = 0;

void loop()
{
  int rotVal = rotary->checkSelection();
  if (rotVal)
  {
    //cycle through streams with button press

    bool successfulUpdate = false;
    //try to initialize the new stream
    //if it fails, just start working through all streams
    //until one succeeds
    do
    {
      if (rotVal == 1)
      {
        running = (running + 1) % StreamLength;
      }
      else if (rotVal == -1)
      {
        //decrement, but loop around if reach start
        running = (running - 1 < 0) ? StreamLength - 1 : running - 1;
      }

      Serial.print("Trying to initialize stream ");
      Serial.println(running);
      successfulUpdate = selector->ChangeStreamTo(running);
    } while (!successfulUpdate);

    selector->SetVolume(lastvol, lastvol);
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