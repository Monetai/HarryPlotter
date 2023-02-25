
Point ToCartesian(float r1, float r2)
{
  float x = (pow(r2,2)-pow(r1,2))/(4*MOTOR_DISTANCE);
  float y = (1/(4*MOTOR_DISTANCE)) * sqrt((16*(MOTOR_DISTANCE*MOTOR_DISTANCE)*(r2*r2)) - pow((r2*r2)-(r1*r1)+4*(MOTOR_DISTANCE*MOTOR_DISTANCE),2));
  
  return Point(x,y);
}

Point ToBipolar(float x, float y)
{
  float r1 = sqrt(pow((x + MOTOR_DISTANCE), 2) + pow(y,2));
  float r2 = sqrt(pow((x - MOTOR_DISTANCE), 2) + pow(y,2));
  
  return Point(r1,r2);
}
