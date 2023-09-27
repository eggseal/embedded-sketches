/*
 * Name: -
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   ...
 */

//  Libraries
#include <Wire.h> //  Built-in
#include <Keypad.h> //  "Keypad" by "Mark Stanley, Alexander Brevig"
#include <LiquidCrystal_I2C.h> //  "LiquidCrystal I2C" by "Frank de Brabander"

//  Pins
#define SENSOR_1 30
#define SENSOR_2 31
#define SENSOR_3 32
#define SENSOR_4 33
#define BAND_R 22
#define BAND_L 23

//  States
#define STATE_PAUSED 0
#define STATE_START 1
#define STATE_MOVING 2
#define STATE_STAY 3
#define STATE_STOP 4

//  Constants
const byte ROWS = 4;
const byte COLS = 3;
const byte ROW_PINS[ROWS] = { 2, 3, 4, 5 };
const byte COL_PINS[COLS] = { 6, 7, 8 };
const char KEY[ROWS][COLS] = {
  { '1', '2', '3' },
  { '4', '5', '6' },
  { '7', '8', '9' },
  { '*', '0', '#' }
};

//  Library constants
Keypad keypad = Keypad(makeKeymap(KEY), ROW_PINS, COL_PINS, ROWS, COLS);
LiquidCrystal_I2C lcd(0x27, 16, 2);

//  Variables
bool PAUSED = false;
int state = STATE_START;
int goalNum, goal, position = 0;
bool sensorOld, sensorNew = false;

//  Time variables
unsigned long timeInit, timeRel, timeCurr = 0;
unsigned int timeStay = 0;

void setup() {
  //  Library initalization
  lcd.init();
  lcd.backlight();
  
  //  Pin definition
  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);
  pinMode(BAND_R, OUTPUT);
  pinMode(BAND_L, OUTPUT);

  //  Output cleaning
  digitalWrite(BAND_R, LOW);
  digitalWrite(BAND_L, LOW);

  //  Randomizer
  randomSeed(analogRead(A0));

  //  Comms
  Serial.begin(9600);
}

void loop() {
  timeCurr = millis();
  timeRel = timeCurr - timeInit;  

  char key = keypad.getKey();

  Serial.print("goalNum: ");
  Serial.print(goalNum);
  Serial.print(", goal: ");
  Serial.print(goal);
  Serial.print(", position: ");
  Serial.print(position);
  Serial.print(", timeStayPrint: ");
  Serial.print(String((int) (timeStay / 1000)));
  Serial.print(", state: ");
  Serial.print(state);
  Serial.print(", state is STOP: ");
  Serial.println(state == STATE_STOP);

  if (digitalRead(SENSOR_1) == HIGH) position = 1;
  else if (digitalRead(SENSOR_2) == HIGH) position = 2;
  else if (digitalRead(SENSOR_3) == HIGH) position = 3;
  else if (digitalRead(SENSOR_4) == HIGH) position = 4;

  switch(state) {
    case STATE_START:
      lcd.setCursor(0, 0);
      lcd.print("Goal Amount...");
      lcd.setCursor(0, 1);
      lcd.print("(Press a number)");
      if (key == NO_KEY || key == '*' || key == '#') return;

      goalNum = key - '0';
      goal = newGoal();
      lcd.clear();
      state = STATE_MOVING;
      timeInit = millis();
      break;
    case STATE_PAUSED:
      lcd.setCursor(0, 0);
      lcd.print("Paused...");
      moveBand(LOW, LOW);
      lcd.setCursor(0, 1);
      lcd.print("(#) to continue");
      if (key != '#') return;

      lcd.clear();
      state = STATE_MOVING;
      timeInit = millis();
      break;
    case STATE_MOVING:
      lcd.setCursor(0, 0);
      lcd.print("Moving to S" + String(goal) + "...");
      lcd.setCursor(0, 1);
      lcd.print("(*) to pause");

      if (position < goal) moveBand(HIGH, LOW);
      else if (position > goal) moveBand(LOW, HIGH);
      else STATE_MOVE_TO_STAY();

      if (goalNum <= 0) return STATE_MOVE_TO_STOP();
      if (key == '*') STATE_MOVE_TO_PAUSED();
      break;
    case STATE_STAY:
      lcd.setCursor(0, 0);
      lcd.print("Stay in S" + String(position) + "...");
      lcd.setCursor(0, 1);
      lcd.print("for " + String((int) (timeStay / 1000)) + " secs");
      moveBand(LOW, LOW);
      if (timeRel <= timeStay) return;
      state = STATE_MOVING;
      break;
    case STATE_STOP:
      lcd.setCursor(0, 0);
      lcd.print("Finished.");
      lcd.setCursor(0, 1);
      lcd.print("(#) to restart");

      if (key == '#') STATE_STOP_TO_START();
      break;
  }
}

int newGoal() {
  int goal;
  do {
    goal = random(1, 5);
  } while (goal == position);
  return goal;
}

void moveBand(bool left, bool right) {
  digitalWrite(BAND_R, right);
  digitalWrite(BAND_L, left);
}

void STATE_MOVE_TO_STOP() {
  state = STATE_STOP;
  Serial.println("Stopping....");
  moveBand(LOW, LOW);
  lcd.clear();
}

void STATE_MOVE_TO_PAUSED() {
  state = STATE_PAUSED;
  lcd.clear();
}

void STATE_MOVE_TO_STAY() {
  goalNum--;
  goal = newGoal();
  timeInit = millis();
  timeStay = random(1, 5) * 1000;
  state = STATE_STAY;
  lcd.clear();
}

void STATE_STOP_TO_START() {
  goalNum = 0;
  state = STATE_START;
  lcd.clear();
}