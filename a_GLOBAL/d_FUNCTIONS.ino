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
  M1->run(RELEASE);
  M2->run(RELEASE);
  m1_state.direction = RELEASE;
  m2_state.direction = RELEASE;
  m1_state.speed = 250;
  m2_state.speed = 250;
}

void init_hall(){
  pinMode(hall_pin, INPUT); 
}

double ultrasound_front(bool raw){
  static double running_total =0;
  static HCSR04 sensor(US_trig, US_echo);
  if (raw){
    return sensor.dist();
  }
  else{
    running_total = 0.5*(sensor.dist()+running_total);
    return running_total;
  }
}
double ultrasound_side(bool raw){
  static double running_total =0;
  static HCSR04 sensor(US_trig_s, US_echo_s);
  if (raw){
    return sensor.dist();
  }
  else{
    running_total = 0.5*(sensor.dist()+running_total);
    return running_total;
  }
}
void motor_release(motor_select motors = BOTH){
  switch(motors){
    case BOTH:
      if (m1_state.direction !=RELEASE){
        M1->run(RELEASE);
        m1_state.direction =RELEASE;
      }
      if (m2_state.direction !=RELEASE){
        M2->run(RELEASE);
        m2_state.direction =RELEASE;
      }
      break;
    case MOTOR_M1:      
      if (m1_state.direction !=RELEASE){
        M1->run(RELEASE);
        m1_state.direction =RELEASE;
      }
      break;  
    case MOTOR_M2:
      if (m1_state.direction !=RELEASE){
        M1->run(RELEASE);
        m1_state.direction =RELEASE;
      }
      break;

    default:
    Serial.println ("Error in motor_release, invalid selection of motors -  Must be BOTYH, LEFT or RIGHT");
  }
}
void motor_interface(byte  m1_dir, byte m2_dir, byte m1_speed, byte m2_speed){
  //prevents unneeded comunication with motors
  //first update direction
  if ((m1_state.direction != m1_dir) and (m2_state.direction != m2_dir)){
    if ((m1_state.direction != RELEASE)or(m2_state.direction!=RELEASE)){
      motor_release(BOTH);
      delay(5);
      M1->run(m1_dir);
      m1_state.direction= m1_dir;
      M2->run(m2_dir);
      m2_state.direction= m2_dir;
    }
  }
  else if (m1_state.direction != m1_dir){
    if (m1_state.direction != RELEASE){
      motor_release(MOTOR_M1);
      delay(5);
    }
    M1->run(m1_dir);
    m1_state.direction= m1_dir;
  }
  else if (m2_state.direction != m2_dir){
    if (m2_state.direction != RELEASE){
      motor_release(MOTOR_M2);
      delay(5);
    }
    M2->run(m2_dir);
    m2_state.direction= m2_dir;
  }
  
  //Then check speeds
  if (m1_state.speed !=m1_speed){
    M1->setSpeed(m1_speed);
    m1_state.speed = m1_speed;
  }
  if(m2_state.speed !=m2_speed){
    M2->setSpeed(m2_speed);
    m2_state.speed = m2_speed;
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

void block_approach_line(){
  //Best activated when the block is closeset
  double target_speed;
  target_speed = target_speed-approach_PID.step(10, ultrasound_front(true));
  // testing motor(target_speed, 0, 50);
  //line_following_linear(target_speed);
  //
}

void follow_wall(double target_dist){
  static FastPID wall_PID(15 ,0.05 , 0 , 10, 8 , true);
  target_dist = wall_PID.step(5, ultrasound_side(true));
  motor(150, target_dist, 50);
}
bool dectect_tunnel(){
  if(ultrasound_side() < 20.0){
    return true;
  }
  else{return false;}
}
