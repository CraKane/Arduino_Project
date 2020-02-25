int pwm = 0;
int Pin = 3;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);//串口比特率默认值 有没有都一样
  pinMode(Pin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(Pin,pwm);
  delay(1000);
  pwm += 20;
  Serial.println(pwm);
  if(pwm >= 200)
  {
    pwm = 0;
  }
}
