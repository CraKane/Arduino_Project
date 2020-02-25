#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>
Servo myServo;
const int Recv_pin = 11; //定义红外接收器信号端口是11引脚
const int ledPinsub = 13;
const int ledPinadd = 5;
int serPos = 90;
IRrecv irr(Recv_pin);
decode_results result;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  myServo.attach(9);
  pinMode(ledPinsub, OUTPUT);
  pinMode(ledPinadd, OUTPUT);
  irr.enableIRIn();//初始化红外接收器
  myServo.write(serPos);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irr.decode( &result))
  {
    Serial.println(result.value, HEX);
    if(result.value == 0xFF02FD)//add
    {
       serPos += 10;
       //if(serPos > 180) serPos = 0;
       myServo.write(serPos);
       digitalWrite(ledPinadd, HIGH);
       delay(100);
       digitalWrite(ledPinadd, LOW);
    }
    else if(result.value == 0xFF22DD)//sub   
    {
       serPos -= 10;
       //if(serPos < 0) serPos = 180;
       myServo.write(serPos);
       digitalWrite(ledPinsub, HIGH);
       delay(100);
       digitalWrite(ledPinsub, LOW);
    }
    irr.resume();//接收下一个消息
  }
}
