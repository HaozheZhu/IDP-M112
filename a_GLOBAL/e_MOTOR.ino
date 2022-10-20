
class motor_shield_interface{
    bool m1_forward, m2_forward, m1_release, m2_release;
    byte m1_speed, m2_speed;
    public:
    motor_shield_interface(){
      Adafruit_MotorShield AFMS = Adafruit_MotorShield();
      Adafruit_DCMotor *M1 = AFMS.getMotor(1);
      Adafruit_DCMotor *M2 = AFMS.getMotor(2);
      //set initial
      this->init();
      m1_forward = true;
      m2_forward = true;
      m1_speed =0;
      m2_speed =0;
    }
    void init(){
       if (!AFMS.begin()) {         // create with the default frequency 1.6KHz
       //if (!AFMS.begin(1000)) {  // OR with a different frequency, say 1KHz
      Serial.println("Could not find Motor Shield. Check wiring.");
      while (1);
    }
      Serial.println("Motor Shield found.");
      M1->run(RELEASE);
      m1_release = true;
      M2->run(RELEASE);
      m2_release = true;
    }
};
