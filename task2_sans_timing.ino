const int push_switch1 = 23;
void setup() {
  pinMode(push_switch1, INPUT);
  Serial.begin(9600);

}

int switchread(){
  int ps1s = digitalRead(push_switch1);
  if (ps1s==HIGH){
    Serial.print("Switch is pressed");
  }
  else if (ps1s==LOW){
    Serial.print("Switch is not pressed");
  }
}
void loop() {
  switchread();

}
