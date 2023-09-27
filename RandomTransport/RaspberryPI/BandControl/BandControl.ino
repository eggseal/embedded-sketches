#define SENSOR_1 30
#define SENSOR_2 31
#define SENSOR_3 32
#define SENSOR_4 33

#define BAND_R 22
#define BAND_L 23

#define STATE_STALE -1
#define STATE_PAUSED 0
#define STATE_START 1
#define STATE_MOVING 2
#define STATE_STAY 3
#define STATE_STOP 4
int state = STATE_STALE;

unsigned long timeInit, timeCurr, timeRel = 0;
int timeStay, goalNum, goal, position = 0;

void setup() {
 	Serial.begin(9600);
  randomSeed(analogRead(A0));

  pinMode(SENSOR_1, INPUT);
  pinMode(SENSOR_2, INPUT);
  pinMode(SENSOR_3, INPUT);
  pinMode(SENSOR_4, INPUT);

  pinMode(BAND_R, OUTPUT);
  pinMode(BAND_L, OUTPUT);
  moveBand(LOW, LOW);
}

void loop() {
  timeCurr = millis();
  timeRel = timeCurr - timeInit; 

  char key = readSerialPort();    

  if (digitalRead(SENSOR_1) == HIGH) position = 1;
  else if (digitalRead(SENSOR_2) == HIGH) position = 2;
  else if (digitalRead(SENSOR_3) == HIGH) position = 3;
  else if (digitalRead(SENSOR_4) == HIGH) position = 4;

  switch (state) {
    //  INITIAL AND FINAL STATE. WAITS FOR INPUT RESTART
    case STATE_STALE:
      if (key != '1') break;
      Serial.print("System started.");
      delay(10);
      state = STATE_START;
      break;

    //  WAITS FOR INPUT DATA BEFORE BEGINNING TO MOVE
    case STATE_START:
      if (key == ' ') return;
      goalNum = key - '0';
      goal = generateNewGoal();

      Serial.print("Generated [" + String(goalNum) + "] destinations.");
      Serial.print("Moving to S" + String(goal) + "...");
      state = STATE_MOVING;
      timeInit = millis();
      break;

    //  STOPS THE BAND AND WAITS FOR INPUT TO CONTINUE
    case STATE_PAUSED:
      moveBand(LOW, LOW);
      if (key != '3') break;

      Serial.print("Resumed the movement.");
      state = STATE_MOVING;
      timeInit = millis();
      break;

    //  MANAGES ALL MOVEMENT OF THE BAND
    case STATE_MOVING:
      if (position < goal) moveBand(HIGH, LOW);
      else if (position > goal) moveBand(LOW, HIGH);
      else STATE_MOVE_TO_STAY();

      if (goalNum <= 0) return STATE_MOVE_TO_STOP();
      if (key == '2') STATE_MOVE_TO_PAUSED();
      break;

    //  WAIT TIME BEFORE RESUMING MOVEMENT
    case STATE_STAY:
      moveBand(LOW, LOW);
      if (timeRel < timeStay) break;
      state = STATE_MOVING;
      break;

    //  FINISHED MESSAGE
    case STATE_STOP:
      Serial.print("Finished.");
      state = STATE_STALE;
      break;
  }
}

int generateNewGoal() {
  while (true) {
    int newGoal = random(1, 5);
    if (newGoal != position) return newGoal;
  }
}

void moveBand(bool left, bool right) {
  digitalWrite(BAND_R, right);
  digitalWrite(BAND_L, left);
}

void STATE_MOVE_TO_STAY() {
  goalNum--;
  goal = generateNewGoal();
  timeInit = millis();
  timeStay = random(1, 5) * 1000;
  Serial.print("Staying on S" + String(position) + " for " + String(timeStay / 1000) + " seconds.");
  state = STATE_STAY;
}

void STATE_MOVE_TO_STOP() {
  state = STATE_STOP;
  Serial.println("Stopping...");
  moveBand(LOW, LOW);
}

void STATE_MOVE_TO_PAUSED() {
  Serial.println("Paused the movement.");
  state = STATE_PAUSED;
}

void STATE_STOP_TO_START() {
  goalNum = 0;
  state = STATE_START;
}

char readSerialPort() {
  if (!Serial.available()) return ' ';

  delay(10);
  char key = (char) Serial.read();
  Serial.flush();
  return key;
}
