#pragma once
#include "Serial.h"
#include <thread>
#include <mutex>
#include "RenderImage.h"
#undef RGB



//easy acces to LEDMatrix, so you don't have to write LEDMatrix::Instance() every time
#define _LEDMatrix LEDMatrix::Instance()

class LEDMatrix : public RenderImage
{
private:
  //static functions which will run in an external thread
  static void ShowS0(LEDMatrix* _this);
  static void ShowS1(LEDMatrix* _this);
  //singleton pointer
  static LEDMatrix* __instance;
public:
  static LEDMatrix* Instance();
  static void Destroy();

private:
  std::thread t0, t1;
  bool update0, update1, quit; //thread handling

  Serial* ser0, *ser1; //serial connection for both arduinos

private:
  //since this is a singleton we don't want to reach the constructor / destructor from outside
  LEDMatrix();
  ~LEDMatrix();
public:
  
  //send the color buffer to the Arduinos
  void Show();
};