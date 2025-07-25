/* Stepper DM320T, Arduino Uno
 * For Motor stepper 24v test AR4 MK3 Robot
 * Wiring arduino:
 *  A0 to A3 Joystick to Arduino
 *  Connect to 5v from Arduino to Joystick
 *  Connect to ground from Arduino to Joystick
 * Stepper Driver:
 *  Pul_1  : Pin 2
 *  Dir_1   : Pin 3
 *  Pul_2  : Pin 4
 *  Dir_2   : Pin 5
 *  Pul_3  : Pin 6
 *  Dir_3   : Pin 7
 *  Opto  : 3.3v
 *  
 *  A+    : Black
 *  A-    : Green 
 *  B+    : Red
 *  B-    : Blue
 */

// Pin stepper motor
#define PUL1_PIN 2
#define DIR1_PIN 3
#define PUL2_PIN 4
#define DIR2_PIN 5
#define PUL3_PIN 6
#define DIR3_PIN 7
#define PUL4_PIN 8
#define DIR4_PIN 9
#define PUL5_PIN 10
#define DIR5_PIN 11
#define PUL6_PIN 12
#define DIR6_PIN 13

// Joystick input
#define J1 A0
#define J2 A1
#define J3 A2
#define J4 A3
#define J5 A4
#define J6 A5

// Variabel last time and state step motor
unsigned long lastStep[6] = {0, 0, 0, 0, 0, 0};
bool stepState[6] = {false, false, false, false, false, false};

// Interval time between step (microsecond)
const unsigned long stepInterval = 1000; // 500us HIGH, 500us LOW

void setup() {
  Serial.begin(115200);

  // Set semua pin sebagai OUTPUT
  int pulPins[6] = {PUL1_PIN, PUL2_PIN, PUL3_PIN, PUL4_PIN, PUL5_PIN, PUL6_PIN};
  int dirPins[6] = {DIR1_PIN, DIR2_PIN, DIR3_PIN, DIR4_PIN, DIR5_PIN, DIR6_PIN};

  for (int i = 0; i < 6; i++) {
    pinMode(pulPins[i], OUTPUT);
    pinMode(dirPins[i], OUTPUT);
  }
}

void loop() {
  int joystick[6];
  joystick[0] = analogRead(J1);
  joystick[1] = analogRead(J2);
  joystick[2] = analogRead(J3);
  joystick[3] = analogRead(J4);
  joystick[4] = analogRead(J5);
  joystick[5] = analogRead(J6);

  int pulPins[6] = {PUL1_PIN, PUL2_PIN, PUL3_PIN, PUL4_PIN, PUL5_PIN, PUL6_PIN};
  int dirPins[6] = {DIR1_PIN, DIR2_PIN, DIR3_PIN, DIR4_PIN, DIR5_PIN, DIR6_PIN};

  for (int i = 0; i < 6; i++) {
    if (joystick[i] > 800 || joystick[i] < 100) {
      digitalWrite(dirPins[i], joystick[i] > 800 ? LOW : HIGH);
      handleStepper(pulPins[i], &lastStep[i], &stepState[i]);
    }
  }
}

// Fungsi non-blocking sending step ke motor
void handleStepper(int pulPin, unsigned long* lastStepTime, bool* stepState) {
  unsigned long now = micros();
  if (now - *lastStepTime >= stepInterval / 2) {
    *lastStepTime = now;
    *stepState = !*stepState;
    digitalWrite(pulPin, *stepState ? HIGH : LOW);
  }
}
