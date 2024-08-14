/*
 * Name:        ThingWorxESP32
 * Description: This program interacts with the Universidad EAFIT IoT Greenhouse's ThingWorx v9 platform via an ESP32 board
 * Author:      eggseal
 * Date:        2024/3/20
 */

// Libraries
#include <ThingworxESP32.h>
#include <ArduinoJson.h>

// Pin I/O
#define BOOT 0

// Constants
#define WIFI_SSID "IoT-B19"                             // The SSID of your Wi-Fi connection
#define WIFI_PASS "lcontrol2020*"                       // The password of your Wi-Fi connection
#define TWX_HOST "iot.dis.eafit.edu.co"       // The host of the ThingWorx platform
#define TWX_PORT 80                                     // The port of the ThingWorx platform
#define TWX_KEY "af054ce4-718d-4018-b365-46f2ed6fd42e"  // The API key of the ThingWorx project
#define TWX_THING "Central_thing"                       // The Thing of the ThingWorx project
#define TWX_INTERVAL 1000

// Variables
String jsonRes = "";
unsigned long lastReq = 0;
JsonDocument jsonIn;
Thingworx centralThing(TWX_HOST, TWX_PORT, TWX_KEY, TWX_THING);

// Subroutines
const char* wifiStatus() {
  return ("SSID: " + String(WiFi.SSID()) + "\nIPv4: " + WiFi.localIP().toString() + "\nRSSI: " + String(WiFi.RSSI()) + " dBm").c_str();
}

void wifiInit() {
  delay(1000);

  Serial.print("[Wi-Fi] Connecting to: ");
  Serial.println(WIFI_SSID);
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(1000);
  }
  Serial.println();
}

// Main
void setup() {
  // Pin definition
  pinMode(BOOT, INPUT);

  // Comms
  Serial.begin(115200);

  // Wi-Fi
  wifiInit();
  Serial.println(wifiStatus());
}

void loop() {
  if (millis() - lastReq >= TWX_INTERVAL) {
    // jsonRes = centralThing.getjson();
    deserializeJson(jsonIn, centralThing.getjson());
    serializeJsonPretty(jsonIn, Serial);
  }
}
