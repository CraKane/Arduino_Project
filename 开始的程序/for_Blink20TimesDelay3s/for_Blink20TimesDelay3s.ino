int LedPin = 13;
int delayTime = 100;
int count = 0;
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
  count++;
  if(count==20)  
    delay(3000);
}
