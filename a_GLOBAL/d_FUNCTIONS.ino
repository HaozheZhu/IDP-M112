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
  Serial.println("Motor Shield found.");
  M1->setSpeed(250);
  M2->setSpeed(250);
}

void init_hall(){
  pinMode(hall_pin, INPUT); 
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

void follow_line(int speed, int angular, int timestep) {
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 

  if(line_sensor_1_value==1 && line_sensor_2_value==0){
    motor(speed, angular, timestep); 
  }
  else if(line_sensor_1_value==0 && line_sensor_2_value==1){
    motor(speed, -angular, timestep);
  }
  else{
    motor(speed, angular, timestep); 
  }
}

void nav_once() {
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  int line_sensor_3_value = digitalRead(line_sensor_3); 
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  if(false) {
    Serial.print("Line sensor 1 = "); 
    Serial.println(line_sensor_1_value); 
    Serial.print("Line sensor 2 = "); 
    Serial.println(line_sensor_2_value); 
    Serial.print("Line sensor 3 = "); 
    Serial.println(line_sensor_3_value); 
    Serial.print("Line sensor 4 = "); 
    Serial.println(line_sensor_4_value); 
    Serial.println("------------------------");
    delay(0); 
  }
  if(line_sensor_1_value == 0 && line_sensor_4_value == 0) {
    //follow line
    Serial.println("Following line"); 
    follow_line(100,60,30); 
  }
  else {
    //at junctions
    if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
      Serial.println("At cross"); 
      delay(3000); 
      follow_line(250,0,500); 
    }
    if(line_sensor_1_value == 1 && line_sensor_4_value == 0) {
      follow_line(100,0,500);
      delay(1000);
      if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
        Serial.println("At cross"); 
        delay(3000); 
        follow_line(250,0,500); 
      }
      else if(line_sensor_1_value == 1 && line_sensor_4_value == 0) {
        Serial.println("At left junction"); 
        delay(10000); 
        follow_line(250,0,500); 
      }
    }
    if(line_sensor_1_value == 0 && line_sensor_4_value == 1) {
      follow_line(100,0,500);
      delay(1000); 
      if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
        Serial.println("At cross"); 
        delay(3000); 
        follow_line(250,0,500); 
      }
      else if(line_sensor_1_value == 0 && line_sensor_4_value == 1) {
        Serial.println("At right junction"); 
        delay(3000); 
        follow_line(250,0,500); 
      }
    }
  }
}  
  