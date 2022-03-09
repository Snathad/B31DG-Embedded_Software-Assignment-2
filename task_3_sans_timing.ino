//Charles Birdsall H00219071 24.2.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This is version one of task three which measures the frequency of an input//
//The method chosen for this is counting the number of pulses over a 0.04 second period//
//and then scaling this up to a second. An alternate means was considered by which the//
//length of a single pulse would be counted and scaled up based on its duration//

//establish frequency input pin as a variable//
 const int freq_in = 33;
 int freq_flag = 0;
 int frequency = 0;
 int freq_count = 0;

void setup() {

 
  pinMode (freq_in, INPUT); 
  Serial.begin(9600);
}
//this subfunction creates a delay based on the clock in the time library. A traditional delay was found to pause the whole code and prevent the button inputs form registering//
void delay2(int nosecs){
  clock_t start_time= clock(); //define the start time of the clock
  while (clock() < start_time + nosecs);  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
}

void freq_measure (int frequency=0, const int freq_in=33, int freq_flag=0, int freq_count=0){
  if (freq_in==LOW){
    freq_flag=1;
  }
  else if (freq_in==HIGH){
    delay (0.5);
    freq_flag=0;}

  clock_t start_timeF= clock(); //define the start time of the clock
    while (clock() < start_timeF + 40);{  //adds the number of elapsed milliseconds on to the clock so timing can be calculated
      if (freq_flag==1 && freq_in==HIGH){ 
        freq_count=freq_count+1;
      if (clock()>= start_timeF +39.5){
        frequency =freq_count*25;  
      }
        }
    }
}
void loop() {
  freq_measure();  
Serial.print("Count");
Serial.print(freq_count);
Serial.print("frequency");
Serial.print(frequency)+("Hz");
}
