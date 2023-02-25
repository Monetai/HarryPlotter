void MotorSetup()
{
  stepsPerMM = ((360/stepAngle)*microStepMulitplier)/(beltPitch*toothCount);
  
  motorA.setEnablePin(MOTOR_A_ENABLE_PIN);
  motorA.setPinsInverted(true, false, true); 
  
  motorB.setEnablePin(MOTOR_B_ENABLE_PIN);
  motorB.setPinsInverted(false, false, true);// this one turns the opposite direction to A, hence inverted.


  motorA.setMaxSpeed(maxMotorSpeed);
  motorA.setAcceleration(motorAcceleration);  
  motorA.setCurrentPosition(RESTING_LENGHT*stepsPerMM);
  
  motorB.setMaxSpeed(maxMotorSpeed);
  motorB.setAcceleration(motorAcceleration);
  motorB.setCurrentPosition(RESTING_LENGHT*stepsPerMM);
}
