#include "LEDMatrix.h"

LEDMatrix* LEDMatrix::__instance;

void LEDMatrix::ShowS0(LEDMatrix * _this)
{
  while (!_this->quit)
  {
    if (_this->update0)
    {
      //send the pixel data to Arduino 0
      _this->ser0->WriteData(_this->img, LED_S0_BYTES);
      _this->update0 = false;
    }
    //yield and sleep to lower the CPU usage within the loop
    std::this_thread::yield();
    Sleep(1);
  }
}

void LEDMatrix::ShowS1(LEDMatrix * _this)
{
  while (!_this->quit)
  {
    if (_this->update1)
    {
      //send the pixel data to Arduino 1
      _this->ser1->WriteData(_this->img + LED_S0_BYTES, LED_S1_BYTES);
      _this->update1 = false;
    }
    //yield and sleep to lower the CPU usage within the loop
    std::this_thread::yield();
    Sleep(1);
  }
}

LEDMatrix* LEDMatrix::Instance()
{
  if (__instance == nullptr)
    __instance = new LEDMatrix();
  return __instance;
}

void LEDMatrix::Destroy()
{
  delete __instance;
}

LEDMatrix::LEDMatrix() : RenderImage()
{
  //create serial connections
  this->ser0 = new Serial(0xE0); //identifier for first Arduino, BAUD Rate is 1,000,000
  this->ser1 = new Serial(0xE1); //identifier for second Arduino
  //start Show threads
  this->t0 = std::thread(ShowS0, this);
  this->t1 = std::thread(ShowS1, this);
  this->Clear();
  this->Show();
}

LEDMatrix::~LEDMatrix()
{
  //terminate and wait until the two threads are finished
  this->quit = true;
  this->t0.join();
  this->t1.join();

  //close the serial connections
  delete this->ser0;
  delete this->ser1;
}

void LEDMatrix::Show()
{
  this->update0 = true;
  this->update1 = true;
}