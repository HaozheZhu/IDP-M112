
#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>

//initialise U/S sensor
HCSR04 hc(5,6);
#include <FastPID.h>

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

//initialise control loops
float line_Kp=0.1, line_Ki=0.5, line_Kd=0, Hz=10;
int output_bits = 8;
bool output_signed = true;
FastPID linePID(line_Kp, line_Ki, line_Kd, Hz,output_bits , output_signed);
