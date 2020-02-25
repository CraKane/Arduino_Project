const int TrigPin = 2;
const int EchoPin = 3;
float cm;//单位为厘米

void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT); 
}

void loop()
{ 
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW);
  cm = pulseIn(EchoPin, HIGH) / 58; //这是一个换算公式
  //将回波时间换算成cm
  cm = (int(cm * 100)) / 100; //保留两位小数
  Serial.print(cm);
  Serial.println("cm");
  delay(500); 
}
