
class motor_shield_interface{
    enum dir{forward, backwards, released}m1_direction, m2_direction;
    byte m1_speed, m2_speed;
    public:
    motor_shield_interface(){
      Adafruit_MotorShield AFMS = Adafruit_MotorShield();
      Adafruit_DCMotor *M1 = AFMS.getMotor(1);
      Adafruit_DCMotor *M2 = AFMS.getMotor(2);
      //set initial
      this->init();
      m1_direction = released;
      m2_direction = released;
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
      M2->run(RELEASE);
      m1_direction = released;
      m2_direction = released;
    }
};
