#include <Servo.h>
#include "ai.h"

Servo servo_test;
#define servo_test_pin 6

#define STEP_DELAY 5 //milisecond one step takes ~200 loops one step 1 second

BUG_AI bug;

void setup() {

  Serial.begin(9600);

  servo_test.attach(servo_test_pin);
  servo_test.write(90);

  bug.begin();
  delay(1000);
}

void loop() {
  delay(STEP_DELAY);
  bug.StepForward();
  //bug.StepBackward();
  //bug.TurnRigth();
  //bug.TurnLeft();
  //bug.Print();
}
