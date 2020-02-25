int pinNum = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  tone(pinNum, 1000, 2000);
  delay(1000);
  tone(pinNum, 2000);
  noTone(pinNum);
}
