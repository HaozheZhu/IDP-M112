#define line_sensor_1 2
#define line_sensor_2 3
#define line_sensor_3 4
#define line_sensor_4 5
//Servo pins for sheild
#define servo_pin_one 9
#define servo_pin_two 10 
#define hall_pin 11 // Temp, here to allow compilation
// Pins for ultrasound
#define US_trig 1
#define US_echo 0
//Constants for PID controller setup
#define PID_output_bits 8
#define PID_output_signed true
#define line_following_proportianal 1
#define line_following_integral 0.1
#define line_following_derivative 0.1
//Block approach
#define block_approach_proportianal 25.
#define block_approach_integral 0.1
#define block_approach_derivative 0.
