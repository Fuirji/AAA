#include <Servo.h>

const int TrigPin = 4; //超声波trig引脚 D4
const int EchoPin = 3; //超声波echo引脚 D3
float cm=0.0; //障碍距离
float warringLine=20.0;//距离cm

const int ledPin = 6 ;//灯led引脚 D6

Servo myservo;  // 定义Servo对象来控制
Servo drive;
int pos = 0;    // 角度存储变量

int playPin = 7; // 语音模块p-l和p-e短接，接到 D7

int state = 0;   //初始状态

void setup() {
  myservo.attach(9);  // 控制线连接 D9
  drive.attach(10);  // 控制线连接 D10
  pinMode(playPin,OUTPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {

  while(1)
  {
       digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去TrigPin 
       delay(2); 
       digitalWrite(TrigPin, HIGH); 
       delay(10); 
       digitalWrite(TrigPin, LOW);
       cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成cm
       cm = (int(cm * 100)) / 100; //保留两位小数 

       if( cm < warringLine && state == 0 )
        {   
          int power1=255;
          int power2=0;
          digitalWrite(playPin, HIGH); 
          for (pos = 0; pos <= 180; pos ++) // 0°到180°
            { 
             // in steps of 1 degree             
              myservo.write(pos);              // 舵机角度写入
              drive.write(180-pos);
              if(pos>=105)  { analogWrite(ledPin,power1);power1-=2;}
              else{ analogWrite(ledPin,power1);power1-=1;}
             delay(16);                       // 等待转动到指定角度
            }
            delay(60);
            for (pos = 180; pos >= 0; pos --)  // 从180°到0°
            { 
              myservo.write(pos);              // 舵机角度写入
              drive.write(180-pos);
              if(pos>=75){ analogWrite(ledPin,power2);power2+=1;}
              else {analogWrite(ledPin,power2);power2+=2;}
              delay(17);                       // 等待转动到指定角度
            }
           digitalWrite(playPin, LOW);
           state = 1;
           delay(10);
        }
       else if ( cm > warringLine && state == 1 )
       {
         state = 0;
         delay(10);
       } 
  }
}
