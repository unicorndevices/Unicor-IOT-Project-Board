/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    TEMPERATURE & HUMIDITY REPORT  ///////////
  /* Steps:
   1: Set your internet router SSID & Password in code.
   2: Set GMT value according to your time zone and Upload code
   3: Place the LCD at its headers and power on IOT board.
   4: Wait for few seconds so controller can get updated time from internet
   5: You can see current time and date at Nokia lCD
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <Time.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>
// set your SSID and PASSWORD here
const char *ssid     = "";
const char *password = "";

const int8_t RST_PIN = D1;                                                                //defining LCD Pins
const int8_t CE_PIN = D2;
const int8_t DC_PIN = D0;
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);
int GMT = 5;
int DAY, MONTH, YEAR, Seconds, Hours;
long int time_now;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);                                     //time library object

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);

  display.begin();
  display.setContrast(40);                                         // Adjust for your display

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Unicorn");
  display.setCursor(0, 20);
  display.println("Devices");
  display.display();
  delay(2000);
  display.clearDisplay();

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin();
}

void loop() {
  timeClient.update();
  time_now = timeClient.getEpochTime() + (GMT * 3600) ;                        //GMT HOUR TO SECONDS
  DAY = day(time_now);
  MONTH = month(time_now);
  YEAR = year(time_now);
  Hours = hourFormat12(time_now);
  Seconds = second(time_now);

  LCD_DISPLAY(String(DAY), String(MONTH), String(YEAR));
  display.display();

  delay(1000);

}
//function to display time and date at LCD
void LCD_DISPLAY(String DAY, String MONTH, String YEAR)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 5);
  if (Hours > 9)
    display.println(String(Hours) + ":" + timeClient.getMinutes());
  if (Hours < 10)
    display.println("0" + String(Hours) + ":" + timeClient.getMinutes());

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(65, 5);
  display.println(String(Seconds));

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(65, 14);
  if (isPM(time_now))
    display.println("PM");
  if (isAM(time_now))
    display.println("AM");


  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(15, 35);
  display.println(DAY + ":" + MONTH + ":" + YEAR);                //display date

}
