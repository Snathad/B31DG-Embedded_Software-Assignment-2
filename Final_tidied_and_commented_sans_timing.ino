//Charles Birdsall H00219071 10.3.22//
//B32DG Embedded Software Assignment2//
//This code gathers together nine tasks with the intention of running as a cyclic executive//

//The time library used
#include <time.h>

//Establish pins as variables
const int green_led = 21;

//Task 1 variables
//Establish variables. a,b,c & d are used to define the lengths of LED pulses, as taken from assignment1. //
const int a=0.2;
const int b=0.9;
int c=14;
const int d=2;
const int L = 0.05; //delay to keep the LED on for task 1
int T;  //The total time variable for calculating task1 pulses

//Task2 variables
const int push_switch1 = 23; //establish input for push switch

//Task 3 variables
//establish frequency input pin as a variable//
const int freq_in = 34;
int frequency = 0; //the value of the frequency in Hz
int freq_count = 0; //The number of pulses over the time period
int raw_value; //The unprocessed input value
int raw_value_old; //The previous unprocessed input value
unsigned long start_timeF; // used to determine the time at which the frequency check was started
unsigned long currentTime; //used to determine the current time

//Tasks 4 variables
const int analogue_in = 35;//Establish analogue read as a variable

//Task 5 variables
//The past four analogue values are stored in analogue_hist0-3
float analogue_hist0;
float analogue_hist1;
float analogue_hist2;
float analogue_hist3;
float analogue_average ; //The average analogue value

//Task 7 variables
const float analogue_max = 3.3; //sets a limit on the maximum analogue value for error processing
int error_code = 0; //a flag for whether the error condition is met or not

//Task 8 variables
const int red_led = 15; //establish the red LED to be used as an error output.
///////////////////////////////////////////////////////////////

void setup() {
  //Establish Pins
  pinMode(green_led, OUTPUT);//establish LED pin as an output
  pinMode(red_led, OUTPUT); //establish LED pin as an output
  pinMode(push_switch1, INPUT); //set button pin as INPUT
  pinMode (freq_in, INPUT); //set the frequency read pin as an input 
  pinMode(analogue_in, INPUT); //set the analogue read from the potentiometer as an input
  
  T=(c*a)+(b*c)+L*(1+2+3+4+5+6+7+8+9+10+11+12+13); //The delay value from assignment one for task one

  //Define the historical analogue read values to shift them
  //Please note a bitshifter and array are seen in earlier iterations
  analogue_hist0=analogRead(analogue_in);
  analogue_hist1=analogue_hist0;
  analogue_hist2=analogue_hist1;
  analogue_hist3=analogue_hist2;
  
  Serial.begin(9600); //start serial plotter
}


///////////////////////////////////////////////////////////////////////////////
//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}


///////////////////////////////////////////////////////////////////////////////
int switchread(){
  int ps1s = digitalRead(push_switch1); //set variable that is read from switch value
  if (ps1s==HIGH){
    Serial.println("Switch is pressed");  //if the input is high print that the button is pressed
  }
  else if (ps1s==LOW){
    Serial.println("Switch is not pressed"); //if the input is low print that the button is not pressed
  }
}


///////////////////////////////////////////////////////////////////////////////
//This subfunction measures the frequency from the input
void freq_measure (){
  raw_value=digitalRead(freq_in);  //set the raw value to be equal to the digital read from the input
  raw_value_old= raw_value;  //set the old value equal to the current
  freq_count=0; //reset the frequency count to zero   
 
  start_timeF= micros(); //define the start time of the clock
  currentTime=micros(); // define current time

  //It was found using one time alone had a processing lag which had to be factored in
  while ((currentTime-start_timeF) < 40000){  //effectively delays for 0.04seconds, the optimum time for detecting frequency that keeps errors within +/- 2.5%
    raw_value=digitalRead(freq_in); //remeasure the actual input
       
    if (raw_value_old != raw_value){ //If frequency input is high and was previously low (ie flag is on) add one to the value of the frequency counter.
      freq_count++; //increase frequency
      raw_value_old=raw_value;//update the old frequency value
      }
    } 
  if (micros()>= start_timeF +40000){ //calculate the frequency by scaling 0.04s up to 1s
      frequency =freq_count*25/2;  
      //Serial.println("Frequency condition is met"); //a flag used to indicate whether this stage is operating
      }
}


///////////////////////////////////////////////////////////////////////////////
void analogue_process(){ //Read in the analogue values and shift the previous values along one
  analogue_hist3=analogue_hist2;
  analogue_hist2=analogue_hist1;
  analogue_hist1=analogue_hist0;
  analogue_hist0=analogRead(analogue_in)*(3.3/4095); //multiplies input by scaling factor for analogue inputs
}


///////////////////////////////////////////////////////////////////////////////
void analogue_filter(){
  analogue_average= (analogue_hist0+analogue_hist1+analogue_hist2+analogue_hist3)/4; //take average of analogue values
  //optional prints to show status
  //Serial.print("filtered analog value");
  //Serial.println(analogue_average);
  //Serial.print(analogue_hist0);
}


///////////////////////////////////////////////////////////////////////////////
void analogue_error(){
  if (analogue_hist0 > (0.5*analogue_max)){ //if condition is met return positive error code
    error_code = 1;
    }
  else if (analogue_hist0 < (0.5*analogue_max)){ //if condition is not met, return negative error code
    error_code = 0;  
    }
}


///////////////////////////////////////////////////////////////////////////////
void error_out(){
  if (error_code==1){ //if error code is positive, turn red LED on
    digitalWrite(red_led,HIGH);
  }
  else if (error_code!=1){ //if error code is no longer positive, turn red LED off
    digitalWrite(red_led,LOW);
  }
}


///////////////////////////////////////////////////////////////////////////////
void task6 (){ //perfoem 1000 times
 int i;
  for (i=1; i<1000; +i){
    __asm__ __volatile__ ("nop");
  }
}


///////////////////////////////////////////////////////////////////////////////
void loop() {
  //the task1 watchdog
  digitalWrite(green_led,HIGH); // turn green led on
  delay2(L);
  digitalWrite(green_led,LOW);
    
  switchread(); //call switchread function
  freq_measure();  //call frequency measuring function
  Serial.println(raw_value);  
  Serial.print("Count");
  Serial.println(freq_count);  //print the inital count
  Serial.print("frequency = ");
  Serial.print(frequency);
  Serial.println("Hz"); //print the processed frequency
    
  analogue_process(); //call analogue processing function
  analogue_filter(); //call analogue averaging function
  analogue_error(); //call analogue error function
  error_out(); //call analogue error visual alarm function
  task6(); //call 1000iter task six function
  }
