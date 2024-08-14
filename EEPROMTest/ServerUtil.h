#ifndef _SERVER_UTIL
#define _SERVER_UTIL

#include "WifiUtil.h"

WebServer server(80);
String content = "";
bool deployedServer = false;

class ServerUtil {
public:
  static void home() {
    Serial.println("HTTP /");
    content = "<p>Hello World</p>";
    server.send(200, "text/html", content);
  }

  static void launchAP() {
    deployedServer = true;
    WiFi.softAP("DEV_ESP32_NS", "pelo");
    Serial.println("Local IP=" + WifiUtil::getIP(WiFi.localIP()));
    Serial.println("Soft APIP=" + WifiUtil::getIP(WiFi.softAPIP()));

    server.on("/", []() {
      Serial.println("HTTP /");
      content = "<p>Hello World</p>";
      server.send(200, "text/html", content);
    });
    server.begin();
  }
};
#endif