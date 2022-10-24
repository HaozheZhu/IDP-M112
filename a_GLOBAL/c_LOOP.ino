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
    Serial.print("Ultrasound = "); 
    Serial.println(ultrasound.dist()); 
    Serial.println("------------------------");
    delay(0); 
  }
  
  nav_once(); 
  
  if (ultrasound.dist()> 0.0){
    block_approach_line();
  }
  
  //block_approach_line();

}
