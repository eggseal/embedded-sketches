#ifndef _EEPROM_UTIL
#define _EEPROM_UTIL

class EEPromUtil {
public:
  static void init(unsigned int size) {
    if (!EEPROM.begin(size)) {
      Serial.println("Failed EEPROM Initialization. Restarting...");
      delay(1000);
      ESP.restart();
      return;
    }
    Serial.println("Initialized EEPROM.");
    delay(10);
  }

  static String readString(unsigned int start, unsigned int size) {
    String result = "";
    for (size_t i = start; i < start + size; i++)
      result += char(EEPROM.read(i));
    return result;
  }

  static void setupCredentials(String &essid, String &epass) {
    essid = EEPromUtil::readString(0, 0x20);
    epass = EEPromUtil::readString(0x20, 0x40);
    Serial.println("EEPROM Data - SSID=" + essid + " :: PASSWORD=" + epass);
    delay(10);
  }
};
#endif