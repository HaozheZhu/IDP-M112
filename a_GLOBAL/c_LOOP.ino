void loop() {
  //nav_once(); 
  follow_line(250, 0, 100); 

  Serial.print("out of tunnel ");

  double dist = US_side.dist(); 
  Serial.println(dist); 
  while(dist < 10) {
    dist = US_side.dist(); 
    follow_wall(5.0, dist); 
    Serial.print("in tunnel: ");
    Serial.println(dist); 
  }
  
  if(US_front.dist()<3.5){
    Serial.println(US_front.dist()); 
    grab_block(); 
    delay(2000); 
    release_block(); 
    while(1);
  }

}
