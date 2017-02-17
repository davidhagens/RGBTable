#include "Rainbow.h"

void Effects::Rainbow::RainbowModePixel()
{
  for (uint16_t i = 0; i < LED_COUNT; i++)
  {
    _LEDMatrix->DrawPixel(i, Tools::Wheel((this->Loops() + i) % 360));
  }
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Rainbow::RainbowModeLineX()
{
  for (uint16_t i = 0; i < LED_H; i++)
  {
    _LEDMatrix->DrawStraightX(i, 0, LED_W - 1, Tools::Wheel((this->Loops() + i * 2) % 360));
  }
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Rainbow::RainbowModeLineY()
{
  for (uint16_t i = 0; i < LED_W; i++)
  {
    _LEDMatrix->DrawStraightY(i, 0, LED_H - 1, Tools::Wheel((this->Loops() + i * 2) % 360));
  }
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Rainbow::RainbowModeFull()
{
  _LEDMatrix->FillRect(Rect{ 0,0,LED_W,LED_H }, Tools::Wheel(this->Loops() % 360));
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Rainbow::Setup()
{
  _LEDMatrix;
}

void Effects::Rainbow::Loop()
{
  switch (this->currentMode)
  {
  case RainbowMode::pixel:
    this->RainbowModePixel();
    break;
  case RainbowMode::lineX:
    this->RainbowModeLineX();
    break;
  case RainbowMode::lineY:
    this->RainbowModeLineY();
    break;
  case RainbowMode::full:
    this->RainbowModeFull();
    break;
  }
}

Effects::Rainbow::Rainbow(RainbowMode::mode mode, size_t delay) : IEffect()
{
  this->currentMode = mode;
  this->delay = delay;
}

Effects::Rainbow::~Rainbow()
{
}

void Effects::Rainbow::SetMode(RainbowMode::mode mode)
{
  this->currentMode = mode;
}

void Effects::Rainbow::setDelay(size_t delay)
{
  this->delay = delay;
}
