// I/O pins
#define GND 53 
#define SWITCH 25   
#define LEDR 10  
#define LEDG 9
#define LEDB 8
#define LDR A0

// Variables
int lightAdc = 0;
bool switchState = false;

// Time variables
unsigned long lastSwitch = 0;

// Sub-routines
void writeRgb(bool red, bool green, bool blue) {
  digitalWrite(LEDR, red);
  digitalWrite(LEDG, green);
  digitalWrite(LEDB, blue);
}

void setup() {
  // Pin definition
  pinMode(GND, OUTPUT);
  pinMode(SWITCH, OUTPUT);
  pinMode(LEDR, OUTPUT);
  pinMode(LEDG, OUTPUT);
  pinMode(LEDB, OUTPUT);

  // Output setup
  digitalWrite(GND, LOW);
  digitalWrite(SWITCH, LOW);
  digitalWrite(LEDR, LOW);
  digitalWrite(LEDG, LOW);
  digitalWrite(LEDB, LOW);

  // Comms
  Serial.begin(9600);
}

void loop() {
  lightAdc = analogRead(LDR);
  if (lightAdc < 0.25 * 1024) writeRgb(1, 0, 0);
  else if (lightAdc < 0.5 * 1024) writeRgb(0, 1, 0);
  else if (lightAdc < 0.75 * 1024) writeRgb(0, 0, 1);
  else if (lightAdc < 1024) writeRgb(1, 0, 1);
  else writeRgb(0, 0, 0);

  Serial.println(lightAdc);

  delay(50);

  if (millis() - lastSwitch > 1000) {
    switchState = !switchState;
    digitalWrite(SWITCH, switchState);
    lastSwitch = millis();
  }
}
