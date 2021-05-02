#include "limb.h"


class BUG_AI {

  public:
    BUG_AI();
    void begin();
    void StepForward();
    void StepBackward();
    void TurnRigth();
    void TurnLeft();
    void StepRigthForward();
    void StepLeftForward();
    void StepRigthBackward();
    void StepLeftBackward();
    void Print();


    LIMB *left_foot;
    LIMB *rigth_foot;
    LIMB *left_leg;
    LIMB *rigth_leg;
  private:
    LimbState left_state, rigth_state;
};

BUG_AI::BUG_AI() {
  left_foot   = new LIMB(PIN_FOOT_LEFT, STEP_DOWN, STEP_DOWN, STEP_UP);
  rigth_foot  = new LIMB(PIN_FOOT_RIGTH, STEP_DOWN, STEP_DOWN, STEP_UP);
  left_leg    = new LIMB(PIN_LEG_LEFT, FOOTL_NEUTRAL, FOOTL_FORWARD, FOOTL_BACKWARD);
  rigth_leg   = new LIMB(PIN_LEG_RIGTH, FOOTR_NEUTRAL, FOOTR_FORWARD, FOOTR_BACKWARD);

  left_state = REST;
  rigth_state = REST;
}


void BUG_AI::begin() {
  left_foot->attach(PIN_FOOT_LEFT);
  rigth_foot->attach(PIN_FOOT_RIGTH);
  left_leg->attach(PIN_LEG_LEFT);
  rigth_leg->attach(PIN_LEG_RIGTH);
}

void BUG_AI::StepForward() {
  StepRigthForward();
  StepLeftForward();
}

void BUG_AI::StepBackward() {
  StepRigthBackward();
  StepLeftBackward();
}

void BUG_AI::TurnRigth() {
  StepRigthBackward();
  StepLeftForward();
}
void BUG_AI::TurnLeft() {
  StepLeftBackward();
  StepRigthForward();
}


void BUG_AI::StepRigthForward() {

  switch (rigth_state)
  {
    //dinlen
    case REST:
      if (left_state == FOOT_DOWN_BACKWARD || left_state == REST)
      {
        rigth_foot->SetPos(STEP_UP);
        rigth_state = FOOT_UP;
      }
      break;
    //ayağı kaldırmasını bekle
    case FOOT_UP:
      if ( rigth_foot->IsFootUp())
      {
        rigth_state = FOOT_UP_FORWARD;
        rigth_leg->SetPos( FOOTR_FORWARD );
      }
      break;
    //ayağın ileri adım atmasını bekle
    case FOOT_UP_FORWARD:
      if ( !rigth_leg->IsMoving())
      {
        rigth_state = FOOT_DOWN_FORWARD;
        rigth_foot->SetPos(STEP_DOWN);
      }
      break;
    //ayağın basmasını bekle
    case FOOT_DOWN_FORWARD:
      if ( rigth_foot->IsFootDown())
      {
        rigth_state = FOOT_DOWN_BACKWARD;
        rigth_leg->SetPos( FOOTR_BACKWARD );
      }

      break;
    //ayağın geri atmasını bekle
    case FOOT_DOWN_BACKWARD:
      if ( !rigth_leg->IsMoving())
      {
        rigth_state = REST;
      }

      break;

    case FOOT_UP_BACKWARD:
      rigth_state = REST;
      break;

    default:
      rigth_state = REST;
      break;
  }

  rigth_leg->Move();
  rigth_foot->Move();
}




void BUG_AI::StepLeftForward() {

  switch (left_state)
  {
    case REST:
      if (rigth_state == FOOT_DOWN_BACKWARD || rigth_state == REST)
      {
        left_foot->SetPos(STEP_UP);
        left_state = FOOT_UP;
      }
      break;

    case FOOT_UP:
      if ( left_foot->IsFootUp())
      {
        left_state = FOOT_UP_FORWARD;
        left_leg->SetPos( FOOTL_FORWARD );
      }
      break;

    case FOOT_UP_FORWARD:
      if ( !left_leg->IsMoving())
      {
        left_state = FOOT_DOWN_FORWARD;
        left_foot->SetPos(STEP_DOWN);
      }
      break;

    case FOOT_DOWN_FORWARD:
      if ( left_foot->IsFootDown())
      {
        left_state = FOOT_DOWN_BACKWARD;
        left_leg->SetPos( FOOTL_BACKWARD );
      }

      break;

    case FOOT_DOWN_BACKWARD:
      if ( !left_leg->IsMoving())
      {
        left_state = REST;
      }

      break;

    case FOOT_UP_BACKWARD:
      left_state = REST;
      break;
    default:
      left_state = REST;
      break;
  }

  left_leg->Move();
  left_foot->Move();
}

void BUG_AI::StepRigthBackward() {

  switch (rigth_state)
  {
    //dinlen
    case REST:
      if (left_state == FOOT_DOWN_FORWARD || left_state == REST)
      {
        rigth_foot->SetPos(STEP_UP);
        rigth_state = FOOT_UP;
      }
      break;
    //ayağı kaldırmasını bekle
    case FOOT_UP:
      if ( rigth_foot->IsFootUp())
      {
        rigth_state = FOOT_UP_BACKWARD;
        rigth_leg->SetPos( FOOTR_BACKWARD );
      }
      break;
    //ayağın geri adım atmasını bekle
    case FOOT_UP_BACKWARD:
      if ( !rigth_leg->IsMoving())
      {
        rigth_state = FOOT_DOWN_BACKWARD;
        rigth_foot->SetPos(STEP_DOWN);
      }
      break;
    //ayağın basmasını bekle
    case FOOT_DOWN_BACKWARD:
      if ( rigth_foot->IsFootDown())
      {
        rigth_state = FOOT_DOWN_FORWARD;
        rigth_leg->SetPos( FOOTR_FORWARD );
      }

      break;
    //ayağın iler atmasını bekle
    case FOOT_DOWN_FORWARD:
      if ( !rigth_leg->IsMoving())
      {
        rigth_state = REST;
      }

      break;

    case FOOT_UP_FORWARD:
      rigth_state = REST;
      break;

    default:
      rigth_state = REST;
      break;
  }

  rigth_leg->Move();
  rigth_foot->Move();
}


void BUG_AI::StepLeftBackward() {

  switch (left_state )
  {
    //dinlen
    case REST:
      if (rigth_state == FOOT_DOWN_FORWARD || left_state == REST)
      {
        left_foot->SetPos(STEP_UP);
        left_state = FOOT_UP;
      }
      break;
    //ayağı kaldırmasını bekle
    case FOOT_UP:
      if ( left_foot->IsFootUp())
      {
        left_state = FOOT_UP_BACKWARD;
        left_leg->SetPos( FOOTR_BACKWARD );
      }
      break;
    //ayağın geri adım atmasını bekle
    case FOOT_UP_BACKWARD:
      if ( !left_leg->IsMoving())
      {
        left_state = FOOT_DOWN_BACKWARD;
        left_foot->SetPos(STEP_DOWN);
      }
      break;
    //ayağın basmasını bekle
    case FOOT_DOWN_BACKWARD:
      if ( left_foot->IsFootDown())
      {
        left_state = FOOT_DOWN_FORWARD;
        left_leg->SetPos( FOOTR_FORWARD );
      }

      break;
    //ayağın iler atmasını bekle
    case FOOT_DOWN_FORWARD:
      if ( !left_leg->IsMoving())
      {
        left_state = REST;
      }

      break;


    case FOOT_UP_FORWARD:
      left_state = REST;
      break;

    default:
      left_state = REST;
      break;
  }

  left_leg->Move();
  left_foot->Move();
}


void BUG_AI::Print() {

  Serial.print(" RF: ");
  Serial.print(rigth_foot->CurrentPos);
  Serial.print(" LF: ");
  Serial.print(left_foot->CurrentPos);
  Serial.print(" RL: ");
  Serial.print(rigth_leg->CurrentPos);
  Serial.print(" LL: ");
  Serial.print(left_leg->CurrentPos);

  Serial.print(" Lstate: ");
  Serial.print(left_state);
  Serial.print(" Rstate: ");
  Serial.println(rigth_state);

}
