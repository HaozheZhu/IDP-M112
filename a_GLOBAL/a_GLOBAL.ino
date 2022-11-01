#include <Adafruit_MotorShield.h>
#include "definitions.h"
#include <HCSR04.h>
#include <Arduino_LSM6DS3.h>
#include <Servo.h>

//initialise servos
Servo servo_grab; //servo 2
Servo servo_lift; //servo 1

//initialise U/S sensors
HCSR04 US_front(US_trig, US_echo);
HCSR04 US_side(US_trig_s,US_echo_s);

//initialise motors
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *M1 = AFMS.getMotor(1);
Adafruit_DCMotor *M2 = AFMS.getMotor(2);

int location = 15; //refer to map
bool has_block = 1; //0 = no block, 1 = has block
bool magnetic = 1; //-1 = no block, 0 = not magnetic, 1 = magnetic