// WiFiManager.cpp

#include "WiFiManager.h"
#include <vector>

bool isAPMode = false;
std::vector<String> wifiList;

/*******************试图链接wifi,并返回true_false*************************/

bool connectToWiFi(const char *ssid, const char *password) {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("连接到WiFi失败，重试中...");
    delay(1000);
    attempts++;
    if (attempts > 20) {
      Serial.println("连接到WiFi超时，回滚到AP模式");
      return false;
      // 连接失败，返回false
    }
  }
  Serial.println("已连接到WiFi");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());
  return true;
  // 连接成功，返回true
}

/*******************切换到客户端模式，无返回*************************/

void switchToStationMode() {
  WiFi.softAPdisconnect(true);
  // 关闭AP模式
  WiFi.mode(WIFI_STA);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("连接到WiFi失败，重试中...");
    delay(1000);
  }
  Serial.println("已连接到WiFi");
  Serial.print("IP 地址: ");
  Serial.println(WiFi.localIP());
}

/********************切换回AP模式，并扫描WIFI*************************/
void startAPMode() {
  const char *apSsid = "ESP32-AP";
  const char *apPassword = "password";
  WiFi.mode(WIFI_AP);
  WiFi.softAP(apSsid, apPassword);
  Serial.println("AP Mode started");
  Serial.print("AP SSID: ");
  Serial.println(apSsid);
  Serial.print("AP Password: ");
  Serial.println(apPassword);
  // 设置扫描到的WiFi列表
  isAPMode = true;
  setupWiFiList();
}



/*******************扫描附近的wifi*************************/
void setupWiFiList() {
  Serial.println("Scanning WiFi networks...");
  int networks = WiFi.scanNetworks();
  if (networks == 0) {
    Serial.println("No WiFi networks found");
  } else {
    Serial.println("WiFi networks found:");
    for (int i = 0; i < networks; ++i) {
      Serial.println(WiFi.SSID(i));
      
      wifiList.push_back(WiFi.SSID(i)); // 将扫描到的SSID添加到全局变量中
    }
  }
}
