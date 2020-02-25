int LedPin = 13;
int delayTime = 100;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(LedPin,HIGH);
  delay(delayTime);
  digitalWrite(LedPin,LOW);
  delay(delayTime);
  if(delayTime < 1)
    delayTime = 100;
  else
    delayTime -= 1;
}
