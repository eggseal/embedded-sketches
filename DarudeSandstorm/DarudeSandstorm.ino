// Libraries
#include "pitches.h"
#include "times.h"

// Pin I/O
#define BUZZER 2

// Constants
#define XX 0,
#define FN -1
const float SEQ[] = {
  B4  B4  B4  B4  B4  XX  XX  XX
  XX  D5  XX
  B4  B4  B4  B4  B4  XX  XX  XX
  XX  
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  A6  G6  FS6 E6  D6  C6  B5  A5  G5  FS5 E5  D5  C5  B4  A4  G4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // Start
  E5  E5  E5  E5  E5  D5  D5  D5  D5  D5  D5  A4  A4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // End
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // Start
  E5  E5  E5  E5  E5  D5  D5  D5  D5  D5  D5  A4  A4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // End
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // Start
  E5  E5  E5  E5  E5  D5  D5  D5  D5  D5  D5  A4  A4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // End
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // Start
  E5  E5  E5  E5  E5  D5  D5  D5  D5  D5  D5  A4  A4
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5
  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  B4  E5  E5 // End
  XX  FN
}; // The pitch of the note 
const float AM_16THS[] = {
  Q4  Q4  Q4  Q4  Q4  Q4  Q2  N2 
  N2  N1  N1
  Q4  Q4  Q4  Q4  Q4  Q4  Q2  N2
  N4 
  Q4  Q4  Q4  Q4  N1  Q4  Q4  Q4  Q4  N1 
  Q4  Q4  Q4  Q4  N1  Q4  Q4  Q4  Q4  N1 
  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  
  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q4  Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16 Q16
  Q4  Q4  Q4  Q2  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // Start
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // End
  Q4  Q4  Q4  Q2  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // Start
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // End
  Q4  Q4  Q4  Q2  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // Start
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // End
  Q4  Q4  Q4  Q2  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // Start
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4
  Q4  Q4  Q4  Q4  Q2  Q4  Q4  Q4  Q4  Q4  Q4  Q2  Q4  Q4 // End
  N1  FN
}; // The length of the note measured in 16ths of a beaths

// Variables
unsigned int idx = 0;
float current = SEQ[idx];
float len = 448 / AM_16THS[idx];

void setup() {
  // Pin definition
  pinMode(BUZZER, OUTPUT);

  // Comms
  Serial.begin(115200);
}

void loop() {
  // The sequence has ended
  if (current == FN) return;
  Serial.printf("Note: %f, Length: %f, Position: %d\n", current, len, idx);

  // Play the sound for the paired duration and turn it of 5ms before the next
  tone(BUZZER, current, len*0.75);
  delay(len);
  noTone(BUZZER);

  // Get the current note of the sequence and advance
  idx++;
  current = SEQ[idx];
  len = 410 / AM_16THS[idx];
}

void volTone(int pin, int frequency, int duration) {
  if (frequency == 0) return;
  long period = 1000000L / frequency; // Period in microseconds
  long halfPeriod = period / 2;
  long cycles = (long) frequency * duration / 1000;

  for (long i = 0; i < cycles; i++) {
    analogWrite(pin, 2); // Turn the pin on with the specified volume
    delayMicroseconds(halfPeriod);
    analogWrite(pin, 0);      // Turn the pin off
    delayMicroseconds(halfPeriod);
  }
}
