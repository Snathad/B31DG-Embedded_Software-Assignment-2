//Charles Birdsall H00219071 24.2.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This task reads the input of a switch and prints it to the serial plotter//

const int push_switch1 = 23; //establish input for push switch

void setup() {
  pinMode(push_switch1, INPUT); //set pin as INPUT
  Serial.begin(9600); //start serial plotter
}

int switchread(){
  int ps1s = digitalRead(push_switch1); //set variable that is read from switch value
  if (ps1s==HIGH){
    Serial.println("Switch is pressed");  //if the input is high print that the button is pressed
  }
  else if (ps1s==LOW){
    Serial.println("Switch is not pressed"); //if the input is low print that the button is not pressed
  }
}
void loop() {
  switchread();

}
