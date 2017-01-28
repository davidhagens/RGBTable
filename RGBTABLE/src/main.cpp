//#include "vld.h"
#include "LEDMatrix.h"
#include "Snake.h"
#include <iostream>

void main()
{
  IGame* snake = new Games::Snake();
  snake->SetTargetFrameRate(60);
  snake->StartLoop();
  
  //block for user input
  char a;
  std::cin >> a;
  snake->Quit();
  delete snake;
  LEDMatrix::Destroy();
  Controller::Destroy();
}