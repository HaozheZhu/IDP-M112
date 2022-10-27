#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>
#include <Arduino_LSM6DS3.h>
#include <Servo.h>

Servo servo_grab; //servo 2
Servo servo_lift; //servo 1

HCSR04 US_front(US_trig, US_echo);
HCSR04 US_side(US_trig_s,US_echo_s);

#include <FastPID.h>

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);


int location = 6; //refer to map
bool has_block = 0; //0 = no block, 1 = has block
bool magnetic = 0; //-1 = no block, 0 = not magnetic, 1 = magnetic
bool in_tunnel = 0; //0 = not in tunnel, 1 = in tunnel
