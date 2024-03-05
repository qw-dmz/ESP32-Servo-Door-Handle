// OLEDManager.h

#ifndef OLED_MANAGER_H
#define OLED_MANAGER_H

#include <Preferences.h>
#ifdef ESP32
#include <WiFi.h>
#include <AsyncTCP.h>
#elif defined(ESP8266)
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#endif
#include <U8g2lib.h>
#include "OLEDChineseFonts.h"

extern U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2;
extern const int voltagePin;

extern char ssid[16];  // 要接入的WIFI名

void oleddisplay();
float batVol();
int batPercent();
void initOLED();
void displayInitialization();
void displayChineseText(int x, int y, const unsigned char *str);

#endif  // OLED_MANAGER_H
