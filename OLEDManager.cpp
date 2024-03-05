// OLEDManager.cpp

#include "OLEDManager.h"

U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, U8X8_PIN_NONE);
char ssid[] = "biying";  // 要接入的WIFI名

void initOLED() {
  u8g2.begin();
  u8g2.enableUTF8Print();
  u8g2.clearBuffer();
}

void displayInitialization() {
  u8g2.clearBuffer();
  u8g2.setFont(u8g2_font_ncenB08_tr);

  // 添加显示初始化信息的逻辑
  displayChineseText(25, 24, str32); //系
  displayChineseText(41, 24, str33); //统
  displayChineseText(57, 24, str34); //初
  displayChineseText(73, 24, str35); //始
  displayChineseText(89, 24, str36); //化

  u8g2.sendBuffer();
}


// 设置 OLED 显示的中文文本
void displayChineseText(int x, int y, const unsigned char *str) {
  u8g2.drawXBMP(x, y, 16, 16, str);
}


/****************OLED显示***************/
void oleddisplay(){
      IPAddress APIP = WiFi.softAPIP();
      IPAddress IP = WiFi.localIP();
      IPAddress NAME = WiFi.localIP();
      
      u8g2.clearBuffer();//清屏
      u8g2.setFont(u8g2_font_ncenB08_tr);//字体08
      
      //电池电量显示
      u8g2.setCursor(0, 64);//设置显示位置
      u8g2.print(batPercent());//输出字符
      u8g2.setCursor(30, 64);//设置显示位置
      u8g2.print("%");//输出字符

      //电池电压显示
      u8g2.setCursor(40, 64);//设置显示位置
      u8g2.print(batVol());//输出字符
      u8g2.setCursor(65, 64);//设置显示位置
      u8g2.print("V");//输出字符


      u8g2.setCursor(80, 64);//设置显示位置
      u8g2.print("--:--:--");//输出字符
      
      
      u8g2.setCursor(20, 8);//设置显示位置
      u8g2.print("WiFi connect:");//输出字符
      if(WiFi.status()!=WL_CONNECTED){//如果wifi没连接
        u8g2.drawXBMP(0, 0, 16, 16, str23); //wifi连接失败图标
        u8g2.setCursor(20, 17);//设置显示位置
        u8g2.print("fail");//输出字符
      }
      else{//如果wifi有连接
        u8g2.drawXBMP(0, 0, 16, 16, str22); //wifi连接成功图标
        u8g2.setCursor(20, 17);//设置显示位置
        u8g2.print(ssid);//输出字符
      }
      
      u8g2.drawXBMP(0, 17, 16, 16, str24); //网络连接图标
      
      u8g2.setCursor(20, 26);//设置显示位置
      u8g2.print("WiFi IP Address:");//输出字符
      u8g2.setCursor(20, 35);//设置显示位置
      u8g2.print(IP);//输出wifi的IP
      u8g2.drawXBMP(0, 36, 16, 16, str26); //AP图标
      u8g2.setCursor(20, 44);//设置显示位置
      u8g2.print("AP IP Address:");//输出AP的IP
      u8g2.setCursor(20, 53);//设置显示位置
      u8g2.print(APIP);//输出字符
      
      u8g2.sendBuffer();//开显示
}

/***********电池电量测量，充电状态，门状态，门外是否有人状态**********/
float batVol(){
  float bat_voltage;//电池电压定义
  Serial.print("电池电压是:  ");
  Serial.print(analogRead(voltagePin));
  Serial.print("  ");
  bat_voltage = ((analogRead(voltagePin)*4.2)/40000);//(当前adc*满电电压4.2)/满电adc
  return bat_voltage; 
}

int batPercent(){
  int bat_value;//电池电量定义
  bat_value = (((analogRead(voltagePin)-31500)*100)/8500);//((当前adc-没电adc)*100)/满电减没电的adc差
  if(bat_value>100){
    bat_value = 100;
  }
  else if(bat_value<0){
    bat_value = 0;
  }
  Serial.print(bat_value);
  Serial.println(" %");
  Serial.print("  ");
  return bat_value; 
}
