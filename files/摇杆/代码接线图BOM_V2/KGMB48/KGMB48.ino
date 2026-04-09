#include <Wire.h>
#include <PCF8575.h>
#include <Joystick.h>
//6轴10bit A0A1软件滤波 32按键 
Joystick_ Joystick(0x02,0x05,
  48, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  true, true, true,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
PCF8575 PCF_20(0x20);
PCF8575 PCF_21(0x21);
PCF8575 PCF_22(0x22);
const int stabilityThreshold = 3;     // 稳定阈值（差值<3不更新）

const int A0_Sample_num = 5;          // 滑动窗口大小
int A0_samples[A0_Sample_num] = {0};  // 初始化全0的缓冲区
int A0_writeIndex = 0;                // 写指针
int A0_sum = 0;                       // 当前窗口总和
int A0_last_stable_value = 0;         // 上次稳定值

const int A1_Sample_num = 5;          // 滑动窗口大小
int A1_samples[A1_Sample_num] = {0};  // 初始化全0的缓冲区
int A1_writeIndex = 0;                // 写指针
int A1_sum = 0;                       // 当前窗口总和
int A1_last_stable_value = 0;         // 上次稳定值


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Wire.begin();

  PCF_20.begin();
  PCF_21.begin();
  PCF_22.begin();

  Joystick.begin();
  Joystick.setXAxisRange(0, 1024);
  Joystick.setYAxisRange(0, 1024);
  Joystick.setZAxisRange(0, 1024);
  Joystick.setRxAxisRange(0, 1024);
  Joystick.setRyAxisRange(0, 1024);
  Joystick.setRzAxisRange(0, 1024);
}
uint16_t val1 = 0;
uint16_t val2 = 0;
uint16_t val3 = 0;

uint8_t clock = 0;

int analogA0,analogA1,analogA2,analogA3,analogA6,analogA7;

void loop() {
  long lasttime = millis();
  clock++;

  // put your main code here, to run repeatedly:
  val1 = PCF_20.read16();
  val2 = PCF_21.read16();
  val3 = PCF_22.read16();
  if(clock==1){
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val1, i));
    Joystick.setButton(i,num);
    }
    analogA2 = analogRead(A2);
    Joystick.setRxAxis(analogA2);
  }
  if(clock==2){
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val1, i+8));
    Joystick.setButton(i+8,num);
    }
    analogA3 = analogRead(A3);
    Joystick.setRyAxis(analogA3);
  }
  if(clock==3){
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val2, i));
    Joystick.setButton(i+16,num);
    }
    analogA6 = analogRead(A6);
    Joystick.setZAxis(analogA6);
  }
  if(clock==4){
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val2, i+8));
    Joystick.setButton(i+24,num);
    }
    analogA7 = analogRead(A7);
    Joystick.setRzAxis(analogA7);
  }
  if(clock==5){
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val3, i));
    Joystick.setButton(i+32,num);
    }
  }
  if(clock==6){
    clock=0;
    for(int i=0;i<8;i++){
    bool num = !(bitRead(val3, i+8));
    Joystick.setButton(i+40,num);
    }
  }
  

  //analogA0 = analogRead(A0);
  //analogA1 = analogRead(A1);
  
  int A0_newValue = analogRead(A0);
  A0_sum = A0_sum - A0_samples[A0_writeIndex] + A0_newValue; // 移除旧值，加入新值
  A0_samples[A0_writeIndex] = A0_newValue;                   // 更新缓冲区
  A0_writeIndex = (A0_writeIndex + 1) % A0_Sample_num;    // 循环移动指针
  int A0_analog_average = A0_sum / A0_Sample_num;  //平均值输出
  if (abs(A0_analog_average - A0_last_stable_value) >= stabilityThreshold) {
    A0_last_stable_value = A0_analog_average;  // 超过阈值则更新
  }

  int A1_newValue = analogRead(A1);
  A1_sum = A1_sum - A1_samples[A1_writeIndex] + A1_newValue; // 移除旧值，加入新值
  A1_samples[A1_writeIndex] = A1_newValue;                   // 更新缓冲区
  A1_writeIndex = (A1_writeIndex + 1) % A1_Sample_num;    // 循环移动指针
  int A1_analog_average = A1_sum / A1_Sample_num;  //平均值输出
  if (abs(A1_analog_average - A1_last_stable_value) >= stabilityThreshold) {
    A1_last_stable_value = A1_analog_average;  // 超过阈值则更新
  }
  
  
  Joystick.setXAxis(A0_last_stable_value);
  Joystick.setYAxis(A1_last_stable_value);
  
  
  /*
  Serial.print(" pcf8575a20:");
  Serial.print(val1,BIN);
  Serial.print(" pcf8575a21:");
  Serial.print(val2,BIN);
  Serial.print(" pcf8575a22:");
  Serial.print(val3,BIN);
  Serial.print(" A0:"); Serial.print(A0_last_stable_value);
  Serial.print(" A1:"); Serial.print(A1_last_stable_value);
  Serial.print(" A2:"); Serial.print(analogA2);
  Serial.print(" A3:"); Serial.print(analogA3);
  Serial.print(" A6:"); Serial.print(analogA6);
  Serial.print(" A7:"); Serial.print(analogA7);
  Serial.print(" delay:");Serial.println(millis()-lasttime);
*/

}
