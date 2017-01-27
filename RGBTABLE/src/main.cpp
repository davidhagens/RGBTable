//#include "vld.h"
#include "LEDMatrix.h"
#include "Bitmap.h"
#include "Tetris.h"
#include <iostream>

void main()
{
  for (;;)
  {
    for (size_t i = 0; i < 30; i++)
    {
      _LEDMatrix->Clear();
      _LEDMatrix->DrawCircle({ 18,9 }, i, COLOR_GREEN);
      _LEDMatrix->Show();
      Sleep(100);
    }
    for (size_t i = 0; i < 30; i++)
    {
      _LEDMatrix->Clear();
      _LEDMatrix->FillCircle({ 18,9 }, i, COLOR_RED);
      _LEDMatrix->Show();
      Sleep(100);
    }
  }

  LEDMatrix::Destroy();

  //IGame* tetris = new Games::TetrisGame();
  //tetris->SetTargetFrameRate(30);
  //tetris->StartLoop();
  //
  ////block for user input
  //char a;
  //std::cin >> a;
  //tetris->Quit();
  //delete tetris;
  //LEDMatrix::Destroy();
  //Controller::Destroy();
}