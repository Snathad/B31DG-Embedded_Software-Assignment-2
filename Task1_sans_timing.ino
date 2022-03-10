//Charles Birdsall H00219071 24.2.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This piece of code controls the first task: the blinking of an LED//

//The time library used
#include <time.h>

//Establish pins as variables
const int green_led = 21;

//Establish variables. a,b,c & d are used to define the lengths of LED pulses, as taken from assignment1. //
const int a=0.2;
const int b=0.9;
int c=14;
const int d=2;
const int TASK1=0.05;
const int L = 0.05;
int T;

void setup() {
  //establish LED pin as an output
  pinMode(green_led, OUTPUT);
T=(c*a)+(b*c)+L*(1+2+3+4+5+6+7+8+9+10+11+12+13);
}
//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(green_led,HIGH); // turn red led on
      delay2(L);
digitalWrite(green_led,LOW);      
}
