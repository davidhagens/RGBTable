#pragma once
#include "Shape.h"
#include "LEDMatrix.h"

namespace Games
{
  namespace Tetris
  {
    enum TetrominoType : uint8_t
    {
      I,
      J,
      L,
      O,
      S,
      T,
      Z
    };

    class Tetromino
    {
    private:
      //tetromino shape, this will be used to draw on the LEDMatrix
      Shape* shape;
      //current position of this tetromino
      Vector2 pos;
      TetrominoType type;
    public:
      //creates a new tetromino at point (LED_W - 4, LED_H / 2) with the given type
      Tetromino(const TetrominoType type);
      //copies a Tetramino's shape (used for rotation checking)
      Tetromino(Shape* pixels);
      ~Tetromino();
      //getter
      Vector2 Position();
      Shape* GetShape();
      TetrominoType Type();
      //set the position
      void SetPos(const Vector2 pos);

      void Rotate();
      //move in left right directions (this will move on the Y axis)
      void Move(const bool right);
      //move down (X axis)
      void MoveDown();

      //Draw the current Shape at the current position to the LEDMatrix' pixel buffer
      void Draw();
      //Erase the current shape at the current position from the LEDMAtrix' pixel buffer
      void Erase();
    };
  }
}