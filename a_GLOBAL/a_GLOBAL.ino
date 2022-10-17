
#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <FastPID.h>

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

//initialise control loops
float line_Kp=0.1, line_Ki=0.5, line_Kd=0, Hz=10;

FastPID linePID(Kp, Ki, Kd, Hz, int output_bits = 8, bool output_signed = true);
