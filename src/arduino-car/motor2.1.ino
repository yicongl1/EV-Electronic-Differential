
#include <IRremote.h>  //红外遥控头文件
#include <Servo.h>     //伺服头文件
 
//-------------------------------------------------------------------//
//*******************************************************************//
///
//红外遥控/
///
const int irReceiverPin = 3;  // 红外接收器的 OUTPUT 引脚接在 PIN11
IRrecv irrecv(irReceiverPin); // 设置irReceiverPin定义的端口为红外信号接收端口
decode_results results;       // 定义results变量为红外结果存放位置
void loop(void);

//-------------------------------------------------------------------//
//*******************************************************************//
///
//电机设置/
///
#define leftA_PIN 5
#define leftB_PIN 6
#define righA_PIN 9
#define righB_PIN 10
void motor_pinint( );     //引脚初始化
void forward( );          //前进
void back( );             //后退
void turnleft();          //左转
void turnright();         //右转
void _stop();             //停车
 
//-------------------------------------------------------------------//
//*******************************************************************//
///
//舵机设置/
///
Servo myservo;
int pos = 90;     // variable to store the servo position

//-------------------------------------------------------------------------//
 
void setup()
{
  Serial.begin(9600);    //波特率9600
  irrecv.enableIRIn();   //红外接收器初始化
  motor_pinint();        //电机引脚初始化自定义函数
  myservo.attach(11); 
  myservo.write(pos);    //舵机位置初始化
 
}
 
/*电机引脚初始化*/
void motor_pinint( )
{
  pinMode (leftA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (leftB_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (righA_PIN, OUTPUT); //设置引脚为输出引脚
  pinMode (righB_PIN, OUTPUT); //设置引脚为输出引脚
}
/**************************************************
forward子函数——前进子函数
函数功能：控制车前进
**************************************************/
void forward( )
{
  analogWrite(leftA_PIN,180);    
  analogWrite(leftB_PIN,0);         //左轮前进
  analogWrite(righA_PIN,180);    
  analogWrite(righB_PIN,0);         //右轮前进
  pos=90;
  myservo.write(pos);
}
/**************************************************
back子函数——后退子函数
函数功能：控制车后退
**************************************************/
void back( )
{
  analogWrite(leftA_PIN,0);    
  analogWrite(leftB_PIN,180);        //左轮后退
  analogWrite(righA_PIN,0);    
  analogWrite(righB_PIN,180);        //右轮后退
  pos=90;
  myservo.write(pos);
}
/**************************************************
turnleft子函数——左转子函数
函数功能：控制车左转
**************************************************/
void turnleft( )
{
  analogWrite(leftA_PIN,120);    
  analogWrite(leftB_PIN,0);         //左轮前进
  analogWrite(righA_PIN,180);    
  analogWrite(righB_PIN,0);         //右轮前进
  pos=45;
  myservo.write(pos);
}
/**************************************************
turnright子函数——右转子函数
函数功能：控制车右转
**************************************************/
void turnright( )
{
  analogWrite(leftA_PIN,180);    
  analogWrite(leftB_PIN,0);         //左轮前进
  analogWrite(righA_PIN,120);    
  analogWrite(righB_PIN,0);         //右轮前进
  pos=135;
  myservo.write(pos);
}
/**************************************************
stop子函数—停止子函数
函数功能：控制车停止
**************************************************/
void _stop()
{
  analogWrite(leftA_PIN,0);    
  analogWrite(leftB_PIN,0);         //左轮静止不动
  analogWrite(righA_PIN,0);    
  analogWrite(righB_PIN,0);          //右轮静止不动
}
 
void loop(void) 
{
  if(irrecv.decode(&results)) {      // 解码成功，把数据放入results.value变量中
    Serial.println(results.value,DEC);//打印接收到的内容
    Serial.println();
    
    //↑前进
    if((results.value==16718055))
      {forward( );delay(500);_stop();}
    //↓后退
    else if((results.value==16730805))
      {back( );delay(500);_stop();}
    //←左转
    else if((results.value==16716015))
      {turnleft( );delay(500);_stop();}
    //→右转
    else if((results.value==16734885))
      {turnright( );delay(500);_stop();}
    irrecv.resume();                  //等待接收下一组信号
  }
  if(results.value==0x16)
    delay(600);                       //延时600毫秒,消抖
}
