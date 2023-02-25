void MoveToBipolar(float lenghtA, float lenghtB)
{
  
  float currSpeedA = motorA.speed();
  float currSpeedB = motorB.speed();
  
  motorA.setSpeed(0.0);
  motorB.setSpeed(0.0);
  motorA.moveTo(lenghtA * stepsPerMM);
  motorB.moveTo(lenghtB * stepsPerMM);
  
  if (!usingAcceleration)
  {
    // The moveTo() function changes the speed in order to do a proper
    // acceleration. This counteracts it. Ha.
    
    if (motorA.speed() < 0)
      currSpeedA = -currSpeedA;
    if (motorB.speed() < 0)
      currSpeedB = -currSpeedB;

    motorA.setSpeed(currSpeedA);
    motorB.setSpeed(currSpeedB);
  }

  while (motorA.distanceToGo() != 0 && motorB.distanceToGo() != 0)
  {
    if (currentlyRunning)
    {
      if (usingAcceleration)
      {
        motorA.run();
        motorB.run();
      }
      else
      {
        motorA.runSpeedToPosition();
        motorB.runSpeedToPosition();
      }
    }
  }
}
