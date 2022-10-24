void loop() {

  nav_once(); 

  double dist_front = ultrasound_front(1); 
  if (dist_front<5.0){
    M1->run(BRAKE);
    M2->run(BRAKE);
    delay(10000);
  }
  Serial.println(dist_front);
  
}
