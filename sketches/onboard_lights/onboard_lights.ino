#define ONBOARD_LED 16
//#define ONBOARD_LED 2

void setup() {
  Serial.begin(9600);
  pinMode(ONBOARD_LED, OUTPUT);
}

void loop() {
  digitalWrite(ONBOARD_LED, HIGH);
  Serial.println("LED on");
  delay(1000);
  
  digitalWrite(ONBOARD_LED, LOW);
  Serial.println("LED off");
  delay(1000);
}
