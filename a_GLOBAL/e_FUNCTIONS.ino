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
  else {
    M1->setSpeed(abs(m1)); 
    M2->setSpeed(abs(m2)); 
    M1->run(BACKWARD);
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
  else {
    motor(forward, forward, dt); 
  }
}

void follow_line_return(int forward, int turn, int dt) {
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  
  if(line_sensor_1_value==0 && line_sensor_4_value==0){
    motor(forward, forward, dt); 
  }
  else if(line_sensor_1_value==1 && line_sensor_4_value==0){
    motor(turn, forward, dt); 
  }
  else if(line_sensor_1_value==0 && line_sensor_4_value==1){
    motor(forward, turn, dt); 
  }
  else {
    motor(forward, forward, dt); 
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
      Serial.println("At position 3 now"); 
      delay(1000); 
      motor(250, 250, 1000); 
      delay(1000); 
      while(digitalRead(line_sensor_3)==0){
        motor(250, -250, 100); 
        delay(10); 
      }
      motor(250, -250, 150); 
      break; 
    case 3: 
      location = 4; 
      Serial.println("At position 4 now"); 
      motor(250, 250, 400); 
      break; 
    case 4: 
      location = 5; 
      Serial.println("At position 5 now"); 
      motor(250, 250, 3000); 
      break; 
    case 5: 
      location = 6; 
      motor(250, 250, 3000); 
      break; 
    case 6: 
      location = 7; 
      motor(250, 250, 500); 
      break; 
    case 7: 
      if(has_block && !magnetic) {
        location = 9; 
        turn_right_green(); 
        release_block(); 
        motor(-250, -250, 2000); 
        while(digitalRead(line_sensor_4)==0){
        motor(-250, 250, 100); 
        }
        motor(250, 250, 1000); 
        motor(0, 250, 400); 
      }
      else {
        location = 9; 
        motor(250, 250, 300); 
      }
      break; 
    case 9: 
      if(has_block){
        location = 15; 
        motor(250, 250, 300); 
      }
      else {
        turn_right_red(); 
        motor(250, 0, 200); 
        double dist_front = US_front.dist(); 
        Serial.println(dist_front); 
        while(1){ 
          delay(100); 
          double dist_front = US_front.dist(); 
          Serial.println(dist_front); 
          if(dist_front > 10) {
          motor(150, 150, 100); 
          }
          else {
            break; 
          }
        }
        digitalWrite(amber_led, LOW); 
        while(1); 
      }
      
      break; 
    case 10: 
      motor(250, 0, 200); 
      motor(250, 250, 500); 
      Serial.println("Dropping non-magnetic block"); 
      release_block(); 
      has_block = 0; 
      delay(1000); 
      motor(-250, -250, 2000); 
      while(digitalRead(line_sensor_4)==0){
        motor(-250, 250, 100); 
      }
      while(1);
      break; 
    case 15: 
      if(has_block && magnetic) {
        location = 12; 
        turn_right_red(); 
      }
      else {
        location = 4; 
        motor(250, 250, 500); 
      }
    case 12: 
      motor(250, 0, 200); 
      motor(250, 250, 500); 
      Serial.println("Dropping magnetic block"); 
      release_block(); 
      delay(1000); 
      Serial.println("Released block"); 
      motor(-250, -250, 2000); 
      while(digitalRead(line_sensor_4)==0) {
        motor(-250, -250, 100); 
      }
      motor(250, 250, 500); 
      delay(1000); 
      motor(250, -250, 800);      
      while(digitalRead(line_sensor_1)==0) {
        motor(250, -250, 100);   
      } 
      while(digitalRead(line_sensor_2)==0) {
        follow_line_return(250,0,50); 
      }
      motor(250, 250, 500); 
      motor(0, 250, 2800); 
      while(1){
        delay(100); 
        double dist_front = US_front.dist(); 
        Serial.println(dist_front); 
        if(dist_front > 10) {
        motor(150, 150, 100); 
        }
        else {
          break; 
        }
      }
      digitalWrite(amber_led, LOW); 
      while(1); 
      break; 
    default: 
      Serial.println("Position error! "); 
      while(1); 
  }
}

void turn_right_green() {
  delay(1000); 
  motor(250, -250, 1000);
  motor(250, 250, 1000); 
}

void turn_right_red() {
  delay(1000); 
  motor(250, 250, 1000); 
  delay(1000); 
  motor(250,-250, 1000); 
  while(digitalRead(line_sensor_3)==0){
    motor(250, -250, 100); 
    delay(10); 
  }
  motor(250, -250, 300); 
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
    follow_wall(8); 
  }
}

void handle_tunnel() {
  while(location==7 && digitalRead(line_sensor_2)==0 && digitalRead(line_sensor_1)==0 && digitalRead(line_sensor_3)==0) {
    Serial.println("in tunnel"); 
    follow_wall(5); 
  }
}

void follow_wall(double target_dist) { 
  double dist_side = US_side.dist(); 
  Serial.println(dist_side); 
  delay(50); 
  if(dist_side<target_dist) {
    motor(150, 250, 50); 
    Serial.println("turn left"); 
  }
  else if(dist_side>target_dist) {
    motor(250, 150, 50); 
    Serial.println("turn right"); 
  }
}

void handle_block() {
  double dist_front = US_front.dist(); 
  Serial.print("dist_front: ");
  Serial.println(dist_front); 
  if(dist_front<20 && !has_block && servo_lift.read()-121>5) {
    delay(1000); 
    servo_lift.write(121); 
    delay(1000); 
  }
  if(dist_front<3.5){
    Serial.println(US_front.dist()); 
    grab_block(); 
  }
}

void grab_block() {
  delay(1000); 
  int value = analogRead(hall_sensor); 
  Serial.println(value); 
  if(value>500) {
    digitalWrite(red_led, HIGH);  
    magnetic = 1; 
    Serial.println("magnetic! "); 
  }
  else {
    digitalWrite(green_led, HIGH); 
    magnetic = 0; 

    Serial.println("NOT magnetic! "); 
  }
  has_block = 1; 
  delay(5000); 

  servo_grab.write(114); 
  delay(1000); 
  servo_lift.write(155); 
  delay(1000); 
}

void release_block() {
  servo_lift.write(124); 
  delay(1000); 

  servo_grab.write(58); 
  delay(2000);
  has_block = 0; 

  servo_lift.write(155); 
  delay(1000); 

  digitalWrite(red_led, LOW); 
  digitalWrite(grab_block, LOW); 
}
