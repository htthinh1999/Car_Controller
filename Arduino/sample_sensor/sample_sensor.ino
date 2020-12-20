int ir = 4;  // hong ngoai

void setup() {
  pinMode(ir, INPUT);
  Serial.begin(9600);
}

void loop() {
  int a = digitalRead(ir);
  if(a==0){
    Serial.println("Trang");
  }else{
    Serial.println("Den");
  }
}
