void setup() {
  Serial.begin(9600);

  init_line_sensors(); 
  init_motors(); 
  init_hall(); 
  init_servo();
  init_led(); 
  
  Serial.println("READY"); 

  init_button(); 
  digitalWrite(amber_led, HIGH); 
}
