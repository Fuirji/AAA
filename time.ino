//使用arduino IDE自带的Stepper.h库文件
#include <Stepper.h>

// 这里设置步进电机旋转一圈是多少步
#define STEPS 100

//设置步进电机的步数和引脚（就是注意点2里面说的驱动板上IN1～IN4连接的四个数字口）。
Stepper stepper(STEPS, 8, 9, 10, 11);

const int ledpin = 5; //红外模块out脚接数字5，VCC、GND对应接
int flag=1;
int count_h=0;
int count_l=0;
void setup()
{  
  pinMode(ledpin, INPUT);     
  stepper.setSpeed(90);   // 设置电机的转速：每分钟为90步
  Serial.begin(9600);     // 初始化串口，用于调试输出信息 
}
 
void loop()
{
  int value = digitalRead(ledpin); //定义传感器检测到的值为value
  Serial.println(value);
  if(value==HIGH && flag==1 && count_h==0)//如果它的值为高电平，即检测到有人通过3632
  {
     stepper.step(555); //4步模式下旋转一周用2048 步。
     count_h=count_l=1;
     flag=0;
     delay(500);
  }
  if (value==HIGH && count_h>0)
  {
     count_h++;
  }
  if (value==LOW && count_l>0)
  {
     count_l++;
  } 
  if(value==LOW && flag==0 && ((count_h-count_l)>10||(count_l-count_h)>20))
  {
     stepper.step(-555); //4步模式下旋转一周用2048 步。
     delay(500);
     flag=1;
     count_h=count_l=0;
  }
}
