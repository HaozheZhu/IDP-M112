#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>

//initialise U/S sensor
/*
HCSR04 US_front(US_trig, US_echo);
HCSR04 US_right(US_trig_r,US_echo_r);
*/
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

int LOCATION = 1; //refer to map
int HAS_BLOCK = 0; //0 = no block, 1 = has block
int MAGNETIC = -1; //-1 = no block, 0 = not magnetic, 1 = magnetic
int IN_TUNNEL = 0; //0 = not in tunnel, 1 = in tunnel

