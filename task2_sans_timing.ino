const int push_switch1 = 23;
void setup() {
  pinMode(push_switch1, INPUT);
  Serial.begin(9600);

}

int switchread(){
  int ps1s = digitalRead(push_switch1);
  if (ps1s==HIGH){
    Serial.println("Switch is pressed");
  }
  else if (ps1s==LOW){
    Serial.println("Switch is not pressed");
  }
}
void loop() {
  switchread();

}
