/*//////////////////////////////////////////////////
  ///       UNICORN IOT PROJECT BOARD    /////////////
  ////////////////////////////////////////////////////
  //////    MQTT COMMUNICATION  ///////////
  /* Steps:
  1: Build Your MQTT Broker in CloudMQTT
      Follow first three steps of this tutorial https://medium.com/@suci/build-your-mqtt-broker-in-cloudmqtt-f95ba04270c3  to create an account at Cloudmqtt.com.
  2:  Open the instance you created in previous step, go to its detail window and note your server id, username, password and port number, we will need these details for next step. 
  3:  Edit the following code according to your mqtt broker details, and upload in controller.
  4:  Open the mqtt instance at your web browser, and click on websocket UI window.
  5:  Here you can see a “Send message” section, write “UNICORN IOT-BOARD” and “(Hello)” in topic and message field respectively(don't ignore the brackets), and click on send button.
  6:  You will receive a message from IOT board in received messages section.
  7:  Change the topic in code and try to communicate using different topics.

  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <ESP8266WiFi.h>
#include <PubSubClient.h>

const char* ssid = "SpeedX-Unicorn";
const char* password =  "unicorn123";
const char* mqttServer = "";
const int mqttPort = 0000 ;
const char* mqttUser = "";
const char* mqttPassword = "" ;

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {

  Serial.begin(115200);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println("Connected to the WiFi network");

  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  while (!client.connected()) {
    Serial.println("Connecting to MQTT...");

    if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {

      Serial.println("connected");

    } else {

      Serial.print("failed with state ");
      Serial.print(client.state());
      delay(2000);

    }
  }

  //client.publish("esp/test", "Hello from ESP8266");
  client.subscribe("IOT-BOARD");

}

void callback(char* topic, byte* payload, unsigned int length) {

  Serial.print("Message arrived in topic: ");
  Serial.println(topic);
  char msg[length];
  Serial.print("Message:");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    msg[i] = (char)payload[i];
  }
  String data = String(msg);
  String message = data.substring(data.indexOf("(") + 1 , data.indexOf(")"));
  Serial.println(message);
  Serial.println("-----------------------");
  if (message.equals("Hello"))
  {
    client.publish("Unicorn IOT-BOARD", "Hello from IOT BOARD");
  }
}

void loop() {
  client.loop();
}
