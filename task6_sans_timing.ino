void setup() {
  

}
void task6 (){
 int i;
  for (i=1; i<1000; +i){
    __asm__ __volatile__ ("nop");
  }
}
void loop() {
 task6();

}
