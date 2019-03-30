/*//////////////////////////////////////////////////// 
///       UNICORN IOT PROJECT BOARD    ///////////////
//////////////////////////////////////////////////////
//////    Nokia LCD message display  ///////////////// 
 /* Steps:
 * 1: Upload code and Insert Nokia LCD at LCD place 
 * 2: Enable LCD by placing its jumper
 * 3: You can see text data at Nokia LCD
 * 4: Set contrast upto 60 value in code according to your LCD 
  */
 //////////////////////////////////////////////////////////////////////////////////////
 /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
 ////////////////////////////////////////////////////////////////////////////////////*/
  
  
  
#include <Arduino.h>

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>



const int8_t  RST_PIN = D1;
const int8_t  CE_PIN = D2;
const int8_t  DC_PIN = D0;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
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

}
