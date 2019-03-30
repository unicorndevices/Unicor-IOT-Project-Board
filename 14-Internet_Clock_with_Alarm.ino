/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////   Blynk Relays ON OFF ///////////
  /* Steps:


   > Check manual and design a project at Blynk application
   1: Set your internet router SSID & Password and lynk project authorization token in code.
   2: Place the BZEN jumper and Nokia lCD at its headers
   3: Open your project at blynk application and go live(Online)
   4: You will see current time at LCD and alram is not setted by default, Input alarm time in time input widget of application.
   5: Set alaram activation minutes for alarm to be ring, default is 5 minutes.
   6: When current time approaches to alarm time, buzzer will start beeping for active minutes.
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#define BLYNK_PRINT Serial
#include <Time.h>
#include <TimeLib.h>
#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#include <BlynkSimpleEsp8266.h>


const int8_t RST_PIN = D1;
const int8_t CE_PIN = D2;
const int8_t DC_PIN = D0;
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);
int GMT = 5;
int  Seconds, Hours, Minutes, DAY, MONTH, YEAR;
int alaram_hour, alaram_min, alaram_sec;
long int time_now;
int active_time = 5;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);


char auth[] = "2d896285e8664523860dc15bdda7673b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jazz-LTE-DBB3";
char pass[] = "48456841";

unsigned long start_time = 00;
unsigned long end_time = 00;
unsigned long curr_time;
int buzzer = 3;


BLYNK_WRITE(V2) {
  active_time = param.asInt();
  Serial.println(active_time);
  end_time =  alaram_hour * 60 + (alaram_min + active_time);

}



BLYNK_WRITE(V1) {


  TimeInputParam t(param);

  // Process start time

  if (t.hasStartTime())
  {
    Serial.println(String("Start: ") +
                   t.getStartHour() + ":" +
                   t.getStartMinute() + ":" +
                   t.getStartSecond());
    Blynk.virtualWrite(V5, String("Start: ") +
                       t.getStartHour() + ":" +
                       t.getStartMinute() + ":" +
                       t.getStartSecond());


    alaram_hour = t.getStartHour();
    alaram_min = t.getStartMinute();
    alaram_sec = t.getStartSecond();

    start_time =  t.getStartHour() * 60 + t.getStartMinute();
    end_time =  alaram_hour * 60 + (alaram_min + active_time);
    Serial.println(start_time);
    Serial.println(end_time);
  }


  Serial.println();
}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(buzzer, OUTPUT);
  digitalWrite(buzzer, LOW);
  Blynk.begin(auth, ssid, pass);
 
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
  display.clearDisplay();

}

void loop()
{
  Blynk.run();
  timeClient.update();
  time_now = timeClient.getEpochTime() + 18000 ;
  //Serial.println(timeClient.getFormattedTime());
  check_alarm();

  DAY = day(time_now);
  MONTH = month(time_now);
  YEAR = year(time_now);

  Hours = hourFormat12(time_now);
  Seconds = second(time_now);
  Minutes = minute(time_now);
  LCD_DISPLAY(String(alaram_hour), String(alaram_min));
  display.display();
  delay(1000);

}

void check_alarm() {
  Hours = hour(time_now);
  curr_time = Hours * 60 + Minutes;
  //Serial.println(curr_time);
  if (curr_time >= start_time  && curr_time < end_time)
  {
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
    digitalWrite(buzzer, HIGH);
    delay(50);
    digitalWrite(buzzer, LOW);
    delay(50);
  }
  else
    digitalWrite(buzzer, LOW);
}

void LCD_DISPLAY(String A_Hour, String A_Min)
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
  display.setCursor(0, 25);
  display.println("Alarm " + A_Hour + ":" + A_Min);



  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(15, 37);
  display.println(String(DAY) + ":" + String(MONTH) + ":" + String(YEAR));

}
