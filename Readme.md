# The All-in-One Streaming Radio

Do you have some less tech-savvy family, who wishes they could listen to the music they *used* to listen to? A friend or family member who would love listening to [99 percent invisible](https://99percentinvisible.org/), [radiolab](https://www.wnycstudios.org/podcasts/radiolab), or other cool podcast, but would throw the computer in a river before they figured out how to listen to one? Why not make a sytem you can put into an old-timey radio case, with simple controls, that would let them do just that? ...Listen to podcasts or their own music, I mean, not throw computers in the river. That's what this project is all about!

# Features

## Simple interface
The plan is to keep the interface simple and familiar. One knob for volume, one for switching between different "radio station" options. There may be a future plan to add a skip/back button setup, but for now, I'm keeping it simple. 

This is both for ease-of-development and to help non-tech-savvy people. 

## The "radio station" options
A knob controls different "radio stations", but what are they and why are they in quotes? Each "radio station" is actually a stream from someplace. Right now, I'm building out functionality so you can easily add your own internet streaming radio stations, music that's stored on a SD card, and eventually, the ability to have individual podcasts, too!

### Internet Radio
Currently only tested with [soma.fm](soma.fm) radio, you can pass in the URL from a direct stream, such as [http://ice6.somafm.com/groovesalad-128-mp3](http://ice6.somafm.com/groovesalad-128-mp3) and it will automatically stream. 

### Music on a microSD card
It doesn't just have to be internet radio, it can also be saved music you already own. Currently only tested with MP3, you can put music in folders on a microSD card, put it in the hardware, and set the code to use each folder you added as its own radio station!

**NOTE** Because I'm using Arduino and it's a FAT filesystem, the directories must have short names, and the files must have short names (such as track001.mp3). I eventually plan on adding a tool to help format the SD card in the correct manner so you don't have to do too much messing around with it yourself.

### Podcasts - (Future)
This is future functionality right now. The eventual plan is to let you set an RSS feed to a podcast, and it will automatically pull in the podcast episodes, in order. Each podcast will be its own "station" on the radio. 

## The Hardware
I'm using an [adafruit Huzzah with ESP8266](https://www.adafruit.com/product/2821) as my main brains. It has built-in wifi support and seems smart enough for my needs. To play the music, I'm using the [adafruit music maker featherwing](https://www.adafruit.com/product/3436) which uses the VS1053B codec chip, allowing it to support Ogg Vorbis, MP3/MP2/MP1, MP4, AAC, WMA, FLAC, WAV/PCM, and MIDI formats, plus it has a built in microSD card slot, which I'm using for that radio station option above. The sound comes from two [3W 4 Ohm mono speakers](https://www.adafruit.com/product/4445).

### temporary hardware
Right now I'm using a [10K linear pot](https://www.adafruit.com/product/562) from adafruit for the volume control, and a single [momentary switch button](https://www.adafruit.com/product/1119) for switching between stations. Eventually this will be replaced with rotary encoders for both. 

## Config file - (Future)
Eventually, I plan on having a simple configuration file on the microSD card that the feather will read on start up, which is where you'll put the list of "radio stations" and where to find them. 

# How to get started

TODO, sorry!