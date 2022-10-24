void setup() {
  Serial.begin(9600);
  init_line_sensors(); 
  init_motors(); 
  init_hall(); 

  //robot starting routine
  //while(1){
    motor(200, 0, 200); 
    delay(2000);
  //}
  
}
