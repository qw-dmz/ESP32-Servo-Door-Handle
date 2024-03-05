// MotorControl.h

#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

#include <Arduino.h>
#include <Preferences.h>
#include <ESP32Servo.h>

extern Servo myservo;
extern const int servoPin;

void moveServo(int targetAngle);
void stopSteering();
void startForward();
void startBackward();

#endif  // MOTOR_CONTROL_H
