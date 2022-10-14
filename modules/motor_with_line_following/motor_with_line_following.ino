#include <Adafruit_MotorShield.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();

Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

void setup() {
  Serial.begin(9600);           // set up Serial library at 9600 bps

  //initialise motors
  if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
  // if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
    Serial.println("Could not find Motor Shield. Check wiring.");
    while (1);
  }
  Serial.println("Motor Shield found.");
  M1->setSpeed(250);
  M2->setSpeed(250);
}

void loop() {
  M1->run(FORWARD);
  M2->run(FORWARD); 
  delay(1000); 

  M1->run(BACKWARD);
  M2->run(BACKWARD);
  delay(1000); 

  M1->run(RELEASE);
  M2->run(RELEASE); 
  delay(1000);
}