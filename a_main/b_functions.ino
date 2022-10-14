void init_line_sensors() {
  pinMode(line_sensor_front, INPUT);
  pinMode(line_sensor_back, INPUT);
  pinMode(line_sensor_left, INPUT);
  pinMode(line_sensor_right, INPUT); 
}

void init_motors() {
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  M1->setSpeed(250);
  M2->setSpeed(250);
}

void steer_right() {
  M1->setSpeed(200); 
  M2->setSpeed(100); 
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(50);  
  M1->run(RELEASE); 
  M2->run(RELEASE); 
} 

void steer_left() {
  M1->setSpeed(100); 
  M2->setSpeed(200); 
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(50);  
  M1->run(RELEASE); 
  M2->run(RELEASE); 
} 