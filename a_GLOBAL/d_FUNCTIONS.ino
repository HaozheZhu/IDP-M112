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
  M1->run(RELEASE);
  M2->run(RELEASE);
}

void init_hall(){
  pinMode(hall_pin, INPUT); 
}

void grab_block() {
  servo_lift.write(127); 
  delay(1000); 

  servo_grab.write(114); 
  delay(1000); 

  servo_lift.write(150); 
  delay(2000); 
}

void release_block() {
  servo_lift.write(127); 
  delay(1000); 

  servo_grab.write(58); 
  delay(2000);
}

void motor(int m1, int m2, int dt) {
  if(m1>=0 && m2>=0){
    M1->setSpeed(abs(m1)); 
    M2->setSpeed(abs(m2)); 
    M1->run(FORWARD);
    M2->run(FORWARD); 
    delay(dt);  
    M1->run(RELEASE); 
    M2->run(RELEASE); 
  }
  else if(m1<=0 && m2>=0){
    M1->setSpeed(abs(m1)); 
    M2->setSpeed(abs(m2)); 
    M1->run(BACKWARD);
    M2->run(FORWARD); 
    delay(dt);  
    M1->run(RELEASE); 
    M2->run(RELEASE); 
  }
  else if(m1>=0 && m2<=0){
    M1->setSpeed(abs(m1)); 
    M2->setSpeed(abs(m2)); 
    M1->run(FORWARD);
    M2->run(BACKWARD); 
    delay(dt);  
    M1->run(RELEASE); 
    M2->run(RELEASE); 
  }
} 


void follow_line(int forward, int turn, int dt) {
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  int line_sensor_3_value = digitalRead(line_sensor_3); 
  
  if(line_sensor_2_value==0 && line_sensor_3_value==0){
    motor(forward, forward, dt); 
  }
  else if(line_sensor_2_value==1 && line_sensor_3_value==0){
    motor(turn, forward, dt); 
  }
  else if(line_sensor_2_value==0 && line_sensor_3_value==1){
    motor(forward, turn, dt); 
  }
}

void handle_cross() {
  Serial.println("At cross"); 
}

void handle_left_junction() {
  Serial.println("At left junction"); 
}

void handle_right_junction() {
  Serial.println("At right junction"); 
}

void nav_once() {
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  int line_sensor_3_value = digitalRead(line_sensor_3); 
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  
  if(line_sensor_1_value == 0 && line_sensor_4_value == 0) {
    Serial.println("Following line straight"); 
    follow_line(250,0,100); 
  }
  else {
    //at junctions
    if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
      handle_cross(); 
    }
    if(line_sensor_1_value == 1 && line_sensor_4_value == 0) {
      motor(250, 250, 200); 
      delay(2000);
      if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
        handle_cross(); 
      }
      else if(line_sensor_1_value == 1 && line_sensor_4_value == 0) {
        handle_left_junction(); 
      }
    }
    if(line_sensor_1_value == 0 && line_sensor_4_value == 1) {
      motor(250, 250, 200); 
      delay(2000); 
      if(line_sensor_1_value == 1 && line_sensor_4_value == 1) {
        handle_cross(); 
      }
      else if(line_sensor_1_value == 0 && line_sensor_4_value == 1) {
        handle_right_junction(); 
      }
    }
  }
}  

void follow_wall(double target_dist, double dist){ 
  if(dist>2.0){
    if(dist<target_dist) {
      motor(250, 150, 20); 
      Serial.println("turn right"); 
    }
    else if(dist>target_dist) {
      motor(150, 250, 20); 
      Serial.println("turn left"); 
    }
  }
  else {
      motor(250, 250, 20); 
      Serial.println("straight"); 
    }  
}

bool dectect_tunnel(){
  if(ultrasound_side() < 20.0){
    return true;
  }
  else{return false;}
}
