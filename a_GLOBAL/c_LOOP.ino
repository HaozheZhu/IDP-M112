void loop() {
  //motor_test_run(); 
  //Serial.println( hc.dist() ); 
  int line_sensor_left_value = digitalRead(line_sensor_left); 
  int line_sensor_right_value = digitalRead(line_sensor_right); 
  int line_sensor_front_value = digitalRead(line_sensor_front); 
  int line_sensor_back_value = digitalRead(line_sensor_back); 

  if(line_sensor_front_value == 0 && line_sensor_back_value == 1){
    //going off the line
    follow_line(250); 
  }
  else if(line_sensor_front_value == 1 && line_sensor_back_value == 1){
    //on the line but at junction
    if(line_sensor_left_value == 1 && line_sensor_right_value == 0){
      Serial.println("At left Cross"); 
      //handle cross
    }
    if(line_sensor_right_value == 1 && line_sensor_left_value == 0){
      Serial.println("At right Cross"); 
      //handle cross
    }
  }
  
  delay(20); 
  //motor(100, 0, 50); 
}
