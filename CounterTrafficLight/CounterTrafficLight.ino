/*
 * Name: Counter Traffic Light
 */

// Pin I/O
#define Q0 30  // Binary value 2^0
#define Q1 31  // Binary value 2^1
#define Q2 32  // Binary value 2^2
#define Q3 33  // Binary value 2^3
#define CP 22  // Counter increment
#define LR 29  // Red traffic light
#define LA 28  // Yellow traffic light
#define LV 27  // Green traffic light

// Constants
#define INCR_INTERVAL 1000 // Counter increment interval of 1s

// Variables
bool bin0 = false; // Read value of binary 2^0 (Q0)
bool bin1 = false; // Read value of binary 2^1 (Q1)
bool bin2 = false; // Read value of binary 2^2 (Q2)
bool bin3 = false; // Read value of binary 2^3 (Q3)
bool stateLR = false; // Current state to set led red
bool stateLA = false; // Current state to set led yellow
bool stateLV = false; // Current state to set led green

// Time variables
unsigned long currTime = 0;  // Current time of program since start
unsigned long incrTime = 0;  // Time of the last increment
unsigned long incrRel = 0;   // Relative time since last increment

// Subroutines
void increaseCounter(byte pin) {
  // 74LS93 increases on LOW pulse
  digitalWrite(CP, HIGH);
  delay(1);
  digitalWrite(CP, LOW);
}

void setup() {
  // Pin definition
  pinMode(Q0, INPUT);
  pinMode(Q1, INPUT);
  pinMode(Q2, INPUT);
  pinMode(Q3, INPUT);
  pinMode(CP, OUTPUT);
  pinMode(LR, OUTPUT);
  pinMode(LA, OUTPUT);
  pinMode(LV, OUTPUT);

  // Output clearing
  digitalWrite(CP, LOW);
  digitalWrite(LR, LOW);
  digitalWrite(LA, LOW);
  digitalWrite(LV, LOW);

  // Comms
  Serial.begin(9600);
}

void loop() {
  // Update current time
  currTime = millis();

  // Read counter binary outputs
  bin0 = digitalRead(Q0);
  bin1 = digitalRead(Q1);
  bin2 = digitalRead(Q2);
  bin3 = digitalRead(Q3);

  // Print binary number to serial monitor
  Serial.println(String(bin3) + String(bin2) + String(bin1) + String(bin0));

  // Reset the leds' states
  stateLR = false;
  stateLA = false;
  stateLV = false;

  // Turn on one led's state based on the counter
  if (!bin3 && (!bin1 || (!bin2 && bin1))) stateLR = true;
  if (bin2 &&  bin1) stateLA = true;
  if (bin3 && (!bin1 || (!bin2 && bin1))) stateLV = true;

  // Write the states to the leds
  digitalWrite(LR, stateLR);
  digitalWrite(LA, stateLA);
  digitalWrite(LV, stateLV);

  // Increase the counter every interval (1s)
  incrRel = currTime - incrTime;
  if (incrRel >= INCR_INTERVAL) {
    increaseCounter(CP);
    incrTime = millis();
  }
}
