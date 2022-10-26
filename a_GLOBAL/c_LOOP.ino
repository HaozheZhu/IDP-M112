void loop() {
  nav_once(); 




  if(0){
    double dist_side = US_side.dist(); 
    Serial.print("out of tunnel, dist_side:  ");
    Serial.println(dist_side); 
    while(dist_side < 6) {
      dist_side = US_side.dist(); 
      follow_wall(5.0, dist_side); 
      Serial.print("in tunnel: ");
      Serial.println(dist_side); 
    }
    
    double dist_front = US_front.dist(); 
    Serial.print("dist_front: ");
    Serial.println(dist_front); 
    if(dist_front<3.5){
      Serial.println(US_front.dist()); 
      grab_block(); 
      delay(2000); 
      release_block(); 
      while(1);
    }
  }
  

}
