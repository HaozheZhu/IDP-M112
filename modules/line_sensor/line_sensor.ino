void setup() {
  // put your setup code here, to run once:
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //1 means white, 0 means black
  Serial.print("Line sensor 1: ");
  Serial.println(digitalRead(2)); 
  Serial.print("Line sensor 2: ");
  Serial.println(digitalRead(3)); 
  Serial.print("Line sensor 3: ");
  Serial.println(digitalRead(4)); 
  Serial.print("Line sensor 4: ");
  Serial.println(digitalRead(5)); 
  delay(200); 
}
