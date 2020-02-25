int LedPin = 13;
int delayTime = 100;
void setup() {
  // put your setup code here, to run once:
  pinMode(LedPin,OUTPUT);
}
void flash(int delayTime)
{
  digitalWrite(LedPin,HIGH);
  delay(delayTime);
  digitalWrite(LedPin,LOW);
  delay(delayTime);  
}
int i;
int delayTime2 = 500;
void loop() {
  // put your main code here, to run repeatedly:
  flash(delayTime2);
  i++;
  delayTime2 -= 20;
  if(i%20==0)
    delay(4000);
  if(delayTime2==0)
    delayTime2 = 500;
}
