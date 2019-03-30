/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////   Blynk Relays ON OFF ///////////
  /* Steps: 
   *  
   *  
   > Check manual and design a project at Blynk application
   1: Set your internet router SSID & Password and lynk project authorization token in code.
   2: Place the Relay-EN jumpers
   3: Open your project at blynk application and go live(Online)
   4: Turn ON/OFF switch at application associated to digital pins 1 & 3, and check the state of relays on board
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "2d896285e8664523860dc15bdda7673b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jazz-LTE-DBB3";
char pass[] = "48456841";

void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}
