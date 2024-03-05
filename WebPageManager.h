// WebPageManager.h

#ifndef WEB_PAGE_MANAGER_H
#define WEB_PAGE_MANAGER_H

#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebSrv.h>
#include <Preferences.h>

void setupWebConfig(bool isApMode);
String getWebPage();
String getControlPage();
extern std::vector<String> wifiList;

#endif  // WEB_PAGE_MANAGER_H
