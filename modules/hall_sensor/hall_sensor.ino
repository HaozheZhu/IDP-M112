#include <Servo.h>
Servo servo_grab; 
Servo servo_lift;

void setup() {
  // put your setup code here, to run once:
  pinMode(A1, INPUT); 
  Serial.begin(9600);

  servo_grab.attach(9); //servo 2
  servo_lift.attach(10); //servo 1
  servo_lift.write(124); 
  servo_grab.write(58);    
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int reading; 
  reading = analogRead(A1); 
  Serial.println(reading); 
  delay(100); 
}
