#include <Servo.h>    // 声明调用Servo.h库
#include <IRremote.h> //可以使用红外控制库
Servo myservo;        // 创建一个舵机对象

//遥控器控制按键设置
const long SPEEDUP = 0xFF629D; 
const long SPEEDDOWN = 0xFFA857; 
const long LEFT = 0xFF22DD;    
const long RIGHT = 0xFFC23D;    

int RECV_PIN = 12;        //定义红外接收器的引脚为12    
IRrecv irrecv(RECV_PIN);   
decode_results results;  

const unsigned char pinMotorCW[2]  = {6, 10};   // 接控制电机1顺时针转的 H 桥引脚
const unsigned char pinMotorCCW[2] = {5, 9};   // 接控制电机1逆时针转的 H 桥引脚
// 电机停转
void motorStop()
{
    digitalWrite(pinMotorCW[0], LOW);
    digitalWrite(pinMotorCCW[0], LOW);
    digitalWrite(pinMotorCW[1], LOW);
    digitalWrite(pinMotorCCW[1], LOW);
}

// 电机以参数设定的 pwm 值顺时针转
void motorCW(int pwm)
{
    analogWrite(pinMotorCW[0], pwm);
    digitalWrite(pinMotorCCW[0], LOW);
    analogWrite(pinMotorCW[1], pwm);
    digitalWrite(pinMotorCCW[1], LOW);
}

// 电机以参数设定的 pwm 值逆时针转
void motorCCW(int pwm)
{
    digitalWrite(pinMotorCW[0], LOW);
    analogWrite(pinMotorCCW[0], pwm);
    digitalWrite(pinMotorCW[1], LOW);
    analogWrite(pinMotorCCW[1], pwm);   
}
void moveForward(){
  digitalWrite(pinMotorCW[0], 1);
  digitalWrite(pinMotorCW[1], 1);
  digitalWrite(pinMotorCCW[0], 0);
  digitalWrite(pinMotorCCW[1], 0);
}
void moveBackward(){
  digitalWrite(pinMotorCW[0], 0);
  digitalWrite(pinMotorCW[1], 0);
  digitalWrite(pinMotorCCW[0], 1);
  digitalWrite(pinMotorCCW[1], 1);
}
void setup()  
{   
    Serial.begin(9600);  
    myservo.attach(3);
    irrecv.enableIRIn(); // 启动接收器  
    pinMode(pinMotorCW[0],  OUTPUT);
    pinMode(pinMotorCCW[0], OUTPUT);
    pinMode(pinMotorCW[1],  OUTPUT);
    pinMode(pinMotorCCW[1], OUTPUT);
}   
int _speed = 0; 
int pos = 124;          // 变量pos用来存储舵机位置
void loop() {  
    if (irrecv.decode(&results))   
    {   
        Serial.println(results.value, HEX);//以16进制换行输出接收代码
        
        switch(results.value){
          case SPEEDUP: if(_speed <= 220) _speed += 20; break;
          case SPEEDDOWN: if(_speed >= -220) _speed -= 20; break;
          case LEFT: pos -= 20; break;
          case RIGHT: pos += 20; break;
          default: break;
        }
        myservo.write(pos);
        if(_speed > 0)
//          motorCW(_speed);
            moveForward();
        else if(_speed == 0)
            motorStop();
        else if(_speed < 0)
//          motorCCW(-_speed);
            moveBackward();
        
        Serial.println(_speed, DEC);
        Serial.println(pos, DEC);  
        irrecv.resume(); // 接收下一个值    
    }    
    delay(100);
}   
