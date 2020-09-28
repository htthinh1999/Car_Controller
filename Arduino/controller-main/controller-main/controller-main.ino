#include<AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);


const int echo = 47, trig = 45;
int leftSen = A15, leftMidSen = A14, midSen = A13 , rightMidSen = A12 , rightSen = A11;
int  normalSpeed = 80,backSpeed = 60,slowTurnSpeed= 50,fastTurnSpeed = 130 ; // stayble slow 100 fast 130
String turnLeft = "Left", turnRight = "Right";
bool turningLeft = 1;

void setup() {
  pinMode(trig,OUTPUT);
  pinMode(echo,INPUT);
  pinMode(12,OUTPUT);
  pinMode(13,OUTPUT);
  Serial.begin(9600);

}

void SlowTurn(String dir)
{
  if(dir == turnLeft)
  {
      turningLeft = 1;
      motor1.setSpeed(slowTurnSpeed);
      motor2.setSpeed(slowTurnSpeed);
      motor3.setSpeed(fastTurnSpeed);
      motor4.setSpeed(fastTurnSpeed);
      motor1.run(BACKWARD);
      motor3.run(FORWARD);
      motor2.run(FORWARD);
      motor4.run(BACKWARD);
  }
  if(dir == turnRight)
  {
      turningLeft = 0;
      motor3.setSpeed(slowTurnSpeed);
      motor4.setSpeed(slowTurnSpeed);
      motor1.setSpeed(fastTurnSpeed);
      motor2.setSpeed(fastTurnSpeed);
      motor1.run(FORWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      motor2.run(FORWARD);
  }
}

void FastTurn (String dir)
{
  if(dir == turnLeft)
  {
      turningLeft = 1;
      motor1.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor2.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor3.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor4.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor1.run(BACKWARD);
      motor3.run(FORWARD);
      motor4.run(FORWARD);
      motor2.run(BACKWARD);
  }
  if(dir == turnRight)
  {
      turningLeft = 0;
      motor2.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor3.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor1.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor4.setSpeed((slowTurnSpeed + fastTurnSpeed)/2);
      motor1.run(FORWARD);
      motor3.run(BACKWARD);
      motor4.run(BACKWARD);
      motor2.run(FORWARD);
  }
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
}

void BackWard()
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
void ForWard()
{
  motor1.setSpeed(normalSpeed);
  motor4.setSpeed(normalSpeed);
  motor2.setSpeed(normalSpeed);
  motor3.setSpeed(normalSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
}
void loop() {
 int leftSenValue = digitalRead(leftSen),
  leftMidSenValue = digitalRead(leftMidSen), 
  midSenValue = digitalRead(midSen) , 
  rightMidSenValue = digitalRead(rightMidSen) , 
  rightSenValue = digitalRead(rightSen);

   unsigned long duration;
    int distance;
    digitalWrite(trig,0);   
   delayMicroseconds(2);
    digitalWrite(trig,1);   
  delayMicroseconds(5);  
  digitalWrite(trig,0);   
  duration = pulseIn(echo,HIGH); 
  distance = int(duration/2/29.412);
   Serial.print(distance);
   Serial.println("cm");

   if(distance <=20)
   {
      Stop(); 
   }
  else
  {
      Serial.print(leftSenValue);
      Serial.print(leftMidSenValue);
      Serial.print(midSenValue);
      Serial.print(rightMidSenValue);
      Serial.print(rightSenValue);
      Serial.println();
      
      // Bat dau nhan dang
      if((midSenValue == 0) && (leftSenValue == 1) && (leftMidSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        ForWard();
      }
      if((leftMidSenValue == 0)&& (midSenValue == 1) && (leftSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        SlowTurn(turnLeft);
      }
    
      if((leftMidSenValue == 0)&& (midSenValue == 0) && (leftSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        SlowTurn(turnLeft);
      }
      
      if((leftSenValue == 0)&& (leftMidSenValue == 1) && (midSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1) )
      {
        FastTurn(turnLeft);
      }
    
      if((leftSenValue == 0)&& (leftMidSenValue == 0) && (midSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        FastTurn(turnLeft);
      }
      
       if((rightMidSenValue == 0)&& (midSenValue == 1) && (leftSenValue == 1) && (leftMidSenValue == 1) && (rightSenValue == 1))
      {
        SlowTurn(turnRight);
      }
    
        if((rightMidSenValue == 0)&& (midSenValue == 0) && (leftSenValue == 1) && (leftMidSenValue == 1) && (rightSenValue == 1))
      {
        SlowTurn(turnRight);
      }
      
       if((rightSenValue == 0)&& (rightMidSenValue == 1) && (midSenValue == 1) && (leftMidSenValue == 1) && (leftSenValue == 1))
      {
        FastTurn(turnRight);
      }
    
       if((rightSenValue == 0)&& (rightMidSenValue == 0) && (midSenValue == 1) && (leftMidSenValue == 1) && (leftSenValue == 1))
      {
        FastTurn(turnRight);
      }
      
      if((leftSenValue == 0)&& (leftMidSenValue == 0) && (midSenValue == 0) && (rightMidSenValue == 0) && (rightSenValue == 0))
      {
        Stop();
      }
      if((leftSenValue == 1)&& (leftMidSenValue == 1) && (midSenValue == 1) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        if(turningLeft == 1)
          SlowTurn(turnLeft);
        else
          SlowTurn(turnRight);
      }
      if((leftSenValue == 0)&& (leftMidSenValue == 0) && (midSenValue == 0) && (rightMidSenValue == 1) && (rightSenValue == 1))
      {
        FastTurn(turnLeft);
      }
      if((leftSenValue == 1)&& (leftMidSenValue == 1) && (midSenValue == 0) && (rightMidSenValue == 0) && (rightSenValue == 0))
      {
        FastTurn(turnRight);
      } 
   }
}
