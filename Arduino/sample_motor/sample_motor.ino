#include<AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
int slowSpeed = 80, fastSpeed = 255, backSpeed = 50, delayTime = 1500;

void setup(){
  motor1.setSpeed(fastSpeed);
  motor2.setSpeed(fastSpeed);
  motor3.setSpeed(fastSpeed);
  motor4.setSpeed(fastSpeed);
}

void TurnLeft()
{
  motor1.setSpeed(slowSpeed);
  motor4.setSpeed(slowSpeed);
  motor2.setSpeed(fastSpeed);
  motor3.setSpeed(fastSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

void TurnRight()
{
  motor2.setSpeed(slowSpeed);
  motor3.setSpeed(slowSpeed);
  motor1.setSpeed(fastSpeed);
  motor4.setSpeed(fastSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}

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

void loop(){
  TurnLeft();
  delay(delayTime);
  Stop();
  delay(delayTime);
  TurnRight();
  delay(delayTime);
  Stop();
  delay(delayTime);
  GoBack();
  delay(delayTime);
}
