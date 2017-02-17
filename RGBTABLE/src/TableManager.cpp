#include "TableManager.h"

void TableManager::CloseCurrentMode()
{
  switch (this->currentMode & 0xF0)
  {
  case 0x00:
    return;
  case 0x10:
    return;
  case 0x20: case 0x30:
    reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Exit();
    delete this->currentPtr;
    return;
  case 0x40:
    reinterpret_cast<IGame*>(this->currentPtr)->Quit();
    delete this->currentPtr;
    return;
  }
}

TableManager::TableManager()
{
  this->currentMode = TableMode::OFF;
  _LEDMatrix;
}

TableManager::~TableManager()
{
  this->CloseCurrentMode();
  LEDMatrix::Destroy();
}

void TableManager::SetMode(TableMode::modeFlags mode)
{
  this->CloseCurrentMode();
  this->currentMode = mode;
  switch (mode & 0xF0)
  {
  case 0x00: //off
    _LEDMatrix->Clear();
    _LEDMatrix->Show();
    break;
  case 0x10: //const color
    _LEDMatrix->DrawPixels(0, LED_COUNT, COLOR_WHITE);
    _LEDMatrix->Show();
    break;
  case 0x20: //Rainbow
    switch (mode & 0x0F)
    {
    case 0x00: //pixel 
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::pixel, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    case 0x01: //line x
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::lineX, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    case 0x02: //line y
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::lineY, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    case 0x03: //full
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::full, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    }
    break;
  case 0x30: //random
    switch (mode & 0x0F)
    {
    case 0x00: //pixel
    {
      this->currentPtr = new Effects::Random(Effects::RandomMode::pixel, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    case 0x01: //full
    {
      this->currentPtr = new Effects::Random(Effects::RandomMode::full, 100);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
      break;
    }
    break;
  case 0x40: //game
    switch (mode & 0x0F)
    {
    case 0x00: //tetris
    {
      this->currentPtr = new Games::TetrisGame();
      reinterpret_cast<IGame*>(this->currentPtr)->SetTargetFrameRate(30);
      reinterpret_cast<IGame*>(this->currentPtr)->StartLoop();
    }
      break;
    case 0x01: //snake
    {
      this->currentPtr = new Games::Snake();
      reinterpret_cast<IGame*>(this->currentPtr)->SetTargetFrameRate(30);
      reinterpret_cast<IGame*>(this->currentPtr)->StartLoop();
    }
      break;
    }
    break;
  }
}

void TableManager::SetMode(TableMode::modeFlags mode, uint32_t data)
{
  this->CloseCurrentMode();
  this->currentMode = mode;
  switch (mode & 0xF0)
  {
  case 0x00: //off
    _LEDMatrix->Clear();
    _LEDMatrix->Show();
    break;
  case 0x10: //const color
    _LEDMatrix->DrawPixels(0, LED_COUNT, Tools::IntToRGB(data));
    _LEDMatrix->Show();
    break;
  case 0x20: //Rainbow
    switch (mode & 0x0F)
    {
    case 0x00: //pixel
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::pixel, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    case 0x01: //line x
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::lineX, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    case 0x02: //line y
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::lineY, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    case 0x03: //full
    {
      this->currentPtr = new Effects::Rainbow(Effects::RainbowMode::full, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    }
    break;
  case 0x30: //random
    switch (mode & 0x0F)
    {
    case 0x00: //pixel
    {
      this->currentPtr = new Effects::Random(Effects::RandomMode::pixel, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    case 0x01: //full
    {
      this->currentPtr = new Effects::Random(Effects::RandomMode::full, data);
      reinterpret_cast<Effects::IEffect*>(this->currentPtr)->Run();
    }
    break;
    }
    break;
  case 0x40: //game
    switch (mode & 0x0F)
    {
    case 0x00: //tetris
    {
      this->currentPtr = new Games::TetrisGame();
      reinterpret_cast<IGame*>(this->currentPtr)->SetTargetFrameRate(30);
      reinterpret_cast<IGame*>(this->currentPtr)->StartLoop();
    }
    break;
    case 0x01: //snake
    {
      this->currentPtr = new Games::Snake();
      reinterpret_cast<IGame*>(this->currentPtr)->SetTargetFrameRate(30);
      reinterpret_cast<IGame*>(this->currentPtr)->StartLoop();
    }
    break;
    }
    break;
  }

}

TableMode::modeFlags TableManager::GetCurrentMode()
{
  return this->currentMode;
}
