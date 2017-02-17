#pragma once
#include <inttypes.h>
#include "LEDMatrix.h"
#include "IGame.h"
#include "IEffect.h"
#include "Rainbow.h"
#include "Random.h"
#include "Snake.h"
#include "Tetris.h"

namespace TableMode
{
  enum modeFlags : uint8_t
  {
    OFF = 0x00,

    CONST_COLOR = 0x10,

    RAINBOW_PIXEL = 0x20,
    RAINBOW_LINE_X = 0x21,
    RAINBOW_LINE_Y = 0x22,
    RAINBOW_FULL = 0x23,

    RANDOM_PIXEL = 0x30,
    RANDOM_FULL = 0x31,

    GAMES_TETRIS = 0x40,
    GAMES_SNAKE = 0x41,
  };
}

class TableManager
{
private:
  TableMode::modeFlags currentMode;
  //a pointer to a possible current variable, like IEffect* or IGame*
  void* currentPtr;

  void CloseCurrentMode();
public:
  TableManager();
  ~TableManager();

  void SetMode(TableMode::modeFlags mode);
  //since some modes require data, this is the function you want to call
  void SetMode(TableMode::modeFlags mode, uint32_t data);
  TableMode::modeFlags GetCurrentMode();

  
};