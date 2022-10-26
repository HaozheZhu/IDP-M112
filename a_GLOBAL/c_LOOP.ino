void loop() {
  nav_once(); //line following and junction handling

  handle_tunnel(); //detect and handle tunnel if in 
  handle_block(); //detect and handle block if close
}
