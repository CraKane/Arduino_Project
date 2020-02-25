#include <boarddefs.h>
#include <IRremote.h>
#include <IRremoteInt.h>
#include <Servo.h>
Servo myServo;
int Recv_pin = 11; //定义红外接收器信号端口是11引脚
IRrecv irr(Recv_pin);
decode_results result;
void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);
  Serial.begin(9600);
  irr.enableIRIn();//初始化红外接收器
}

void loop() {
  // put your main code here, to run repeatedly:
  if(irr.decode( &result))
  {
    Serial.println(result.value, HEX);
    //Serial.println();
    irr.resume();//接收下一个值    
  }
}
