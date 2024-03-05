#include <Arduino.h>
#include <esp_task_wdt.h>
#include "MotorControl.h"
#include <esp32-hal-timer.h>
#include "WiFiManager.h"
#include "WebPageManager.h"
#include "DoorManager.h"
#include "OLEDManager.h"
#include "OLEDChineseFonts.h"
#include "PinConfig.h"

const int doorServoSignal = 23;    // 门舵机信号引脚

Servo myservo;

const int servoPin = 23;  // 舵机连接的引脚
bool doorNeedOpen = false;
uint32_t doorOpenTime = 0;

unsigned long previousMillis = 0;
const long interval = 500;  // 间隔时间，单位毫秒

/*************初始化*****************/
void setup() {
  // 初始化OLED显示
  initOLED();
  // 初始化引脚
  initPins();
  // 显示初始化信息
  displayInitialization();
  
  // 初始化Preferences库
  Preferences preferences;
  preferences.begin("config", false);
  // 初始化功能
  initFunctionality(preferences);
}

void loop() {
  // 获取当前时间
  unsigned long currentMillis = millis();

  // 判断是否达到延迟时间
  if (currentMillis - previousMillis >= interval) {
    // 保存当前时间
    previousMillis = currentMillis;

    // 处理舵机状态
    if (doorNeedOpen) {
      doorOpenTime++;
    } else {
      if (doorOpenTime >= 4) {
        doorOpenTime++;
      }
    }
    // 处理每秒的任务
    handleSecond();
  }
}

void handleSecond() {
  // OLED显示
  oleddisplay();
  // 处理门的开启时间
  timeopendoor();
}



// 初始化其他功能
void initFunctionality(Preferences &preferences) {
  bool isApMode = false;
  // 设置 aliogRead 返回值的分辨率
  analogReadResolution(16);

  // 将 Servo 附加到引脚并设置周期
  myservo.setPeriodHertz(50);
  myservo.attach(doorServoSignal, 1000, 2000);

  // 启动串行通信
  Serial.begin(115200);

  // 尝试从 Preferences 中读取 WiFi 配置
  String savedSSID = preferences.getString("ssid", "");
  String savedPassword = preferences.getString("password", "");
  preferences.end();

  // 检查是否有 WiFi 凭据
  if (savedSSID.length() > 0 && savedPassword.length() > 0) {
    // 使用保存的凭据连接 WiFi
    if (!connectToWiFi(savedSSID.c_str(), savedPassword.c_str())) {
      // 如果连接失败，启动 AP 模式
      startAPMode();
      isApMode = true;
    }
  } else {
    // 如果没有凭据，启动 AP 模式
    startAPMode();
    isApMode = true;
  }

  // 设置和启动 Web 服务器
  setupWebConfig(isApMode);
}
