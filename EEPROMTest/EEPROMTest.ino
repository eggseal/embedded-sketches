#include <EEPROM.h>

#define READ

#ifdef READ
String wifiSSID;
String wifiPass;
#else
String wifiSSID = "IoT-B19";
String wifiPass = "lcontrol2020*";
#endif

void setup() {
  Serial.begin(115200);

  EEPROM.begin(512);

#ifdef READ
  Serial.println(wifiSSID);
  Serial.println(wifiPass);
  
  EEPROM.get(0, wifiSSID);
  EEPROM.get(sizeof(wifiSSID), wifiPass);
#else
  EEPROM.put(0, wifiSSID);
  EEPROM.put(sizeof(wifiSSID), wifiPass);
  EEPROM.commit();
#endif

  Serial.println(wifiSSID);
  Serial.println(wifiPass);
}

void loop() {
}