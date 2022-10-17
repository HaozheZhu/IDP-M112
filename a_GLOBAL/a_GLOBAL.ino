#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>

//initialise U/S sensor
HCSR04 hc(5,6);

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);


