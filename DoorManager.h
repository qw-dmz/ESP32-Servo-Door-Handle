// DoorManager.h

#ifndef DOOR_MANAGER_H
#define DOOR_MANAGER_H
#include <Arduino.h>

extern bool doorNeedOpen;
extern uint32_t doorOpenTime;

void door();
void timeopendoor();

#endif  // DOOR_MANAGER_H
