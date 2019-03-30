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
  5:  Go lve with your IOT board after placing DHT sensor at sensor 2 field.
  6:  You will start receiving sensor data at your websocket window
  

  //////////////////////////////////////////////////////////////////////////////////////
  /////////////// See Complete Manual at: WWW.UNICORNDEVICES.COM   /////////////////////
  ////////////////////////////////////////////////////////////////////////////////////*/



#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
float temp, humd;




const char* mqttServer = "m15.cloudmqtt.com";
int mqttPort = 14629 ;
const char* mqttUser = "pwmmummy";
const char* mqttPassword = "9zE35oEb_awd" ;

const char* ssid = "SpeedX-Unicorn";
const char* password = "unicorn123";

WiFiClient espClient;
PubSubClient client(espClient);

String data;
DHT dht(DHTPIN, DHTTYPE);


void setup_wifi();
void MQTT_Setup();
void PUBLISH_DATA(String data , String topic);

void setup() {
  Serial.begin(9600);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
  setup_wifi();
  dht.begin();
  MQTT_Setup();


}

void loop() {
  delay(2000);
  humd = dht.readHumidity();
  // Read temperature as Celsius (the default)
  temp = dht.readTemperature();
  data = "Temperature: " + String(temp) + "Humidity: " + String(humd);
  Serial.println(data);
  PUBLISH_DATA(data , "Sensor Data");

if (!client.connected()) {
  reconnect();
}
client.loop();
}

void PUBLISH_DATA(String data , String topic) {
  int data_len = data.length();
  char databuf[data_len + 2];
  data.toCharArray(databuf, data_len + 2);
  //Serial.println(databuf);

  int topic_len = topic.length();
  char topicbuf[topic_len + 2];
  topic.toCharArray(topicbuf, topic_len + 2);
  client.publish(topicbuf, databuf, true);
}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

void MQTT_Setup() {
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);
  if (client.connect("ESP8266Client", mqttUser, mqttPassword )) {
    Serial.println("connected");
    client.publish("Initialize", "Hello" );
  } 
  else {

    Serial.print("failed with state ");
    Serial.print(client.state());

  }
}
