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
void motor_release(bool m1, bool m2){
  //prevents unneeded comunication with board be checking if motors are released.
  // true to release
  if (m1 and !(m1_release)){
    M1->run(RELEASE);
    m1_release = true;
  }
  if (m2 and !(m2_release)){
    M2->run(RELEASE);
    m2_release = true;
  }
}
void motor_interface(bool m1_forward, byte m1_speed, bool m2_forward, byte m2_speed){
  //prevents unneeded comunication with motors
  static bool m1_prev_forward = true;
  static bool m2_prev_forward = true;
  static byte m1_prev_speed = 0;
  static byte m2_prev_speed = 0;
  if ((m1_prev_forward != m1_forward) or (m1_release and (m1_speed!=0))){
    motor_release(true, false);  
    if (m1_forward){
      M1->run(FORWARD);
    }
    else{
      M1->run(BACKWARD);
    }
    m1_prev_forward = m1_forward;
    m1_release = false;
  }
  if ((m2_prev_forward != m2_forward)or m2_release){
    motor_release(false, true);
    if (m2_forward){
      M2->run(FORWARD);
    }
    else{
      M2->run(BACKWARD);
    }
    m2_prev_forward = m2_forward;
    m2_release =false;
  }
 //ask if motor can switch striaght between speeds/foward and reverse 
  if (m1_prev_speed !=m1_speed){
    M1->setSpeed(m1_speed);
    m1_prev_speed = m1_speed;
  }
  if(m2_prev_speed !=m2_speed){
    M2->setSpeed(m2_speed);
    m2_prev_speed = m2_speed;
  }
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

void line_following_linear(int target_speed){
  static double error = 0;
  // Issue, define the behaviour when the line is lost.
  //Take sensor readings
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  // Calculate error in line (improve this)
  if (line_sensor_1_value){
    error = 1;
  }
  if (line_sensor_2_value){
    error =-1;
  }
  if (!(line_sensor_1_value or line_sensor_2_value) and line_sensor_1_value and line_sensor_2_value) {
  }
  // Command motors
  motor(target_speed, line_PID.step(0.0, error), 10);
}
void block_approach_line(){
  //Best activated when the block is closeset
  double target_speed;
  target_speed = approach_PID.step(0, ultrasound.dist());
  //line_following_linear(target_speed);
  //
}
