void loop() {
  //motor_test_run(); 
  //Serial.println( hc.dist() ); 
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  int line_sensor_3_value = digitalRead(line_sensor_3); 
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  if(true) {
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
  if(line_sensor_3_value == 0 && line_sensor_4_value == 0) {
    //going off the line
    follow_line(100,20,100); 
  }
  if(line_sensor_3_value == 1 && line_sensor_4_value == 1) {
    Serial.println("At cross"); 
    delay(3000); 
    follow_line(250,0,500); 
  }
  if(line_sensor_3_value == 1 && line_sensor_4_value == 0) {
    Serial.println("At left junction"); 
    delay(3000); 
    follow_line(250,0,500); 
  }
  if(line_sensor_3_value == 0 && line_sensor_4_value == 1) {
    Serial.println("At right junction"); 
    delay(3000); 
    follow_line(250,0,500); 
  }

}
