const short int EXT_D1 = 5;
const short int EXT_D2 = 4;
const short int EXT_D3 = 0;

const short redPin = EXT_D1;
const short greenPin = EXT_D2;
const short bluePin = EXT_D3;

void setup() {
  Serial.begin(9600);
  pinMode(redPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  rainbow(250);
  rgb(0,0,0,750);
}

void rgb(short r, short g, short b, short delayDuration) {
  analogWrite(redPin, r);
  analogWrite(greenPin, g);
  analogWrite(bluePin, b);
  delay(delayDuration);
}

void rainbow(short delayDuration) {
  rgb(255, 255, 255, delayDuration);
  rgb(255, 0, 0, delayDuration);
  rgb(255, 127, 0, delayDuration);
  rgb(255, 255, 0, delayDuration);
  rgb(0, 255, 0, delayDuration);
  rgb(0, 0, 255, delayDuration);
  rgb(75, 0, 130, delayDuration);
  rgb(143, 0, 255, delayDuration);
  rgb(255, 255, 255, delayDuration);
  delay(delayDuration);
}
