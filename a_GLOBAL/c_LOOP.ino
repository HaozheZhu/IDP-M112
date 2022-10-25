void loop() {
  //nav_once(); 
  follow_line(250, 0, 100); 

  Serial.println(US_front.dist()); 
  delay(50); 
  
  if(US_front.dist()<3.5){
    Serial.println(US_front.dist()); 
    grab_block(); 
    delay(2000); 
    release_block(); 
    while(1);
  }

}
