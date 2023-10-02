
/*
  Name: DivisionDisplay
  Version: 1.0
  Author: eggseal
  Description:
    Makes a division between to numbers making use of a LCD display and a Matrix Keypad
*/

//  Libraries
#include <Wire.h> //  Built-in
#include <LiquidCrystal.h> //  Built-in
#include <Keypad.h> //  "Keypad" by "Mark Stanley, Alexander Brevig"

#define DEBUG

//  Constants
const unsigned short ROWS = 4; //  Amount of rows of matrix keypad
const unsigned short COLS = 3; //  Amount of columns of matrix keypad
const byte ROW_PINS[ROWS] = {2, 3, 4, 5}; //  Pins of keypad rows
const byte COL_PINS[COLS] = {6, 7, 8}; //  Pins of keypad columns
const char KEYS[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'/', '0', '='}
}; //  Keypad character matrix

//  Library constants
Keypad KEYPAD = Keypad(makeKeymap(KEYS), ROW_PINS, COL_PINS, ROWS, COLS);
LiquidCrystal lcd(48, 49, 45, 44, 43, 42); //  RS E D4 D5 D6 D7

//  Variables
int writing = 0; //  The index of the screen's second line
int result = 0; //  The result of the operation
char key, keyUnit, keyTens; //  The input keys
int unit = 0; //  The value of the input units
int tens = 0; //  The value of the input tens

//  Sub-routines
/**
 * Write a character on the second line of the LCD screen in a given index and moves to the next
 * @param character The character to write
 * @param index The position of the character
 */
void writeLCD(char character, int &index) {
  //  Write on the index
  lcd.setCursor(index, 1);
  lcd.print(character);

  Serial.println("Writing " + String(character) + " on position " + String(index));
  delay(10);

  //  Move to the next position or loop around if at the end
  index++;
  if (index >= 16) index = 0;
}

void writeLCD(String text, int &index) {
    //  Write on the index
  lcd.setCursor(index, 1);
  lcd.print(text);

  Serial.println("Writing " + text + " on position " + String(index));
  delay(10);

  //  Move to the next position or loop around if at the end
  index++;
  if (index >= 16) index = 0;
}

void setup() {
  //  LCD RW Pin to GND
  pinMode(47, OUTPUT);
  digitalWrite(47, LOW);

  //  Library initialization
  lcd.begin(16, 2);
  lcd.print("Mensaje");

  //  Comms
  Serial.begin(9600);
}

void loop() {
  //  Get key and execute loop only when one is pressed
  key = KEYPAD.getKey();
  if (!key) return;

  //  Convert the key to respective number
  unit = keyUnit ? keyUnit - '0' : 0;
  tens = keyTens ? (keyTens - '0') * 10 : 0;

  //  Debug logs
  #ifdef DEBUG
  Serial.println();
  Serial.print("Unit: ");
  Serial.print(keyUnit);
  Serial.print(" - Value: ");
  Serial.println(unit);
  Serial.print("Tens: ");
  Serial.print(keyTens);
  Serial.print(" - Value: ");
  Serial.println(tens);
  #endif

  if (key == '/') {
    //  Set the input value as the temporary result
    result = tens + unit;

    //  Reset the keys and restart the loop
    keyTens = '0';
    keyUnit = '0';
    writeLCD('/', writing);

    #ifdef DEBUG
    Serial.println(result);
    #endif
    return;
  }
  if (key == '=') {
    //  Divide the stored result by the input number
    result /= tens + unit;

    //  Set a temporary writing index for writing at the end
    int w = 13;

    writeLCD(String((int) result / 100 % 10), w);
    writeLCD(String((int) result / 10 % 10), w);
    writeLCD(String(result % 10), w);

    //  Reset the result for the next operation
    #ifdef DEBUG
    Serial.println("Result: " + String(result));
    #endif
    result = 0;
  }

  //  Write the input is its written
  writeLCD(key, writing);

  //  Move the units to the next order
  keyTens = keyUnit ;
  keyUnit = key;
}
