#include "Random.h"

void Effects::Random::RandomModePixel()
{
  for (uint16_t i = 0; i < LED_COUNT; i++)
  {
    _LEDMatrix->DrawPixel(i, Tools::Wheel(rand() % 360));
  }
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Random::RandomModeFull()
{
  _LEDMatrix->FillRect({ 0,0,LED_W,LED_H }, Tools::Wheel(rand() % 360));
  _LEDMatrix->Show();
  Sleep((DWORD)this->delay);
}

void Effects::Random::Setup()
{
  _LEDMatrix;
}

void Effects::Random::Loop()
{
  switch (currentMode)
  {
  case RandomMode::pixel:
    this->RandomModePixel();
    break;
  case RandomMode::full:
    this->RandomModeFull();
    break;
  }
}

Effects::Random::Random(RandomMode::mode mode, size_t delay) : IEffect()
{
  this->currentMode = mode;
  this->delay = delay;
}

Effects::Random::~Random()
{
}

void Effects::Random::SetMode(RandomMode::mode mode)
{
  this->currentMode = mode;
}

void Effects::Random::SetDelay(size_t delay)
{
  this->delay = delay;
}