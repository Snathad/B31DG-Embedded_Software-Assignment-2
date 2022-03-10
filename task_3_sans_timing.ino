//Charles Birdsall H00219071 24.2.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This is version one of task three which measures the frequency of an input//
//The method chosen for this is counting the number of pulses over a 0.04 second period//
//and then scaling this up to a second. An alternate means was considered by which the//
//length of a single pulse would be counted and scaled up based on its duration//

#include <time.h>;
//establish frequency input pin as a variable//
 const int freq_in = 22;
 int freq_flag = 0; //the flag to indicate if the signal is low then went high
 int frequency = 0; //the value of the frequency in Hz
 int freq_count = 0; //The number of pulses over the time period

void setup() {
  pinMode (freq_in, INPUT); //set the frequency read pin as an input 
  Serial.begin(9600);  //open the serial port with a refresh rate of 9600 baud
}
//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}

//This subfunction measures the frequency from the input
void freq_measure (){
  //If the frequency is low trigger the frequency flag
  if (freq_in==LOW){
    freq_flag=1;
  }
  else if (freq_in==HIGH){  //else if the pulse is high wait to check its not low then reset flag
    delay (0.5);
    freq_flag=0;}

  clock_t start_timeF= clock(); //define the start time of the clock
    while (clock() < start_timeF + 40);{  //effectively delays for 0.04seconds, the optimum time for detecting frequency that keeps errors within +/- 2.5%
      if (freq_flag==1 && freq_in==HIGH){ //If frequency input is high and was previously low (ie flag is on) add one to the value of the frequency counter.
        freq_count=freq_count+1;
      if (clock()>= start_timeF +39.5){ //calculate the frequency by scaling 0.04s up to 1s
        frequency =freq_count*25;  
      }
        }
    }
}
void loop() {
  freq_measure();  //call frequency measuring function
Serial.print("Count");
Serial.println(freq_count);  //print the inital count
Serial.print("frequency = ");
Serial.print(frequency);
Serial.println("Hz"); //print the processed frequency
}
