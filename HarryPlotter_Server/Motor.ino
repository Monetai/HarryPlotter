void MotorSetup()
{
  pinMode(MOTOR_A_ENABLE_PIN, OUTPUT);
  digitalWrite(MOTOR_A_ENABLE_PIN, LOW);
  pinMode(MOTOR_B_ENABLE_PIN, OUTPUT);
  digitalWrite(MOTOR_B_ENABLE_PIN, LOW);
  motorA.setEnablePin(MOTOR_A_ENABLE_PIN);
  motorA.setPinsInverted(false, false, true);
  motorB.setEnablePin(MOTOR_B_ENABLE_PIN);
  motorB.setPinsInverted(true, false, true); // this one turns the opposite direction to A, hence inverted.

  motorA.setMaxSpeed(maxMotorSpeed);
  motorA.setAcceleration(motorAcceleration);  
  motorB.setMaxSpeed(maxMotorSpeed);
  motorB.setAcceleration(motorAcceleration);
}
