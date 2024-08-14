// Libraries
#include <WiFi.h>
#include <PubSubClient.h>
#include "Secrets.h"

// Pin I/O
#define LED 2

// Constants
const char* MQTT_SERVER = "mqtt.dis.eafit.edu.co";
const short MQTT_PORT = 1883;
const char* MQTT_CLIENT = "esp32_ns";
const char* TOPIC = "/devices/esp32_ns";

// Variables
WiFiClient wifiClient;
PubSubClient mqtt(wifiClient);

// Subroutines
void setupWifi() {
  delay(10);

  // Start connection to WiFi network
  Serial.print("Connecting to [" + String(__WIFI_SSID) + "]");
  WiFi.mode(WIFI_STA);
  WiFi.begin(__WIFI_SSID, __WIFI_PSWD);

  // Await connection
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  Serial.println("\nWiFi Connected [IP:" + String(WiFi.localIP()) + "]");
}

void reconnect() {
  // Loop until connection is established
  while (!mqtt.connected()) {
    // Attempt to connect
    Serial.println("Attempting MQTT Connection...");

    // Exit on success
    if (mqtt.connect(MQTT_CLIENT, __MQTT_USER, __WIFI_PSWD)) {
      Serial.println("Connected");
      return;
    }

    // Retry after 5s
    Serial.println("Failed, RC=" + String(mqtt.state()) + ". Retrying in 5s");
    delay(5000);
  }
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Convert message to String
  String topicStr = topic;
  String payloadStr = (char*) payload;
  payloadStr.remove(length);
  Serial.print("Message Received [" + topicStr + "] " + payloadStr);
}

void setup() {
  // Pin definition
  pinMode(LED, OUTPUT);

  // Comms
  Serial.begin(115200);
  setupWifi();
  mqtt.setServer(MQTT_SERVER, MQTT_PORT);
}

void loop() {
  if (!mqtt.connected()) reconnect();
  mqtt.loop();
}
