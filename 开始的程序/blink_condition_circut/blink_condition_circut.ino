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
  delayTime += 100;
  if(delayTime > 2000)
    delayTime  = 100;
}
