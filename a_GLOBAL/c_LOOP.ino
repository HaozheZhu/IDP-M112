void loop() {
  //motor_test_run();   
  //steer_left(); 
  /*M1->setSpeed(100);
  M2->setSpeed(100);
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(2000);

  motor(1, 0, 1000);
  delay(1000);
  motor(0, 2, 1000);
  delay(1000);
  motor(1, 0, 1000);
  delay(1000);
  motor(1, -1, 1000);
  delay(1000);
    */
  for (int i = 0 ; i<255; i =i+5){
    motor(i, 0, 1000);
    delay(1000);
  }
}
