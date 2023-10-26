/*
 * Name: SerialMaster
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   Sends a boolean value via serial port 3
 */

// Pin I/O
#define SWITCH 37

// Variables
bool switchState = false;

void setup() {
  // Pin init
  pinMode(SWITCH, INPUT);

  // Comms
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  // Read the switch
  switchState = digitalRead(SWITCH);
  Serial.println("SWITCH="+String(switchState));

  // Send through port 3
  Serial3.println(switchState);
  Serial3.flush();

  delay(10);
}
