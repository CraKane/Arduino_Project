int LEDPin = 13;
int delayTime = 200;
void setup() {
  // put your setup code here, to run once:
  pinMode(LEDPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LEDPin,HIGH);
  delay(delayTime);
  digitalWrite(LEDPin,LOW);
  delay(delayTime);
}
