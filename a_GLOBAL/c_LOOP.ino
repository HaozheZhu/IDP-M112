void loop() {
  nav_once(); //line following and junction handling

  if(location == 7) {handle_tunnel();} //detect and handle tunnel if in 
  if(location == 6) {handle_block();} //detect and handle block if close
  handle_ramp(); 
}
