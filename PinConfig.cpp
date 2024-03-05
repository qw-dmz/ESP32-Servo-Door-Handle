#include "PinConfig.h"  

// 初始化引脚
void initPins() {
  pinMode(voltagePin, INPUT);      // 电压测量
  pinMode(lowBatteryLED, OUTPUT);  // 低电量指示灯
  pinMode(wifiLED, OUTPUT);        // WIFI 指示灯
  pinMode(networkLED, OUTPUT);     // 网络指示灯
  pinMode(chargingPin, OUTPUT);    // 充电检测
  pinMode(doorRelay, OUTPUT);      // 门继电器
  pinMode(doorServoSignal, OUTPUT); // 门舵机信号
  digitalWrite(chargingPin, HIGH); // 启用充电
  digitalWrite(relayPin, HIGH);//断开继电器
}