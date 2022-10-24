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


enum motor_select{
  MOTOR_M1,
  MOTOR_M2,
  BOTH
};
struct motor_state{
  byte direction; //foward =1 , back =2, 3 =brake, 4 = release
  byte speed;
}m1_state, m2_state;
