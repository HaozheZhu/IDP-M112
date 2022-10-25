void setup() {
  Serial.begin(9600);
  init_line_sensors(); 
  init_motors(); 
  init_hall(); 
  servo_grab.attach(9); //servo 2
  servo_lift.attach(10); //servo 1
  servo_lift.write(150); 
  servo_grab.write(58);    
  delay(10000);

  //robot starting routine
  if(0){
    int line_sensor_1_value = digitalRead(line_sensor_1); 
    int line_sensor_2_value = digitalRead(line_sensor_2); 
    int line_sensor_3_value = digitalRead(line_sensor_3); 
    int line_sensor_4_value = digitalRead(line_sensor_4); 
    while(line_sensor_1_value == 0 && line_sensor_4_value == 0) {
      int line_sensor_1_value = digitalRead(line_sensor_1); 
      int line_sensor_2_value = digitalRead(line_sensor_2); 
      int line_sensor_3_value = digitalRead(line_sensor_3); 
      int line_sensor_4_value = digitalRead(line_sensor_4); 
      motor(250, 250, 100); 
    }
    motor(250, 250, 200); 
    while(line_sensor_1_value == 0 && line_sensor_4_value == 0) {
      int line_sensor_1_value = digitalRead(line_sensor_1); 
      int line_sensor_2_value = digitalRead(line_sensor_2); 
      int line_sensor_3_value = digitalRead(line_sensor_3); 
      int line_sensor_4_value = digitalRead(line_sensor_4); 
      nav_once(); 
    }
  }
  //}

}
