void loop() {
  //nav_once(); 
  follow_line(250, 0, 100); 
  if(block_approach_line()){
    while(1); 
  }
  

}
