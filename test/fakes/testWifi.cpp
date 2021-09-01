#include "testWifi.h"

WiFiClient::WiFiClient(const char * text, int length){
    mytext = text;
    textLength = length;
}

/*!
* @return The next byte (or character), or -1 if none is available.
*/
 int WiFiClient::read()
 {
     int returnChar;
     if (index < textLength){
         returnChar = mytext[index];
         index++;
     }
     else{
         returnChar = -1;
     }

    return returnChar;

 }