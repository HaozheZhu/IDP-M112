#include <Adafruit_MotorShield.h>
#include "definitions.h"

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);
  init_line_sensors(); 
  init_motors(); 
}

void loop() {
  if(line_sensor_left==0 && line_sensor_right==0){
    M1->run(FORWARD);
    M2->run(FORWARD); 
    delay(100);  
    M1->run(RELEASE);
    M2->run(RELEASE); 
    delay(100);
  }
  else if(line_sensor_left==1 && line_sensor_right==0){
    steer_left(); 
  }
  else if(line_sensor_left==0 && line_sensor_right==1){
    steer_right(); 
  }
}