// PinConfig.h
#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

#include <Arduino.h>
extern const int doorServoSignal;

// 定义引脚配置

const int voltagePin = 34;         // 电压测量引脚
const int lowBatteryLED = 25;      // 低电量指示灯引脚
const int wifiLED = 26;            // WIFI指示灯引脚
const int networkLED = 27;         // 网络指示灯引脚
const int chargingPin = 13;        // 充电检测引脚
const int doorRelay = 5;           // 门继电器引脚
const int relayPin = 5;           // 门继电器引脚
// Function declarations
void initPins();

#endif // PIN_CONFIG_H
