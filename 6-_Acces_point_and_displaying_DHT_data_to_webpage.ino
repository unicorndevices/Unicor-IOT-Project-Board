
/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////   Sensor data at HTML page ///////////
  /* Steps:
   1: Set SSID and Password whatver you want to set for your access point
   2: Upload code and connect to the access point, goto IP address "192.168.4.1" from your mobile/laptop browser.
   3: Check temp and humidity values on browser (Refresh page to get updated values).
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/


#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include "DHTesp.h"

#ifdef ESP32
#pragma message(THIS EXAMPLE IS FOR ESP8266 ONLY!)
#error Select ESP8266 board.
#endif
int Sensor_PIN  = 0;
/*Put your SSID & Password*/
const char* ssid = "Unicorn-Devices";  // Enter SSID here
const char* password = "unicorn123";  //Enter Password here

DHTesp dht;

ESP8266WebServer server(80);


float Temperature;
float Humidity;

void setup() {
  Serial.begin(115200);
  delay(100);

  dht.setup(Sensor_PIN, DHTesp::DHT11);


  //connect to your local wi-fi network
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {

  server.handleClient();

}

void handle_OnConnect() {

  Temperature = dht.getTemperature(); // Gets the values of the temperature
  Humidity = dht.getHumidity(); // Gets the values of the humidity
  server.send(200, "text/html", SendHTML(Temperature, Humidity));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML(float Temperaturestat, float Humiditystat) {
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr += "<title>ESP8266 Weather Report</title>\n";
  ptr += "<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr += "body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr += "p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr += "</style>\n";
  ptr += "</head>\n";
  ptr += "<body>\n";
  ptr += "<div id=\"webpage\">\n";
  ptr += "<h1>Unicorn IOT Board Weather Report</h1>\n";

  ptr += "<p>Temperature: ";
  ptr += String(Temperaturestat);
  ptr += "°C</p>";
  ptr += "<p>Humidity: ";
  ptr += String(Humiditystat);
  ptr += "%</p>";

  ptr += "</div>\n";
  ptr += "</body>\n";
  ptr += "</html>\n";
  return ptr;
}
