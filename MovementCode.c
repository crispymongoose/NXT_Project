void accelerate(int speed)
{
  for(int i = 0; i >= -speed; i--)
  {
    motor[motorA] = i;
    wait1Msec(10);
  }
}
void deccelerate(int speed)
{
  for(int i = -speed; i <= 0; i++)
  {
    motor[motorA] = i;
    wait1Msec(10);
  }
}
void turn(int direction, int clicks, int tim)
{
  nMotorEncoder[motorB] = 0;
  while (abs(nMotorEncoder[motorB]) < clicks)
    motor[motorB] = direction*20;
  motor[motorB] = 0;
  wait1Msec(tim);
  while (abs(nMotorEncoder[motorB]) > 0)
    motor[motorB] = -1*direction*20;
}

task main()
{
  accelerate(50);
  wait10Msec(100);
  turn (-1, 150, 1000);
  deccelerate(50);
}
