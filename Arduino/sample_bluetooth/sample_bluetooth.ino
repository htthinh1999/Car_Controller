int led = 12;
char a;

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    a = Serial.read();
    if(a=='0'){
      digitalWrite(led, LOW);
    }else{
      digitalWrite(led, HIGH);
    }
  }
}
