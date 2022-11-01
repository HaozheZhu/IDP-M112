void init_line_sensors() {
  pinMode(line_sensor_1, INPUT);
  pinMode(line_sensor_2, INPUT);
  pinMode(line_sensor_3, INPUT);
  pinMode(line_sensor_4, INPUT); 
}

void init_motors() {
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  M1->run(RELEASE);
  M2->run(RELEASE);
}

void init_hall(){
  pinMode(hall_sensor, INPUT); 
}

void init_servo() {
  servo_grab.attach(9); //servo 2
  servo_lift.attach(10); //servo 1
  servo_lift.write(155); 
  servo_grab.write(58); 
}

void init_button() {
  pinMode(start_button, INPUT); 
  while(analogRead(start_button) > 500); 
}

void init_led() {
  pinMode(red_led, OUTPUT); 
  digitalWrite(red_led, LOW); 
  pinMode(green_led, OUTPUT); 
  digitalWrite(green_led, LOW); 
}