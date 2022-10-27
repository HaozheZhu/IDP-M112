void setup() {
  Serial.begin(9600);
  init_line_sensors(); 
  init_motors(); 
  init_hall(); 
  init_servo();
  init_button(); 
  pinMode(A3, OUTPUT); 
  digitalWrite(A3, LOW); 
}
