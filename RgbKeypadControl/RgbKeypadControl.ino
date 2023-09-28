/*
  Name: RGB Keypad Control
  Version: 1.0
  Author: eggseal
  Description:
    This program controls the colors of an RGB LED with the use of a Matrix Keypad
*/

//  Libraries
#include <Keypad.h> //  "Keypad" by "Mark Stanley, Alexander Brevig"

//  Pins
#define LED_R 23 //  RGB Led red color pin
#define LED_G 24 //  RGB Led green color pin
#define LED_B 25 //  RGB Led blue color pin

//  Constants
const unsigned short ROWS = 4; //  Amount of rows of matrix keypad
const unsigned short COLS = 3; //  Amount of columns of matrix keypad
const byte ROW_PINS[ROWS] = {2, 3, 4, 5}; //  Pins of keypad rows
const byte COL_PINS[COLS] = {6, 7, 8}; //  Pins of keypad columns
const char KEYS[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
}; //  Keypad character matrix

//  Library constants
Keypad keypad = Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);

//  States
#define STATE_R 0 //  Waits for input on the red color
#define STATE_G 1 //  Waits for input on the green color
#define STATE_B 2 //  Waits for input on the blue color
#define END 3 //  Finished program, waits for reset input

// #define DEBUG

//  Variables
char key; //  Character pressed on the keypad
bool value; //  Character value; 0: LOW, else: HIGH
int state = STATE_R; //  Current state of the program

void setup() {
  //  Pin definition
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);

  //  Output cleaning
  digitalWrite(LED_R, LOW);
  digitalWrite(LED_G, LOW);
  digitalWrite(LED_B, LOW);

  //  Debug definition
  #ifdef DEBUG
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(37, OUTPUT);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(36, LOW);
  digitalWrite(37, LOW);
  #endif

  //  Comms
  Serial.begin(9600);
}

void loop() {
  //  Get the pressed key and its boolean value
  key = keypad.getKey();
  value = key ? (int) key > 48 : false;

  #ifdef DEBUG
  if (key) Serial.println(key);
  digitalWrite(34, 34 + state == 34);
  digitalWrite(35, 34 + state == 35);
  digitalWrite(36, 34 + state == 36);
  digitalWrite(37, 34 + state == 37);
  #endif

  //  Stop and restart key
  if (key == '*') {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
    state = STATE_R;
    return;
  }

  switch(state) {
    //  Wait for input on red color
    case STATE_R:
      if (!key) break;
      digitalWrite(LED_R, HIGH);
      delay(50);

      digitalWrite(LED_R, value);
      state = STATE_G;
      break;
    //  Wait for input on green color
    case STATE_G:
      if (!key) break;
      digitalWrite(LED_G, HIGH);
      delay(50);

      digitalWrite(LED_G, value);
      state = STATE_B;
      break;
    //  Wait for input on blue color
    case STATE_B:
      if (!key) break;
      digitalWrite(LED_B, HIGH);
      delay(50);

      digitalWrite(LED_B, value);
      state = END;
      break;
    //  Wait for input on reset key
    case END:
      if (key != '#') break;

      digitalWrite(LED_R, LOW);
      digitalWrite(LED_G, LOW);
      digitalWrite(LED_B, LOW);
      state = STATE_R;
      break;
  }
}

