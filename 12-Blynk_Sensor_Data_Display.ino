/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    Sending Sensor data to Blynk application  ///////////
  /* Steps: 
   *  
   *  
   > Check manual and design a project at Blynk application
   1: Set your internet router SSID & Password and lynk project authorization token in code.
   2: Place the sensor at sensor1 field
   3: Open your project at blynk application and go live(Online)
   4: You can see sensor value at type of value display widget subscribed for virtual pin 5 and pin 6.
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/
#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
int Sensor_PIN  = 0;

DHTesp dht;

char auth[] = "2d896285e8664523860dc15bdda7673b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jazz-LTE-DBB3";
char pass[] = "48456841";


float Temperature;
float Humidity;

BlynkTimer timer;

void myTimerEvent()
{
  Temperature = dht.getTemperature(); // Gets the values of the temperature
  Humidity = dht.getHumidity(); // Gets the values of the humidity
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, Temperature);
  Blynk.virtualWrite(V6, Humidity);
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  dht.setup(Sensor_PIN, DHTesp::DHT11);
  Blynk.begin(auth, ssid, pass);


  // Setup a function to be called every second
  timer.setInterval(5000L, myTimerEvent);
}

void loop()
{
  Blynk.run();
  timer.run(); // Initiates BlynkTimer
}
