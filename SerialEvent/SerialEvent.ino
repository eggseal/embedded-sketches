// Pin I/O
#define LED 2 // Built-in LED

// Variables
String msg = ""; // Serial input message
bool complete = false; // Flag message transfer completion
bool blink = false; // Flag LED blinking state
unsigned long lastBlink = 0; // Last LED change time on blink

void setup() {
  // Pin definition
  pinMode(LED, OUTPUT);

  // Comms
  Serial.begin(115200);
}

void loop() {
  // Toggle LED if blink mode is on and 1s has passed since last change
  if (blink && millis() - lastBlink > 1000) {
    digitalWrite(LED, !digitalRead(LED));
    lastBlink = millis();
  }

  // Return early if message isn't fully received
  if (!complete) return;
  // Handle serial input from this point
  msg.toLowerCase();

  // Switch the LED mode from the input
  blink = false;
  if (msg == "on") digitalWrite(LED, HIGH);
  else if (msg == "off") digitalWrite(LED, LOW);
  else if (msg == "blink") blink = true;

  // Reset input variables
  msg = "";
  complete = false;
}

void serialEvent() {
  // Loop until serial input is empty
  while (Serial.available()) {
    // Read the next byte as a character
    char input = (char) Serial.read();
    // Mark as completed and exit the loop on end of line
    if (input == '\n') {
      Serial.println(">> " + msg);
      complete = true;
      break;
    }
    // Append character to the message
    msg += input;
  }
}