#define D_a 2  //数码管a 接引脚 2
#define D_b 3
#define D_c 4
#define D_d 5
#define D_e 6
#define D_f 7
#define D_g 8
#define D_h 9
 
//数码管0-F数字码值
unsigned char num[17][8] =
{
 //1为点亮，0为关闭，a表示数码管a的led灯，其他类似
 //a  b  c  d  e  f  g  h 
  {1, 1, 1, 1, 1, 1, 0, 0},     //0
  {0, 1, 1, 0, 0, 0, 0, 0},     //1
  {1, 1, 0, 1, 1, 0, 1, 0},     //2
  {1, 1, 1, 1, 0, 0, 1, 0},     //3
  {0, 1, 1, 0, 0, 1, 1, 0},     //4
  {1, 0, 1, 1, 0, 1, 1, 0},     //5
  {1, 0, 1, 1, 1, 1, 1, 0},     //6
  {1, 1, 1, 0, 0, 0, 0, 0},     //7
  {1, 1, 1, 1, 1, 1, 1, 0},     //8
  {1, 1, 1, 1, 0, 1, 1, 0},     //9
  {1, 1, 1, 0, 1, 1, 1, 1},     //A
  {1, 1, 1, 1, 1, 1, 1, 1},     //B
  {1, 0, 0, 1, 1, 1, 0, 1},     //C
  {1, 1, 1, 1, 1, 1, 0, 1},     //D
  {1, 0, 0, 1, 1, 1, 1, 1},     //E
  {1, 0, 0, 0, 1, 1, 1, 1},     //F
  {0, 0, 0, 0, 0, 0, 0, 1},     //.
};
 
void setup()
{
  pinMode(D_a,OUTPUT);        //设置引脚为输出
  pinMode(D_b,OUTPUT);        //设置引脚为输出
  pinMode(D_c,OUTPUT);        //设置引脚为输出
  pinMode(D_d,OUTPUT);        //设置引脚为输出
  pinMode(D_e,OUTPUT);        //设置引脚为输出
  pinMode(D_f,OUTPUT);        //设置引脚为输出
  pinMode(D_g,OUTPUT);        //设置引脚为输出
  pinMode(D_h,OUTPUT);        //设置引脚为输出
}
 
void loop()
{
  //按顺序显示0123456789ABCDEF.
    digitalWrite(D_a,1 - num[0][0]);  //设置a 引脚的电平
    digitalWrite(D_b,1 - num[0][1]);  //设置b 引脚的电平
    digitalWrite(D_c,1 - num[0][2]);  //设置c 引脚的电平
    digitalWrite(D_d,1 - num[0][3]);  //设置d 引脚的电平
    digitalWrite(D_e,1 - num[0][4]);  //设置e 引脚的电平
    digitalWrite(D_f,1 - num[0][5]);  //设置f 引脚的电平
    digitalWrite(D_g,1 - num[0][6]);  //设置g 引脚的电平
    digitalWrite(D_h,1 - num[0][7]);  //设置h 引脚的电平
}

