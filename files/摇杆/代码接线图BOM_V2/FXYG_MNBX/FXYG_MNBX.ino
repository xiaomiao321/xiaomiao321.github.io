#include <Wire.h>
#include <PCF8575.h>
#include "ADS1X15.h"
#include <Joystick.h>
//40按键+2轴10bit+2轴16bir+2轴模拟八向摇杆
Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,0x04,
  40, 0,                  // Button Count, Hat Switch Count
  true, true, true,     // X and Y, but no Z Axis
  true, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering
PCF8575 PCF_20(0x20);
PCF8575 PCF_21(0x21);
ADS1115 ADS(0x48);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  Wire.begin();
  Wire.setClock(400000);
  PCF_20.begin();
  PCF_21.begin();

  ADS.begin();
  ADS.setDataRate(7);
  ADS.setMode(1);
  ADS.setGain(0);
  

  Joystick.begin();
  Joystick.setXAxisRange(0, 23800);
  Joystick.setYAxisRange(0, 23800);
  Joystick.setZAxisRange(0, 1024);
  Joystick.setRxAxisRange(0, 1024);
}
uint16_t val1 = 0;
uint16_t val2 = 0;
int16_t adc0, adc1;
bool digital_V1=0;
uint8_t clock = 0;
int analogA0,analogA1,analogA2,analogA3;
void loop() {
  //long lasttime = millis();


  // put your main code here, to run repeatedly:
  val1 = PCF_20.read16();
  val2 = PCF_21.read16();
  
  adc0 = ADS.readADC(0); 
  Joystick.setXAxis(adc0);
  adc1 = ADS.readADC(1); 
  Joystick.setYAxis(adc1);


  clock++;
  if(clock==1){
    for(int i=0;i<8;i++){
      bool num = !(bitRead(val1, i));
      Joystick.setButton(i,num);
      }
  }
  if(clock==2){
    for(int i=0;i<8;i++){
      bool num = !(bitRead(val1, i+8));
      Joystick.setButton(i+8,num);
      }
  }
  if(clock==3){
    for(int i=0;i<8;i++){
      bool num = !(bitRead(val2, i));
      Joystick.setButton(i+16,num);
      }
  }
  if(clock==4){
    for(int i=0;i<8;i++){
      bool num = !(bitRead(val2, i));
      Joystick.setButton(i+24,num);
      }
  }
  if(clock==5){
    clock=0;
    analogA0 = analogRead(A0);
    analogA1 = analogRead(A1);
    if(analogA0<=200){Joystick.setButton(32,1);}else{Joystick.setButton(32,0);}
    if(analogA1<=200){Joystick.setButton(33,1);}else{Joystick.setButton(33,0);}
    if(analogA0>=800){Joystick.setButton(34,1);}else{Joystick.setButton(34,0);}
    if(analogA1>=800){Joystick.setButton(35,1);}else{Joystick.setButton(35,0);}
    if(analogA0<=200&&analogA1<=200){Joystick.setButton(36,1);}else{Joystick.setButton(36,0);}
    if(analogA0>=800&&analogA1>=800){Joystick.setButton(37,1);}else{Joystick.setButton(37,0);}
    if(analogA0>=800&&analogA1<=200){Joystick.setButton(38,1);}else{Joystick.setButton(38,0);}
    if(analogA0<=200&&analogA1>=800){Joystick.setButton(39,1);}else{Joystick.setButton(39,0);}
    analogA2 = analogRead(A2);
    analogA3 = analogRead(A3);
    Joystick.setZAxis(analogA2);
    Joystick.setRxAxis(analogA3);
  }
  
  
  
/*
  Serial.print(" pcf8575a20:");
  Serial.print(val1,BIN);
  Serial.print(" pcf8575a21:");
  Serial.print(val2,BIN);
  Serial.print(" adc_A0:"); Serial.print(adc0);
  Serial.print(" adc_A1:"); Serial.print(adc1);
  Serial.print(" analogA0:"); Serial.print(analogA0);
  Serial.print(" analogA1:"); Serial.print(analogA1);
  Serial.print(" analogA2:"); Serial.print(analogA2);
  Serial.print(" analogA3:"); Serial.println(analogA3);
*/

}
