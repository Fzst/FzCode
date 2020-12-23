int Echo1 = A5;  // Echo回声脚(P2.0)
int Trig1 = A4;  //  Trig 触发脚(P2.1)

int servopin=2;//设置舵机驱动脚到数字口2
int myangle;//定义角度变量
int pulsewidth;//定义脉宽变量
int val;

int Front_Distance = 0;//
int Left_Distance = 0;
int Right_Distance = 0;

int Left_motor_back=9;     //左电机后退(IN1)
int Left_motor_go=5;     //左电机前进(IN2)
int Right_motor_go=6;    // 右电机前进(IN3)
int Right_motor_back=10;    // 右电机后退(IN4)

int key=A0;//定义按键 A0 接口
int beep=A1;//定义蜂鸣器 A1 接口

const int SensorRight = A2;     //右循迹红外传感器(P3.2 OUT1)
const int SensorLeft = A3;      //左循迹红外传感器(P3.3 OUT2)

int SL;    //左循迹红外传感器状态
int SR;    //右循迹红外传感器状态

void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(Echo1, INPUT);    // 定义超声波输入脚
  pinMode(Trig1, OUTPUT);   // 定义超声波输出脚
  pinMode(Left_motor_go,OUTPUT); // PIN 5 (PWM)
  pinMode(Left_motor_back,OUTPUT); // PIN 9 (PWM)
  pinMode(Right_motor_go,OUTPUT);// PIN 6 (PWM) 
  pinMode(Right_motor_back,OUTPUT);// PIN 10 (PWM)
  pinMode(key,INPUT);//定义按键接口为输入接口
  pinMode(beep,OUTPUT);
  pinMode(SensorRight, INPUT); //定义右循迹红外传感器为输入
  pinMode(SensorLeft, INPUT); //定义左循迹红外传感器为输入
  pinMode(servopin,OUTPUT);//设定舵机接口为输出接口
}

//=======================智能小车的基本动作=========================
//void run(int time)     // 前进
void run()
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);     
  analogWrite(Right_motor_go,80);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Right_motor_back,0);
  digitalWrite(Left_motor_go,HIGH);  // 左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,72);//PWM比例0~255调速，左右轮差异略增减
  analogWrite(Left_motor_back,0);
  //delay(2020);   //执行时间，可以调整  
}

//void brake(int time)  //刹车，停车
void brake()
{
  digitalWrite(Right_motor_go,LOW);
  digitalWrite(Right_motor_back,LOW);
  digitalWrite(Left_motor_go,LOW);
  digitalWrite(Left_motor_back,LOW);
  //delay(time * 100);//执行时间，可以调整  
}

//void left(int time)         //左转(左轮不动，右轮前进)
void left()
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,90); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整  
}
void left_1(int time)
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,75); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}
void back(int time)  
{
  digitalWrite(Right_motor_go,LOW);  //右轮后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0);
  analogWrite(Right_motor_back,73);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);  //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0);
  analogWrite(Left_motor_back,64);//PWM比例0~255调速
  delay(time * 100);     //执行时间，可以调整  
}

void spin_left(int time)         //左转(左轮后退，右轮前进)
{
  digitalWrite(Right_motor_go,HIGH);  // 右电机前进
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,100); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,LOW);   //左轮后退
  digitalWrite(Left_motor_back,HIGH);
  analogWrite(Left_motor_go,0); 
  analogWrite(Left_motor_back,100);//PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}

//void right(int time)        //右转(右轮不动，左轮前进)
void right()
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,90); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  //delay(time * 100);  //执行时间，可以调整  
}

void right_1(int time)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,LOW);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,0);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,63); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整  
}
void spin_right(int time)        //右转(右轮后退，左轮前进)
{
  digitalWrite(Right_motor_go,LOW);   //右电机后退
  digitalWrite(Right_motor_back,HIGH);
  analogWrite(Right_motor_go,0); 
  analogWrite(Right_motor_back,100);//PWM比例0~255调速
  digitalWrite(Left_motor_go,HIGH);//左电机前进
  digitalWrite(Left_motor_back,LOW);
  analogWrite(Left_motor_go,100); 
  analogWrite(Left_motor_back,0);//PWM比例0~255调速
  delay(time * 100);  //执行时间，可以调整    
}

//void back(int time)          //后退

//==========================================================

void keysacn()//按键扫描
{
  int val;
  val=digitalRead(key);//读取数字7 口电平值赋给val
  while(!digitalRead(key))//当按键没被按下时，一直循环
  {
    val=digitalRead(key);//此句可省略，可让循环跑空
  }
  while(digitalRead(key))//当按键被按下时
  {
    delay(10);  //延时10ms
    val=digitalRead(key);//读取数字7 口电平值赋给val
    if(val==HIGH)  //第二次判断按键是否被按下
    {
      digitalWrite(beep,HIGH);    //蜂鸣器响
      while(!digitalRead(key))  //判断按键是否被松开
        digitalWrite(beep,LOW);   //蜂鸣器停止
    }
    else
      digitalWrite(beep,LOW);//蜂鸣器停止
  }
}
float Distance_test()   // 量出前方距离 
{
  digitalWrite(Trig1, LOW);   // 给触发脚低电平2μs
  delayMicroseconds(2);
  digitalWrite(Trig1, HIGH);  // 给触发脚高电平10μs，这里至少是10μs
  delayMicroseconds(10);
  digitalWrite(Trig1, LOW);    // 持续给触发脚低电
  float Fdistance = pulseIn(Echo1, HIGH);  // 读取高电平时间(单位：微秒)
  Fdistance= Fdistance/58;       //为什么除以58等于厘米，  Y米=（X秒*344）/2
  // X秒=（ 2*Y米）/344 ==》X秒=0.0058*Y米 ==》厘米=微秒/58
  //Serial.print("Distance:");      //输出距离（单位：厘米）
  //Serial.println(Fdistance);         //显示距离
  //Distance = Fdistance;
  return Fdistance;
}  

void servopulse(int servopin,int myangle)/*定义一个脉冲函数，用来模拟方式产生PWM值*/
{
  pulsewidth=(myangle*11)+500;//将角度转化为500-2480 的脉宽值
  digitalWrite(servopin,HIGH);//将舵机接口电平置高
  delayMicroseconds(pulsewidth);//延时脉宽值的微秒数
  digitalWrite(servopin,LOW);//将舵机接口电平置低
  delay(20-pulsewidth/1000);//延时周期内剩余时间
}

void front_detection()
{
  //此处循环次数减少，为了增加小车遇到障碍物的反应速度
  for(int i=0;i<=5;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,90);//模拟产生PWM
  }
  Front_Distance = Distance_test();
  //Serial.print("Front_Distance:");      //输出距离（单位：厘米）
 // Serial.println(Front_Distance);         //显示距离
 //Distance_display(Front_Distance);
}
void left_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,175);//模拟产生PWM
  }
  Left_Distance = Distance_test();
  //Serial.print("Left_Distance:");      //输出距离（单位：厘米）
  //Serial.println(Left_Distance);         //显示距离
}

void right_detection()
{
  for(int i=0;i<=15;i++) //产生PWM个数，等效延时以保证能转到响应角度
  {
    servopulse(servopin,5);//模拟产生PWM
  }
  Right_Distance = Distance_test();
  //Serial.print("Right_Distance:");      //输出距离（单位：厘米）
  //Serial.println(Right_Distance);         //显示距离
}
void tracking()
{ 
  while(1)
  {
  //有信号为LOW  没有信号为HIGH
  SR = digitalRead(SensorRight);//有信号表明在白色区域，车子底板上L3亮；没信号表明压在黑线上，车子底板上L3灭
  SL = digitalRead(SensorLeft);//有信号表明在白色区域，车子底板上L2亮；没信号表明压在黑线上，车子底板上L2灭

  if (SL == LOW&&SR==LOW){
    run(); //调用前进函数
    }
  else if (SL == HIGH && SR == LOW){// 左循迹红外传感器,检测到信号，车子向右偏离轨道，向左转 
    left();
    break;}
  else if (SR == HIGH && SL == LOW) {// 右循迹红外传感器,检测到信号，车子向左偏离轨道，向右转  
    right();
    break;}
  else if (SL == HIGH && SR == HIGH)
    break;
 }
}

void loop(){
    keysacn();  //调用按键扫描函数  
    while(1)
  {
    front_detection();//测量前方距离
    if(Front_Distance < 11)//当遇到障碍物时
    {
      back(2);//后退减速
      brake();//停下来做测距
      left_detection();//测量左边距障碍物距离

      right_detection();//测量右边距障碍物距离

      if((Left_Distance < 12 ) &&( Right_Distance < 12 ))//当左右两侧均有障碍物靠得比较近
        spin_left(20);//旋转掉头
      else if(Left_Distance > Right_Distance)//左边比右边空旷
      {      
        spin_left(5);//左转
        brake();//刹车，稳定方向
      }
      else if(Left_Distance < Right_Distance)//右边比左边空旷
      {
        spin_right(5);//右转
        brake();//刹车，稳定方向
      }
      else {
        spin_right(5);
        brake();
      }
    }
    else
    {
      tracking(); //无障碍物，直行     
    }
  } 
}
