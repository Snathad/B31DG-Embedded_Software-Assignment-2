//Charles Birdsall H00219071 09.03.22//
//B32DG Embedded Software Assignment2//
//This code is broken into tasks that will be later combined in a cycle//
//This task handles the analogue input values, storing them as a rolling//
//array which can late rbe averaged//
//Additionally the code to detect errors in the analogue input is included//
//so this is tasks 4,5 and 7 and 8//

//Establish analogue read as a variable//
const int analogue_in = 35;
const int red_led = 15;
float analogue_hist[4]={0,0,0,0};
float analogue_average = 0;
const float analogue_max = 3.3;
int error_code = 0;
void setup() {
  pinMode(red_led, OUTPUT);
  pinMode(analogue_in, INPUT);
  Serial.begin(9600);
}

void analogue_process(){
  analogue_hist[3]=analogue_hist[2];
  analogue_hist[2]=analogue_hist[1];
  analogue_hist[1]=analogue_hist[0];
  analogue_hist[0]=analogRead(analogue_in);
}

void analogue_filter(){
  analogue_average= (analogue_hist[0]+analogue_hist[1]+analogue_hist[2]+analogue_hist[3])/4;
  Serial.println("filtered analog value");
  Serial.print(analogue_average);
}

void analogue_error(){
  if (analogue_hist[0] > (0.5*analogue_max)){
    error_code = 1;
    }
    else if (analogue_hist[0] < (0.5*analogue_max)){
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

void loop() {
  // put your main code here, to run repeatedly:
analogue_process();
analogue_filter();
analogue_error();
error_out();
}
