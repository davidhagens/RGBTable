#pragma once
#include "Serial.h"
#include <functional>

//easy controller acces, so you don't need to write Controller::Instance() everytime
#define _Controller Controller::Instance()

class Controller
{
private:
  //singleton pointer
  static Controller* __instance;
public:
  static Controller* Instance();
  static void Destroy();

private:
  Serial* conSerial;
  uint8_t con0;
  uint8_t con1;

private:
  //since this is a singleton we don't want to reach the constructor / destructor from outside
  Controller();
  ~Controller();
public:
  const uint8_t GetCon0();
  const uint8_t GetCon1();

  //update the controller data from the Arduino (Warning: this will block until it get's an answer from the Arduino)
  void Update();
};