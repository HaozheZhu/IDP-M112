int reading; 

void setup() {
  // put your setup code here, to run once:
  pinMode(3, INPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  reading = digitalRead(3); 
  Serial.println(reading); 
  delay(200); 
}
