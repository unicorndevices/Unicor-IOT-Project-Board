/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    Online Weather Report  ///////////
  /* Steps:
  1.  Install the library from “link”.
  2.  Goto “www.openweather.com” from your browser and get API key after registering your account,
  3.  Note the latitude and longitude of your location from google.
  4.  Make changings according to your API, wifi router and location in following code and enable the LCD using jumper.
  5. Check the complet weather report displayed at Nokia LCD.


  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <TridentTD_OpenWeather.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

#define ssid      "Jazz-LTE-DBB3"
#define pass      "48456841"

#define OpenWeather_APIKEY    "efa4041124acc9d273dcdbb21e8ea276"

#define lat      31.5204
#define lon      74.3587

#define timezone  5

const int8_t RST_PIN = D1;
const int8_t CE_PIN = D2;
const int8_t DC_PIN = D0;
Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);


unsigned long last_update_time = 0;
unsigned long update_time_interval = 120000;        //2 minutes

TridentTD_OpenWeather myPlace(OpenWeather_APIKEY);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.println(myPlace.getVersion());
  Serial.println();

  display.begin();
  display.setContrast(40);  // Adjust for your display

  Serial.println("Hello from Unicorn Devices");

  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Unicorn");
  display.setCursor(0, 20);
  display.println("Devices");
  display.display();
  delay(2000);
  // Show the Adafruit logo, which is preloaded into the buffer by their library
  display.clearDisplay();


  myPlace.wificonnect(ssid, pass);

  myPlace.setLocation( lat, lon );

  /* OPTIONAL to set "unit_type"
     by default   "metric"   ( Celcius, meter/sec)
     or change to "imperial" ( Fahrenheit, miles/hour) */
  //myPlace.setUnit("metric");
  //myPlace.setUnit("imperial");

  myPlace.weatherNow();

  Serial.println("--------------------------------------------");
  Serial.println("[OpenWeather] Location   : " + myPlace.latitude() + ", " + myPlace.longitude() );
  Serial.println("[OpenWeather] Temperature: " + String(myPlace.readTemperature()));  // [metric] Celcius  or [imperial] Fahrenheit
  Serial.println("[OpenWeather] Humidity   : " + String(myPlace.readHumidity()));     // %
  Serial.println("[OpenWeather] Pressure   : " + String(myPlace.readPressure()));     // hPa
  Serial.println("[OpenWeather] Weather    : " + myPlace.readWeather());
  Serial.println("[OpenWeather] Wind Speed : " + String(myPlace.readWindSpeed()));    // [metric] meter/sec  or [imperial] miles/hour
  Serial.println("[OpenWeather] Wind Deg   : " + String(myPlace.readWindDeg()));      // degrees
  Serial.println("[OpenWeather] Cloudiness : " + String(myPlace.readCloudiness()));   // %
  Serial.println("[OpenWeather] Sunrise    : " + String(myPlace.readSunrise(timezone)));
  Serial.println("[OpenWeather] Sunset     : " + String(myPlace.readSunset(timezone)));
  Serial.println("--------------------------------------------");

}


void weather(String parameter, String value, String Unit)
{
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println(String(myPlace.readTemperature()) + " C");

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 18);
  display.println(myPlace.readWeather());

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 30);
  display.println(parameter);

  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 40);
  display.println( value + " " + Unit);
}


void loop() {

  if (millis() - last_update_time > update_time_interval)
  {
    last_update_time = millis();
    myPlace.setLocation( lat, lon );
    myPlace.weatherNow();
    display.clearDisplay();
    display.setTextSize(2);
    display.setTextColor(BLACK);
    display.setCursor(0, 15);
    display.println("UPDATE");
    Serial.println("UPDATE");
    display.display();
    delay(2000);
  }
  else
  {
    weather("Humidity", String(myPlace.readHumidity()), "%");
    display.display();
    delay(3000);
    weather("Pressure" ,String(myPlace.readPressure()), "hPa");
    display.display();
    delay(3000);
    weather("WindSpeed" ,String(myPlace.readWindSpeed()), "m/s");
    display.display();
    delay(3000);
    weather("Wind Degree" ,String(myPlace.readWindDeg()), "degree");
    display.display();
    delay(3000);
    weather("Cloudiness" ,String(myPlace.readCloudiness()), "%");
    display.display();
    delay(3000);
    weather("Sun Rise" ,String(myPlace.readSunrise(timezone)), "");
    display.display();
    delay(3000);
    weather("Sun Set" ,String(myPlace.readSunset(timezone)), "");
    display.display();
    delay(3000);

  }

}
