/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    TEMPERATURE & HUMIDITY REPORT  ///////////
  /* Steps:
   1: Upload code and insert DHT22 sensor at sensor 2 place
   2: Insert Nokia LCD at LCD place
   3: Enable LCD and Sensor by placing their respective jumpers at IOT board
   4: You can see temp and humidity values at Nokia LCD
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
DHTesp dht;
int Sensor_PIN  = 2;    //

// Pins
const int8_t RST_PIN = D1;
const int8_t CE_PIN = D2;
const int8_t DC_PIN = D0;


Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);

  dht.setup(Sensor_PIN, DHTesp::DHT11); // Connect DHT sensor to Sensor_PIN

  display.begin();
  display.setContrast(40);  // Adjust for your display

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Unicorn");
  display.setCursor(0, 20);
  display.println("Devices");
  display.display();
  delay(2000);
}

void loop() {
  delay(dht.getMinimumSamplingPeriod());

  float humidity = dht.getHumidity();
  float temperature = dht.getTemperature();     //celcius
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Humidity  (%) " + String(humidity));
  display.setCursor(0, 25);
  display.println("Temperature(C)" + String(temperature));
  display.display();
  delay(1000);
}
