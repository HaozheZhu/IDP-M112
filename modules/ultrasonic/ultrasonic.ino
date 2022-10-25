#include <HCSR04.h>
#include <Servo.h>

HCSR04 hc(6,7);//initialisation class HCSR04 (trig pin , echo pin)
Servo servo_grab; 
Servo servo_lift; 


void setup()
{ 
  Serial.begin(9600); 
  servo_grab.attach(9); //servo 2
  servo_lift.attach(10); //servo 1
  servo_lift.write(150); 
  servo_grab.write(58);    
  delay(2000);

}

void loop()
{ 
  Serial.println( hc.dist() ); 
  delay(500); 
}//return curent distance in serial