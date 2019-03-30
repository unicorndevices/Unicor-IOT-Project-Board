/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    Blynk text to Board LCD with beep  ///////////
  /* Steps:


   > Check manual and design a project at Blynk application
   1: Set your internet router SSID & Password and lynk project authorization token in code.
   2: Place the Nokia LCD and BZ-EN jumper at board
   3: Open your project at blynk application and go live(Online)
   4: Write a message at text input field and click send, you will see your message at NOKIA LCD with a notification beep.
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/


#define BLYNK_PRINT Serial


#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int8_t  RST_PIN = D1;
const int8_t  CE_PIN = D2;
const int8_t  DC_PIN = D0;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);

char auth[] = " 2d896285e8664523860dc15bdda7673b";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Jazz-LTE-DBB3";
char pass[] = "48456841";

int buz_pin = 3;
// This function will be called every time Slider Widget
// in Blynk app writes values to the Virtual Pin 1
BLYNK_WRITE(V2)
{
  String msg = param.asStr(); // assigning incoming value from pin V1 to a variable
  for (int i = 0; i < 3 ; i++) {
    digitalWrite(buz_pin, HIGH);
    delay(200);
    digitalWrite(buz_pin, LOW);
    delay(200);
  }
  Serial.print("massege is: ");
  Serial.println(msg);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println(msg);
  display.display();

}

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(buz_pin, OUTPUT);
  digitalWrite(buz_pin, LOW);

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


  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);
}

void loop()
{
  Blynk.run();
}
