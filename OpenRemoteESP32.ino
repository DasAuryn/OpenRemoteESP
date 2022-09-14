/*
  Basic MQTT example for OpenRemote www.openremote.io

  This Code is for an ESP32
  In case you use an ESP8266, change the WiFi Library.
  #include <ESP8266WiFi.h>

  For ESP8266 SSL Connection, you need a fingerprint of your Server Certificate
  Example: "static const char *fingerprint PROGMEM = "00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00";"
  and in the setup: askClient.setFingerprint(fingerprint);

  This sketch demonstrates the basic capabilities of the library.
  It connects to an OpenRemote MQTT server then:
  - publishes boolean "1" to your topic
  - publishes "Hello" to another topic
  - subscribes to your topic  printing out any messages

  It will reconnect to the server if the connection is lost using a blocking
  reconnect function.

  Edit secret.h for your credentials.

  In case you connect to the broker nonsecure, change the object "WifiClientSecure" to "WifiClient"
  and comment out in setup askClient.setCACert(local_root_ca);
  Also change the MQTT Port in secret.h

***Important: Don't forget to add the PubSubClient to your Library*** https://github.com/knolleary/pubsubclient

*/

#include "secret.h"
#include <WiFi.h>
#include <PubSubClient.h>

//Objects
WiFiClientSecure askClient; //If you use non SSL then WiFiClient askClient;
PubSubClient client(askClient);

void setup() {
  Serial.begin(115200);
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);

  }

  Serial.println(WiFi.localIP());
  askClient.setCACert(local_root_ca); //If you use non SSL then comment out
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

}

void loop() {
  //Publish Boolean format:
  client.publish("master/xxxxxxxxxx/writeattributevalue/AttributeName/AsssetID", "1");
  //To publish Strings:
  client.publish("master/xxxxxxxxxx/writeattributevalue/AttributeName/AssetID", String("Hello").c_str());
  delay(10000);

}

//MQTT callback
void callback(char* topic, byte * payload, unsigned int length) {

  for (int i = 0; i < length; i++) {
    Serial.println(topic);
    Serial.print(" has send ");
    Serial.print((char)payload[i]);
  }

}

//MQTT reconnect
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("********** Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(ClientID, username, mqttpass, lastwill, 1, 1, lastwillmsg)) {
      Serial.println("-> MQTT client connected");
      client.subscribe(topic);
      Serial.print("Subscribed to: ";
      Serial.println(topic);
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println("-> try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
