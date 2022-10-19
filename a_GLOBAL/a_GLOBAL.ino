#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>

//initialise U/S sensor
HCSR04 ultrasound(US_trig, US_echo);
#include <FastPID.h>

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

//initialise control loops
//line
double Hz=10;
FastPID line_PID(line_following_proportianal, line_following_integral, line_following_derivative , Hz, PID_output_bits , PID_output_signed);
FastPID approach_PID(block_approach_proportianal, block_approach_integral, block_approach_derivative, Hz, PID_output_bits , PID_output_signed);
