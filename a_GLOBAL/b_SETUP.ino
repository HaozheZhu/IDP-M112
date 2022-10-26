void setup() {
  Serial.begin(9600);
  init_line_sensors(); 
  init_motors(); 
  init_hall(); 
  servo_grab.attach(9); //servo 2
  servo_lift.attach(10); //servo 1
  servo_lift.write(150); 
  servo_grab.write(58);    
  pinMode(start_button, INPUT); 
  while(analogRead(start_button) > 500); 

}
