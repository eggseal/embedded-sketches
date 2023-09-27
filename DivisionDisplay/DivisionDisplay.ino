/**
 * Name: DivisionDisplay
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   Makes a division between to numbers making use of a LCD display and a Matrix Keypad
 */

//  Libraries
#include <Wire.h> //  Built-in
#include <Keypad.h> //  "Keypad" by "Mark Stanley, Alexander Brevig"
#include <LiquidCrystal_I2C.h> //  "LiquidCrystal I2C" by "Frank de Brabander"

//  Constants
const byte ROWS = 4;
const byte COLS = 3;
const byte ROW_PINS[ROWS] = {2, 3, 4, 5};
const byte COL_PINS[COLS] = {6, 7, 8};
const char keys[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '/', '0', '=' }
};

//  Library constants
Keypad keypad = Keypad(makeKeymap(keys), ROW_PINS, COL_PINS, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//  Variables
int writing = 0;
int result = 0;
char key, keyUnit, keyDec;
int unit = 0;
int dec = 0;

//  Sub-routines
void write(char c, int &writing) {
  lcd.setCursor(writing, 1);
  lcd.print(c);
  delay(10);

  writing++;
  if (writing >= 16) writing = 0;
}

void setup() {
  //  Library initialization
  lcd.init();
  lcd.backlight();
  lcd.print("Teclado");

  //  Comms
  Serial.begin(9600);
}

void loop() {
  //  Get key and execute loop only when one is pressed
  key = keypad.getKey();
  if (key == NO_KEY) return;

  //  Convert the key to respective number
  unit = keyUnit - '0';
  dec = (keyDec - '0') * 10;

  if (key == '/') {
    //  Set the input value as the temporary result
    result += dec + unit;

    //  Reset the keys and restart the loop
    keyDec = '0';
    keyUnit = '0';
    write('/', writing);
    return;
  }
  if (key == '=') {
    //  Divide the stored result by the input number
    result /= dec + unit;

    //  Set a temporary writing index for writing at the end
    int w = 13;
    write((int) (result / 100) % 10, w);
    write((int) (result / 10) % 10, w);
    write(result % 10, w);

    //  Reset the result for the next operation
    result = 0;
  }

  //  Write the input is its written
  write(key, writing);

  //  Move the units to the next order
  keyDec = keyUnit;
  keyUnit = key;

  //  Debug prints
  Serial.println("-------------");
  Serial.println(result);
  Serial.println(keyUnit);
  Serial.println(keyDec);
}
