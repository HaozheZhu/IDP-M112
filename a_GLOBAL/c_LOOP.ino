void loop() {
  //motor_test_run(); 
  //Serial.println( hc.dist() ); 
  int line_sensor_1_value = digitalRead(line_sensor_1); 
  int line_sensor_2_value = digitalRead(line_sensor_2); 
  int line_sensor_3_value = digitalRead(line_sensor_3); 
  int line_sensor_4_value = digitalRead(line_sensor_4); 
  if(true) {
    /*Serial.print("Line sensor 1 = "); 
    Serial.println(line_sensor_1_value); 
    Serial.print("Line sensor 2 = "); 
    Serial.println(line_sensor_2_value); 
    Serial.print("Line sensor 3 = "); 
    Serial.println(line_sensor_3_value); 
    Serial.print("Line sensor 4 = "); 
    Serial.println(line_sensor_4_value); 
    Serial.print("Ultrasound = "); */
    Serial.println("Front");
    Serial.println(ultrasound_front(true));
    Serial.println(ultrasound_front()); 
    Serial.println("Side:");
    Serial.println(ultrasound_side(true)); 
    Serial.println(ultrasound_side()); 
    Serial.println("------------------------");
    delay(10); 
  }
  //follow_wall(10);
  //delay(1000);

  //block_approach_line();

}
