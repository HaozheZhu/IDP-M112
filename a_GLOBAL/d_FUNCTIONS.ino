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

void motor_test_run() {
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(2000);
  M1->run(BACKWARD);
  M2->run(BACKWARD); 
  delay(2000);
  M1->run(RELEASE);
  M2->run(RELEASE); 
  delay(2000);
}

void motor(int target_speed, int angle_velocity, int timestep){
  // speed, foward is positive; angular velocity: anti-clockwise is positive. 
  double m1, m2;
  m1 = (target_speed+angle_velocity);
  m2 = (target_speed-angle_velocity);

  M1->setSpeed(m1);
  M2->setSpeed(m2);
  
  if (m1<0 and m2<0){
    M1->run(BACKWARD);
    M2->run(BACKWARD);
  }
  else if (m1<0 and m2 >=0){
    M1->run(BACKWARD);
    M2->run(FORWARD);
  }
   else if (m1>=0 and m2 <0){
    M1->run(FORWARD);
    M2->run(BACKWARD);
  }
  else
  {
      M1->run(FORWARD);
      M2->run(FORWARD); 
  }

  delay(timestep);
  M1->run(RELEASE);
  M2->run(RELEASE);
}

void follow_line(int speed) {
  int line_sensor_left_value = digitalRead(line_sensor_left); 
  int line_sensor_right_value = digitalRead(line_sensor_right); 
  int line_sensor_front_value = digitalRead(line_sensor_front); 
  int line_sensor_back_value = digitalRead(line_sensor_back); 
  if(line_sensor_left_value==0 && line_sensor_right_value==0){
    motor(100, 0, 50); 
  }
  else if(line_sensor_left_value==1 && line_sensor_right_value==0){
    motor(100, 50, 50); 
  }
  else if(line_sensor_left_value==0 && line_sensor_right_value==1){
    motor(100, -50, 50);
  }
  else{
    Serial.println("both on! "); 
  }
}
