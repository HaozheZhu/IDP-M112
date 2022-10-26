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
  servo_lift.write(124); 
  delay(1000); 

  servo_grab.write(114); 
  delay(1000); 

  servo_lift.write(150); 
  delay(2000); 
}

void release_block() {
  servo_lift.write(124); 
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

void handle_junction() {
  Serial.println("At junction"); 
  switch(location){
    case 1: 
      location = 2; 
      Serial.println("At position 2 now"); 
      delay(1000); 
      motor(250, 250, 500); 
      break; 
    case 2: 
      location = 3; 
      Serial.println("At position 14 now, turning right"); 
      delay(1000); 
      motor(250, 250, 500); 
      delay(1000); 
      while(digitalRead(line_sensor_3)==0){
        motor(250, -250, 100); 
      }
      break; 
    case 14: 
      location = 3; 
      Serial.println("At position 3 now, keep rotating"); 
      while(digitalRead(line_sensor_3)==0){
        motor(250, -250, 100); 
      }
      motor(250, -250, 500); 
      break; 
    case 3: 
      location = 4; 
      Serial.println("At position 4 now"); 
      motor(250, 250, 400); 
      break; 
    case 4: 
      location = 5; 
      Serial.println("At position 5 now"); 
      motor(250, 250, 2000); 
      break; 
    case 5: 
      location = 6; 
      motor(250, 250, 2000); 
      break; 
    case 6: 
      location = 7; 
      motor(250, 250, 500); 
      break; 
    case 7: 
      while(1); 
      break; 
    default: 
      Serial.println("Position error! "); 
      while(1); 
  }
}

void nav_once() {
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  Serial.println(location); 
  if(line_sensor_4_value == 0) {
    follow_line(250,0,100); 
  }
  else {
    handle_junction(); 
  }
}  

void handle_ramp() {
  while(location==4 && digitalRead(line_sensor_2)==0 && digitalRead(line_sensor_1)==0 && digitalRead(line_sensor_3)==0) {
    Serial.println("on ramp"); 
    follow_wall(5.0); 
  }
}

void handle_tunnel() {
  while(location==7 && digitalRead(line_sensor_2)==0 && digitalRead(line_sensor_1)==0 && digitalRead(line_sensor_3)==0) {
    Serial.println("in tunnel"); 
    follow_wall(5.0); 
  }
}

void follow_wall(double target_dist) { 
  double dist_side = US_side.dist(); 
  Serial.println(dist_side); 
  if(dist_side<target_dist) {
    motor(250, 150, 20); 
    Serial.println("turn right"); 
  }
  else if(dist_side>target_dist) {
    motor(150, 250, 20); 
    Serial.println("turn left"); 
  }
}

void handle_block() {
  double dist_front = US_front.dist(); 
  Serial.print("dist_front: ");
  Serial.println(dist_front); 
  if(dist_front<3.5){
    Serial.println(US_front.dist()); 
    grab_block(); 
    //delay(1000); 
    //release_block(); 
    //while(1);
  }
}
