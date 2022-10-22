#include <HCSR04.h>
class ultrasound_interace{
  // Holds pin numbers, calculates rolling averages to reduce noise
  double running_average;
  unsigned long last_read_time;
  public:
  ultrasound_interace(int trig_pin, int echo_pin){
    HCSR04 ultrasound(trig_pin, echo_pin);
    running_average = read_raw();
    last_read_time = millis();
  }
  double read_raw(){
    ultrasound.dist();
  }
};
