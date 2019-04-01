/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    TEMPERATURE & HUMIDITY REPORT  ///////////
  /* Steps:
   1: Set your internet router SSID & Password in code.
   2: Upload code and see IP address at serial Monitor
   3: Enter IP in browser (note: IOT board and browser device must be at same network)
   4: Check temp and humidity on browser.
   5: You can set temp and humidity threshold to activate relay 1 and 2 respectively
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int8_t  RST_PIN = D1;                                     //defining LCD Pins
const int8_t  CE_PIN = D2;
const int8_t  DC_PIN = D0;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);


#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
int Sensor_PIN      = 0;                      //sensor 2 field at IOT board
int relay1_Pin      = 3;                      //for temperature threshold 
int relay2_Pin      = 1;                      //for humidity threshold
/*Put your SSID & Password*/
const char* ssid = "";                       // Enter SSID here
const char* password = "";                   //Enter Password here
String local_IPaddress;
DHTesp dht;

ESP8266WebServer server(80);              //default port is 80


float Temperature;
float Humidity;
float temp_thr = 50;
float humd_thr = 80;

void setup() {
  Serial.begin(115200);
  
  pinMode(relay1_Pin, OUTPUT);
  digitalWrite(relay1_Pin, LOW);
  
  pinMode(relay2_Pin, OUTPUT);
  digitalWrite(relay2_Pin, LOW);

  dht.setup(Sensor_PIN, DHTesp::DHT11);                                //defien DHT sensor type

  display.begin();
  display.setContrast(40);                                             // Adjust for your display

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("Connecting to ");
  display.setCursor(0, 20);
  display.println(ssid);
  display.display();

  Serial.println("Connecting to ");
  Serial.println(ssid);

  //connect to your local wi-fi network
  WiFi.begin(ssid, password);

  //check wi-fi is connected to wi-fi network
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(BLACK);
  display.setCursor(0, 0);
  display.println("WiFi connected");
  display.setCursor(0, 15);
  display.println("Got IP: ");
  display.setCursor(0, 30);
  display.println(WiFi.localIP());
  display.display();




  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());


  local_IPaddress = WiFi.localIP().toString();

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  delay(dht.getMinimumSamplingPeriod());
  Temperature = dht.getTemperature();         // Gets the values of the temperature
  Humidity = dht.getHumidity();               // Gets the values of the humidity

  if (Temperature >= temp_thr )
  {
    digitalWrite(relay1_Pin, HIGH);
  }
  if (Temperature < temp_thr)
  {
    digitalWrite(relay1_Pin, LOW);
  }

  if (Humidity >= humd_thr )
  {
    digitalWrite(relay2_Pin, HIGH);
  }
  if (Humidity < humd_thr)
  {
    digitalWrite(relay2_Pin, LOW);
  }
  server.handleClient();
  delay(200);
}

void handle_OnConnect() {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>Weather Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Temperature and Humidity Report</h1>\n";
  ptr += "<form action='http://" + local_IPaddress + "' method='POST'>";
  ptr += "<p>Temperature: ";
  ptr += String(Temperature);
  ptr += "°C</p>";
  ptr += "<p>Humidity: ";
  ptr += String(Humidity);
  ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "Temperature Threshold to activate Relay 1 (e.g 25.5):<input type='text' name='temp_thr'>";
  ptr += "</p>";
   ptr +="</p>";
  ptr += "Humidity Threshold to activate Relay 2 (e.g 50.5):&nbsp;&nbsp;&nbsp;<input type='text' name='humd_thr'>&nbsp;<input type='submit' value='Enter'>";
  ptr += "</form>";
  ptr += "</body>\n";
  ptr += "</html>\n";
  server.send(200, "text/html", ptr);
  if (server.args() > 0 ) {                                            // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      Serial.print(server.argName(i));                                // Display the argument
      //  Argument_Name = server.argName(i);
      if (server.argName(i) == "temp_thr") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        if (server.arg(i).length() > 0)                              //make sure input field is not empty
          temp_thr = server.arg(i).toFloat();
        // e.g. range_maximum = server.arg(i).toInt();               // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat();             // use string.toFloat() if you wanted to convert the input to a floating point number
      }
      if (server.argName(i) == "humd_thr") {
        Serial.print(" Input received was: ");
        Serial.println(server.arg(i));
        if (server.arg(i).length() > 0)                              //make sure input field is not empty
          humd_thr = server.arg(i).toFloat();
        // e.g. range_maximum = server.arg(i).toInt();              // use string.toInt()   if you wanted to convert the input to an integer number
        // e.g. range_maximum = server.arg(i).toFloat();            // use string.toFloat() if you wanted to convert the input to a floating point number
      }

    }
  }
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}
