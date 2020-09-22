#include<AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

int leftSen = 35, leftMidSen = 37, midSen = 39 , rightMidSen = 41 , rightSen = 43;
int maxSpeed = 200, slowSpeed = 100, fastSpeed = 150, backSpeed = 80;
String turnLeft = "Left", turnRight = "Right";

void setup() {
  motor1.setSpeed(maxSpeed);
  motor2.setSpeed(maxSpeed);
  motor3.setSpeed(maxSpeed);
  motor4.setSpeed(maxSpeed);

}

void SlowTurn(String dir)
{
  if(dir == turnLeft)
  {
      motor1.setSpeed(fastSpeed);
      motor4.setSpeed(fastSpeed);
      motor2.setSpeed(maxSpeed);
      motor3.setSpeed(maxSpeed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
  }
  if(dir == turnRight)
  {
      motor2.setSpeed(fastSpeed);
      motor3.setSpeed(fastSpeed);
      motor1.setSpeed(maxSpeed);
      motor4.setSpeed(maxSpeed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
  }
}

void FastTurn (String dir)
{
  if(dir == turnLeft)
  {
      motor1.setSpeed(slowSpeed);
      motor4.setSpeed(slowSpeed);
      motor2.setSpeed(maxSpeed);
      motor3.setSpeed(maxSpeed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
  }
  if(dir == turnRight)
  {
      motor2.setSpeed(slowSpeed);
      motor3.setSpeed(slowSpeed);
      motor1.setSpeed(maxSpeed);
      motor4.setSpeed(maxSpeed);
      motor1.run(FORWARD);
      motor2.run(FORWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
  }
}
/*
void SlowTurnLeft()
{
  motor1.setSpeed(fastSpeed);
  motor4.setSpeed(fastSpeed);
  motor2.setSpeed(maxSpeed);
  motor3.setSpeed(maxSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void FastTurnLeft()
{
  motor1.setSpeed(slowSpeed);
  motor4.setSpeed(slowSpeed);
  motor2.setSpeed(maxSpeed);
  motor3.setSpeed(maxSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void SlowTurnRight()
{
  motor2.setSpeed(fastSpeed);
  motor3.setSpeed(fastSpeed);
  motor1.setSpeed(maxSpeed);
  motor4.setSpeed(maxSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void FastTurnRight()
{
  motor2.setSpeed(slowSpeed);
  motor3.setSpeed(slowSpeed);
  motor1.setSpeed(maxSpeed);
  motor4.setSpeed(maxSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
*/
void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void GoBack()
{
  motor1.setSpeed(backSpeed);
  motor2.setSpeed(backSpeed);
  motor3.setSpeed(backSpeed);
  motor4.setSpeed(backSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
}
void GoStraight()
{
  motor1.setSpeed(maxSpeed);
  motor4.setSpeed(maxSpeed);
  motor2.setSpeed(maxSpeed);
  motor3.setSpeed(maxSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void loop() {
}
