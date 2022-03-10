//Charles Birdsall H00219071 24.2.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This is version one of task three which measures the frequency of an input//
//The method chosen for this is counting the number of pulses over a 0.04 second period//
//and then scaling this up to a second. An alternate means was considered by which the//
//length of a single pulse would be counted and scaled up based on its duration//

#include <time.h>;
//establish frequency input pin as a variable//
 const int freq_in = 34;
 int freq_flag = 0; //the flag to indicate if the signal is low then went high
 int frequency = 0; //the value of the frequency in Hz
 int freq_count = 0; //The number of pulses over the time period
  int raw_value;
  int raw_value_old;
unsigned long start_timeF;
unsigned long currentTime;
void setup() {
  pinMode (freq_in, INPUT); //set the frequency read pin as an input 
  Serial.begin(9200);  //open the serial port with a refresh rate of 9200 baud
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

void loop() {
  freq_measure();  //call frequency measuring function
Serial.println(raw_value);  
Serial.print("Count");
Serial.println(freq_count);  //print the inital count
Serial.print("frequency = ");
Serial.print(frequency);
Serial.println("Hz"); //print the processed frequency
}
