#ifndef _WIFI_UTIL
#define _WIFI_UTIL

class WifiUtil {
public:
  static void connect(String ssid, String pass) {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), pass.c_str());
  }

  static void disconnect() {
    Serial.println("Disconnecting WiFi...");
    WiFi.disconnect();
  }

  static String getIP(IPAddress ip) {
    return String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
  }
};
#endif