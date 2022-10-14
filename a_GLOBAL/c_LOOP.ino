void loop() {
  //motor_test_run();   
  //steer_left(); 
  /*M1->setSpeed(100);
  M2->setSpeed(100);
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(2000);
  */
  motor(255, 0, 1000);
  delay(1000);
  motor(0, 255, 1000);
  delay(1000);
  motor(255, 0, 1000);
  delay(1000);
  motor(255, -255, 1000);
  delay(1000);
}
