#include<AFMotor.h>

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);

const int echo = 31, trig = 33;
int normalSpeed = 80, backSpeed = 60, slowTurnSpeed = 50, fastTurnSpeed = 130 ; // stable slow 100 fast 130
int leftSen = A8, rightSen = A9;
String turnLeft = "Left", turnRight = "Right";
bool turningLeft = 1;
int switchBtn = 50;
int forwardLed = 22, stopLed = 24, warningLeftLed = 26, warningRightLed = 28;

void setup() { 
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(forwardLed, OUTPUT);
  pinMode(stopLed, OUTPUT);
  pinMode(warningLeftLed, OUTPUT);
  pinMode(warningRightLed, OUTPUT);

  digitalWrite(forwardLed, LOW);
  digitalWrite(stopLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
  
  Serial.begin(9600);
  Serial3.begin(9600);

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
      digitalWrite(warningLeftLed,HIGH);     
      digitalWrite(forwardLed, LOW);
      digitalWrite(stopLed, LOW);
      digitalWrite(warningRightLed, LOW);
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
      digitalWrite(warningRightLed,HIGH);
      digitalWrite(forwardLed, LOW);
      digitalWrite(stopLed, LOW);
      digitalWrite(warningLeftLed, LOW);
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
      digitalWrite(warningLeftLed,HIGH);     
      digitalWrite(forwardLed, LOW);
      digitalWrite(stopLed, LOW);
      digitalWrite(warningRightLed, LOW);
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
      digitalWrite(warningRightLed,HIGH); 
      digitalWrite(forwardLed, LOW);
      digitalWrite(stopLed, LOW);
      digitalWrite(warningLeftLed, LOW);
  }
}

void Stop()
{
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  digitalWrite(stopLed,HIGH); 
  digitalWrite(forwardLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void Forward()
{
  motor1.setSpeed(normalSpeed);
  motor4.setSpeed(normalSpeed);
  motor2.setSpeed(normalSpeed);
  motor3.setSpeed(normalSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  digitalWrite(forwardLed,HIGH);  
  digitalWrite(stopLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}


void Backward()
{
  motor1.setSpeed(backSpeed);
  motor2.setSpeed(backSpeed);
  motor3.setSpeed(backSpeed);
  motor4.setSpeed(backSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  digitalWrite(stopLed,HIGH);
  digitalWrite(forwardLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void LeftBackward()
{
  motor1.setSpeed(backSpeed);
  motor4.setSpeed(normalSpeed);
  motor2.setSpeed(backSpeed);
  motor3.setSpeed(normalSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  digitalWrite(stopLed,HIGH);
  digitalWrite(forwardLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void RightBackward()
{
  motor1.setSpeed(normalSpeed);
  motor4.setSpeed(backSpeed);
  motor2.setSpeed(normalSpeed);
  motor3.setSpeed(backSpeed);
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
  motor3.run(BACKWARD);
  motor4.run(BACKWARD);
  digitalWrite(stopLed,HIGH);
  digitalWrite(forwardLed, LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void LeftForward()
{
  motor1.setSpeed(slowTurnSpeed);
  motor2.setSpeed(slowTurnSpeed);
  motor3.setSpeed(normalSpeed);
  motor4.setSpeed(normalSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  digitalWrite(forwardLed,HIGH);
  digitalWrite(stopLed,LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void RightForward()
{
  motor1.setSpeed(normalSpeed);
  motor2.setSpeed(normalSpeed);
  motor3.setSpeed(slowTurnSpeed);
  motor4.setSpeed(slowTurnSpeed);
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);
  digitalWrite(forwardLed,HIGH);
  digitalWrite(stopLed,LOW);
  digitalWrite(warningLeftLed, LOW);
  digitalWrite(warningRightLed, LOW);
}

void AutoFollowLine(){
  int leftSenVal = digitalRead(leftSen),
  rightSenVal = digitalRead(rightSen);

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
      if(leftSenVal && rightSenVal){
        if(turningLeft){
          FastTurn(turnLeft);
        }else{
          FastTurn(turnRight);
        }
      }
      if(!leftSenVal && rightSenVal){
        turningLeft = 1;
        FastTurn(turnLeft);
      }
      if(leftSenVal && !rightSenVal){
        turningLeft = 0;
        FastTurn(turnRight);
      }
      if(leftSenVal && rightSenVal){
        Stop();
      }
   }
}

void ManualControl(){
  Serial.println(Serial3.read());
  switch(Serial3.read()){
    case '1':
      Forward();
      delay(100);
      break;
    case '2':
      Backward();
      delay(100);
      break;
    case '3':
      LeftForward();
      delay(100);
      break;
    case '4':
      RightForward();
      delay(100);
      break;
    case '5':
      LeftBackward();
      delay(100);
      break;
    case '6':
      RightBackward();
      delay(100);
      break;
    default:
      Stop();
      break;
  }
}

void loop() {
  bool autoDrive = digitalRead(switchBtn);
  Serial.println(autoDrive);
  
  if(autoDrive){
    AutoFollowLine();
  }else{
    ManualControl();
  }
}
