// MotorControl.cpp

#include "MotorControl.h"

void moveServo(int targetAngle) {
  int targetPulseWidth = map(targetAngle, 0, 360, 1000, 2000);
  myservo.writeMicroseconds(targetPulseWidth);
}

void stopSteering() {
  moveServo(180);  // 停转
}

void startForward() {
  moveServo(0);  // 正转
}

void startBackward() {
  moveServo(360);  // 反转
}
