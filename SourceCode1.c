void accelerate(int speed)
{
  for(int i = 0; i >= -speed; i--)
  {
    motor[motorA] = i;
    wait1Msec(10);
  }
}

task main()
{
  accelerate(50);
  wait10Msec(100);
}
