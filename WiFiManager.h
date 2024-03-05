// WiFiManager.h

#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

bool connectToWiFi(const char *ssid, const char *password);
void switchToStationMode();
void startAPMode();
void setupWiFiList();

#endif  // WIFI_MANAGER_H
