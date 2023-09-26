/**
 * Name: RGB Keypad Control
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   This program controls the colors of an RGB LED with the use of a Matrix Keypad
 */

//  Libraries
#include <Keypad.h>

//  Pins
#define LED_R 25
#define LED_G 23
#define LED_B 24

//  Constants
const unsigned short ROWS = 4;
const unsigned short COLS = 3;
const byte ROW_PINS[ROWS] = {2, 3, 4, 5};
const byte COL_PINS[COLS] = {6, 7, 8};
const char KEYS[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};

//  Library constants
Keypad keypad = Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);

//  States
#define STATE_R 0
#define STATE_G 1
#define STATE_B 2
#define END 3

//  Variables
char key;
bool value;
int state = STATE_R;

void setup() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  Serial.begin(9600);
}

void loop() {
  key = keypad.getKey();
  value = key ? (int) key > 48 : false;

  if (key == '*') {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    state = STATE_R;
    return;
  }

  switch(state) {
    case STATE_R:
      if (!key) break;
      digitalWrite(LED_R, HIGH);
      delay(50);

      digitalWrite(LED_R, value);
      state = STATE_G;
      break;
    case STATE_G:
      if (!key) break;
      digitalWrite(LED_G, HIGH);
      delay(50);

      digitalWrite(LED_G, value);
      state = STATE_B;
      break;
    case STATE_B:
      if (!key) break;
      digitalWrite(LED_B, HIGH);
      delay(50);

      digitalWrite(LED_B, value);
      state = END;
      break;
    case END:
      if (key != '#') break;

      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      state = STATE_R;
      break;
  }
}

