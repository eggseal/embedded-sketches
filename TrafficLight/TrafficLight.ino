/**
 * Name: TrafficLight
 * Version: 1.0
 * Author: eggseal
 * Description:
 *   Controls the states of a traffic light with pedestrian light with cross button using a finite state machine
 */

//  Pins
#define CAR_GREEN 22
#define CAR_YELLOW 23
#define CAR_RED 24
#define PED_GREEN 25
#define PED_RED 26
#define PULSE 30

//  States
#define STATE_0 0
#define STATE_1 1
#define STATE_2 2

//  Variables
bool blink = true;
bool pulsed = false;
int NEXT = STATE_0;

//  Time variables
unsigned long currTime, initTime, stateTime = 0;
unsigned long lastBlink = 0;



void setup() {
  //  Pin definition
  pinMode(CAR_GREEN, OUTPUT);
  pinMode(CAR_YELLOW, OUTPUT);
  pinMode(CAR_RED, OUTPUT);
  pinMode(PED_GREEN, OUTPUT);
  pinMode(PED_RED, OUTPUT);
  pinMode(PULSE, INPUT);

  //  Output cleaning
  digitalWrite(CAR_GREEN, LOW);
  digitalWrite(CAR_YELLOW, LOW);
  digitalWrite(CAR_RED, LOW);
  digitalWrite(PED_GREEN, LOW);
  digitalWrite(PED_RED, LOW);

}

void loop() {
  currTime = millis();
  stateTime = currTime - initTime;

  //  If pedestrian button is pressed and pedestrian light isn't green
  if (digitalRead(PULSE) == HIGH && NEXT != STATE_2) {
    //  Change state to pedestrian green
    NEXT = STATE_2;
    blink = true;
    pulsed = true;

    //  Update last state change time
    initTime = millis();
  }

  switch (NEXT) {
    case STATE_0:
      //  Traffic light to green
      digitalWrite(CAR_GREEN, HIGH);
      digitalWrite(CAR_YELLOW, LOW);
      digitalWrite(CAR_RED, LOW);

      //  Pedestrian light to red
      digitalWrite(PED_GREEN, LOW);
      digitalWrite(PED_RED, HIGH);

      //  Change after 4s to traffic yellow
      if (stateTime >= 4000) {
        NEXT = STATE_1;
        initTime = millis();
      }

      //  Changed without pulse
      pulsed = false;
      break;
    case STATE_1:
      //  Traffic light to yellow
      digitalWrite(CAR_GREEN, LOW);
      digitalWrite(CAR_YELLOW, HIGH);
      digitalWrite(CAR_RED, LOW);

      //  Change after 0.5s to traffic light red
      if (stateTime >= 500) {
        NEXT = STATE_2;
        initTime = millis();
      }

      //  Changed without pulse
      pulsed = false;
      break;
    case STATE_2:
      //  Traffic light to red
      digitalWrite(CAR_GREEN, LOW);
      digitalWrite(CAR_YELLOW, LOW);
      digitalWrite(CAR_RED, HIGH);

      //  Start blinking if its been 1.5s after pulsing
      if (stateTime >= 1500 && pulsed) {
        //  Change light state every 0.25s
        if ((currTime - lastBlink) >= 250) {
          lastBlink = millis();
          blink = !blink;
        }
      } //  If no pulse or less than 1.5s keep the light on
      else {
        blink = true;
      }

      //  Pedestrian light to green blink
      digitalWrite(PED_GREEN, blink);
      digitalWrite(PED_RED, LOW);

      //  Change after 3s to traffic green
      if (stateTime >= 3000) {
        NEXT = STATE_0;
        initTime = millis();
      }
      break;
  }
}
