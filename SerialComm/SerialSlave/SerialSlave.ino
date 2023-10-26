/*
 * Name: SerialSlave
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   Receives a boolean value via serial port 3 and toggles pin 22 according to the value
 */

// Pin I/O
#define LED 22

// Variables
bool switchState = false;

void setup() {
  // Pin init
  pinMode(LED, OUTPUT);

  // Output clearing
  digitalWrite(LED, LOW);

  // Comms
  Serial.begin(9600);
  Serial3.begin(9600);
}

void loop() {
  if (Serial3.available() <= 0) return;

  // Receive data
  switchState = Serial3.readStringUntil('\n').toInt();
  Serial.println("Received: " + String(switchState));

  // Toggle led
  digitalWrite(LED, switchState);
}
