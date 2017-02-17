#include "vld.h"
#include <iostream>
#include "TableManager.h"

void main()
{
  srand(GetTickCount());

  TableManager manager;
  char a;
  bool quit = false;
  
  while (!quit)
  {
    std::cin >> a;
  
    switch (a)
    {
    case '0':
      manager.SetMode(TableMode::RAINBOW_PIXEL, 50);
      break;
    case '1':
      manager.SetMode(TableMode::RAINBOW_FULL, 50);
      break;
    case '2':
      manager.SetMode(TableMode::RANDOM_PIXEL, 50);
      break;
    case '3':
      manager.SetMode(TableMode::RANDOM_FULL, 500);
      break;
    case '4':
      manager.SetMode(TableMode::CONST_COLOR, Tools::RGBToInt(COLOR_GREEN));
      break;
    case '^':
      quit = true;
      break;
    }
  }
  manager.SetMode(TableMode::OFF);
}