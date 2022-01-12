#define GPIO13_D7 13

void setup() {
  Serial.begin(9600);
  pinMode(GPIO13_D7, OUTPUT);
}

void loop() {
  digitalWrite(GPIO13_D7, HIGH);
  Serial.println("LED on");
  delay(1000);
  
  digitalWrite(GPIO13_D7, LOW);
  Serial.println("LED off");
  delay(1000);
}
