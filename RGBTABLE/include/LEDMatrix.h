#pragma once
#include "Serial.h"
#include "RGB.h"
#include "Bitmap.h"
#include "Math.hpp"
#include "Shape.h"
#include <thread>
#include <mutex>
#include "RenderImage.h"
#undef RGB

#define LED_W 36
#define LED_H 18
#define LED_COUNT LED_W * LED_H
#define LED_S0_COUNT LED_W * 10 //first 10 rows, the actual led matrix is powered by two Arduino UNO
#define LED_S1_COUNT LED_W * 8 //last 8 rows
#define LED_BYTES LED_COUNT * 3 //3 bytes per pixel (r,g,b) * 648 (LED_COUNT)
#define LED_S0_BYTES LED_S0_COUNT * 3 //bytes used for the first 10 rows
#define LED_S1_BYTES LED_S1_COUNT * 3 //bytes used for the last 8 rows
//override modes to set a bitmap or a color
#define OVERRIDE_MODE_ALL 0x00
#define OVERRIDE_MODE_BLACK_AS_ALPHA 0x01
#define OVERRIDE_MODE_MERGE_ADD 0x02
#define OVERRIDE_MODE_MERGE_MULTIPLY 0x03
#define OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE 0x04

//some RGB values for better readability
#define COLOR_BLACK   RGB{0,0,0}
#define COLOR_WHITE   RGB{255,255,255}
#define COLOR_RED     RGB{255,0,0}
#define COLOR_GREEN   RGB{0,255,0}
#define COLOR_BLUE    RGB{0,0,255}
#define COLOR_YELLOW  RGB{255,255,0}
#define COLOR_CYAN    RGB{0,255,255}
#define COLOR_MAGENTA RGB{255,0,255}
#define COLOR_ORANGE  RGB{255,165,0}

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