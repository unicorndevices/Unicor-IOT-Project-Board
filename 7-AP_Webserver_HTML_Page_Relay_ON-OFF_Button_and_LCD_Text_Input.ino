/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    TEMPERATURE & HUMIDITY REPORT  ///////////
  /* Steps:
   1: Set SSID and Password whatver you want to set for your access point
   2: Upload code and connect to the access point, goto IP address "192.168.4.1" from your mobile/laptop browser.
   3: Click on ON/OFF buttons and check relay1 state
   4. Write any text in input field and check display at Nokia LCD.
  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/




#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_PCD8544.h>

const int8_t  RST_PIN = D1;                                               //defining LCD pins
const int8_t  CE_PIN  = D2;
const int8_t  DC_PIN  = D0;

Adafruit_PCD8544 display = Adafruit_PCD8544(DC_PIN, CE_PIN, RST_PIN);




ESP8266WebServer server(80);

// Replace with your network credentials
const char* ssid         = "Unicorn";
const char* password     = "unicorn123";

String HTMLpage     = "";
String LCD_Message  = "";
int relay1 = 1;
bool relay11_flag = false;

void setup() {

  pinMode(relay1, OUTPUT);
  digitalWrite(relay1, LOW);


  //Serial.begin(115200);
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
  // Wait for connection
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  //Serial.print("AP IP address: ");
  //Serial.println(myIP);
  server.begin();
  server.on("/",  handle_OnConnect);




  server.on("/relay11ON", relay1_ON);                                     //function to turn ON relay 1

  server.on("/relay11OFF", relay1_OFF);                                   //function to turn OFF relay 1


  //Serial.println("HTTP server started");
}

void relay1_ON() {
  digitalWrite(relay1, HIGH);
  relay11_flag = true;
  //Serial.println("relay1 ON");
  handle_OnConnect();
}

void relay1_OFF() {
  digitalWrite(relay1, LOW);
  relay11_flag = false;
  //Serial.println("relay1 OFF");
  handle_OnConnect();
}



void loop() {
  server.handleClient();
}


void handle_OnConnect() {
  HTMLpage = "";
  HTMLpage += "<head><title>server Tutorial</title></head><h3>UNICORN IOT BOARD</h3>\n<form action='http://192.168.4.1' method='POST'><p>relay 1 <a href=\"relay1ON\">ON</a>&nbsp;<a href=\"relay1OFF\">OFF</a></p>";
  HTMLpage += "</div>\n";
  if (relay11_flag == true)
    HTMLpage += "<p>relay is ON</p>";
  if (!relay11_flag)
    HTMLpage += "<p>relay is OFF</p>";

  HTMLpage += "Enter text to display on Nokia LCD :<input type='text' name='LCD_message'>&nbsp;<input type='submit' value='Enter'>";
  HTMLpage += "</div>\n";
  server.send(200, "text/html", HTMLpage );
  if (server.args() > 0 ) {                                             // Arguments were received
    for ( uint8_t i = 0; i < server.args(); i++ ) {
      //Serial.print(server.argName(i));                                  // Display the argument
      //  Argument_Name = server.argName(i);
      if (server.argName(i) == "LCD_message") {
        //Serial.print(" Input received was: ");
        //Serial.println(server.arg(i));
        if (server.arg(i).length() > 0) {                                //make sure input field is not empty
          LCD_Message = server.arg(i);
          display.clearDisplay();
          display.setTextSize(1);
          display.setTextColor(BLACK);
          display.setCursor(0, 0);
          display.println(LCD_Message);
          display.display();
        }
      }
    }
  }

}


