#pragma once
#include <inttypes.h>

#define BIT_SET(var, pos) ((var) & (1 << (pos)))

class GameController
{
public:
  bool Up, Down, Right, Left, A, B, Start, Select;

  GameController()
  {}

  //NES Controller bitset, check http://forum.arduino.cc/index.php?topic=8481.0 for more information
  GameController(const uint8_t controllerData)
  {
    Up = !BIT_SET(controllerData, 3);
    Down = !BIT_SET(controllerData, 2);
    Right = !BIT_SET(controllerData, 0);
    Left = !BIT_SET(controllerData, 1);
    Start = !BIT_SET(controllerData, 4);
    Select = !BIT_SET(controllerData, 5);
    A = !BIT_SET(controllerData, 7);
    B = !BIT_SET(controllerData, 6);
  }
};