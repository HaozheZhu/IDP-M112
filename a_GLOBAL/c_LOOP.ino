void loop() {
  //nav_once(); 
  follow_line(250, 0, 10); 

  Serial.println(US_front.dist()); 
  delay(500); 
  
  if(US_front.dist()<5){
    grab_block(); 
    delay(2000); 
    release_block(); 
    while(1);
  }

}
