#include "Arduino.h"
#include <Servo.h>

#define PIN_FOOT_LEFT   5
#define PIN_FOOT_RIGTH  9
#define PIN_LEG_LEFT    10
#define PIN_LEG_RIGTH   11

#define STEP_DOWN 135
#define STEP_UP 90

#define FOOTR_FORWARD 110
#define FOOTR_BACKWARD 70
#define FOOTR_NEUTRAL 90

#define FOOTL_FORWARD 70
#define FOOTL_BACKWARD 110
#define FOOTL_NEUTRAL 90

#define STEP_UP_THRESHOLD 15


typedef enum LimbState {
  REST,
  FOOT_UP,
  FOOT_UP_FORWARD,
  FOOT_UP_BACKWARD,
  FOOT_DOWN_FORWARD,
  FOOT_DOWN_BACKWARD
};

class LIMB: public Servo {

  public:
    LIMB(byte pin, int pos, int max, int min);
    void Move();
    void SetPos(int pos);
    bool IsMoving();
    bool IsFootUp();
    bool IsFootDown();

    void Rest();
    void Forward();
    void Backward();
    void StepUp();
    void StepDown();

    int CurrentPos;
    int TargetPos;

  private:
    int _min; //min servo position
    int _max; //max servo position
    int _def; //default servo position
    int _pin;
};

void LIMB::Forward() {
  TargetPos = _max;
}

void LIMB::Backward() {
  TargetPos = _min;
}

void LIMB::StepDown() {
  TargetPos = _max;
}

void LIMB::StepUp() {
  TargetPos = _min;
}

LIMB::LIMB(byte pin, int pos, int max, int min) {
  _pin = pin;
  //attach(pin);
  _max = max;
  _min = min;
  if (pos > 0 && pos < 180)
    _def = pos;
  else
    _def = 90;

  CurrentPos = _def;
  TargetPos = _def;
}

void LIMB::Move() {

  if (CurrentPos == TargetPos) {

  } else if (CurrentPos > TargetPos) {
    CurrentPos--;
  }
  else {
    CurrentPos++;
  }
  write(CurrentPos);
}


void LIMB::Rest() {
  write(_def);
}

void LIMB::SetPos(int pos) {
  TargetPos = pos;
}

bool LIMB::IsMoving() {

  if (CurrentPos == TargetPos) {
    return false;
  } else {
    return true;
  }
}

bool LIMB::IsFootUp() {
  if (CurrentPos < _max - STEP_UP_THRESHOLD) {
    return true;
  } else {
    return false;
  }
}

bool LIMB::IsFootDown() {
  if (CurrentPos == _max) {
    return true;
  } else {
    return false;
  }
}

