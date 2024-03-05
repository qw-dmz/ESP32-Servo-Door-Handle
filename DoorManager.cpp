// DoorManager.cpp

#include "DoorManager.h"
#include "MotorControl.h"
/********************拉门动作*************************/
void door() {
  if(!doorNeedOpen){
    doorNeedOpen = true;
    const int relayPin = 5; //继电器针脚
    digitalWrite(relayPin, LOW);//打开继电器
    startForward();// 拉门，正转
    doorOpenTime = 0; //重新计时
  }
}
/**********************计时开门****************************/
void timeopendoor(){
  if(doorNeedOpen){
    if(doorOpenTime >= 7){//超过1.5秒
      stopSteering();// 停止舵机
      doorNeedOpen = false;
    }
  }else{
    if(doorOpenTime >= 17){// 6秒后断电恢复关门
      doorOpenTime = 0;
      const int relayPin = 5; //继电器针脚
      digitalWrite(relayPin, HIGH);//断开继电器
    }
    if(doorOpenTime >= 14){//超过3秒
      startBackward();// 反转门
    }
  }
}