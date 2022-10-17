
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
double Kpl=1, Kil=0, Kdl=0.01, Hz=10, Kpa=1, Kia=0, Kda=0.01;
int output_bits = 8;
bool output_signed = true;
FastPID line_PID(Kpl, Kil, Kdl, Hz,output_bits , output_signed);
FastPID approach_PID(Kpa, Kia, Kda, Hz,output_bits , output_signed);
