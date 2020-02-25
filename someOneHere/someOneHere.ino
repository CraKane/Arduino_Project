#include<Servo.h>
Servo myServo;
const int serPos = 0;//初始化舵机为0度
const int TrigPin = 2;
const int EchoPin = 3;
const int ledPin = 4;
const int BeepPin = 6;
float cm;//单位为厘米

void setup()
{
  Serial.begin(9600);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT); 
  pinMode(ledPin, OUTPUT);
  myServo.attach(5);//舵机接5引脚，这个可以自己调整
}

void loop()
{ 
  myServo.write(serPos);
  /*以下代码是用户界面容易理解的输出语句，对于功能没有任何影响*/
  Serial.println("test start:");
  /*以上代码*/
  delay(1000);//看到start就开始测试
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
  if(cm <= 5)//有人来了，嘘~
  {
    /*以下代码是用户界面容易理解的输出语句，对于功能没有任何影响*/
    Serial.println("some one coming, lock it!");
    Serial.println("Door is open");
    /*以上代码*/
    digitalWrite(ledPin, HIGH);
    tone(BeepPin, 1000);
    myServo.write(90);
    /*以下代码是用户界面容易理解的输出语句，对于功能没有任何影响*/
    Serial.println("locked, save now!");
    /*以上代码*/
    delay(1500);//可以实验看看这个会发生什么？
    digitalWrite(ledPin, LOW);
    noTone(BeepPin);
  }
  /*以下代码是用户界面容易理解的输出语句，对于功能没有任何影响*/
  Serial.println("test end");
  Serial.println("test resetting");
  /*以上代码*/
   delay(2000);
}
