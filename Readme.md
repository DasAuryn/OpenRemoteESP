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
