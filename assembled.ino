//Charles Birdsall H00219071 10.3.22//
//B32DG Embedded Software Assignment2//
//assembled form//
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
const int push_switch1 = 23; //establish input for push switch
//establish frequency input pin as a variable//
 const int freq_in = 34;
 int freq_flag = 0; //the flag to indicate if the signal is low then went high
 int frequency = 0; //the value of the frequency in Hz
 int freq_count = 0; //The number of pulses over the time period
  int raw_value;
  int raw_value_old;
unsigned long start_timeF;
unsigned long currentTime;
//Establish analogue read as a variable//
const int analogue_in = 35;
const int red_led = 15;
float analogue_hist0;
float analogue_hist1;
float analogue_hist2;
float analogue_hist3;
float analogue_average ;
const float analogue_max = 3.3;
int error_code = 0;

void setup() {
  // put your setup code here, to run once:
//establish LED pin as an output
  pinMode(green_led, OUTPUT);
T=(c*a)+(b*c)+L*(1+2+3+4+5+6+7+8+9+10+11+12+13);
  pinMode(push_switch1, INPUT); //set pin as INPUT
  Serial.begin(9600); //start serial plotter
   pinMode (freq_in, INPUT); //set the frequency read pin as an input 
   pinMode(red_led, OUTPUT);
  pinMode(analogue_in, INPUT);
  analogue_hist0=analogRead(analogue_in);
  analogue_hist1=analogue_hist0;
  analogue_hist2=analogue_hist1;
  analogue_hist3=analogue_hist2;
}

//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
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

//This subfunction measures the frequency from the input
void freq_measure (){
  raw_value=digitalRead(freq_in);
  raw_value_old= raw_value;
  freq_count=0;    
 

  start_timeF= micros(); //define the start time of the clock
  currentTime=micros();
    while ((currentTime-start_timeF) < 40000){  //effectively delays for 0.04seconds, the optimum time for detecting frequency that keeps errors within +/- 2.5%
       
      raw_value=digitalRead(freq_in);
      if (raw_value_old != raw_value){ //If frequency input is high and was previously low (ie flag is on) add one to the value of the frequency counter.
        freq_count++;
        raw_value_old=raw_value;}
     
     
         
     
     
      //Serial.println(raw_value);
      //Serial.println(raw_value_old);
      currentTime=micros();
        
    } 
    if (micros()>= start_timeF +40000){ //calculate the frequency by scaling 0.04s up to 1s
        frequency =freq_count*25/2;  
        Serial.println("yeah its working");
      }
}

void analogue_process(){
  analogue_hist3=analogue_hist2;
  analogue_hist2=analogue_hist1;
  analogue_hist1=analogue_hist0;
  analogue_hist0=analogRead(analogue_in)*(3.3/4095);
}

void analogue_filter(){
  analogue_average= (analogue_hist0+analogue_hist1+analogue_hist2+analogue_hist3)/4;
  Serial.print("filtered analog value");
  Serial.println(analogue_average);
  Serial.print(analogue_hist0);
}

void analogue_error(){
  if (analogue_hist0 > (0.5*analogue_max)){
    error_code = 1;
    }
    else if (analogue_hist0 < (0.5*analogue_max)){
    error_code = 0;  
    }
}

void error_out(){
  if (error_code==1){
    digitalWrite(red_led,HIGH);
  }
  else if (error_code!=1){
    digitalWrite(red_led,LOW);
  }
}

void task6 (){
 int i;
  for (i=1; i<1000; +i){
    __asm__ __volatile__ ("nop");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(green_led,HIGH); // turn red led on
      delay2(L);
digitalWrite(green_led,LOW);  
switchread();
freq_measure();  //call frequency measuring function
Serial.println(raw_value);  
Serial.print("Count");
Serial.println(freq_count);  //print the inital count
Serial.print("frequency = ");
Serial.print(frequency);
Serial.println("Hz"); //print the processed frequency
  // put your main code here, to run repeatedly:
analogue_process();
analogue_filter();
analogue_error();
error_out();
task6();
}
