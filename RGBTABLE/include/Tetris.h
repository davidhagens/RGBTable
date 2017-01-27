#pragma once
#include "Tetromino.h"
#include "IGame.h"
#include "RenderImage.h"

namespace Games
{
  //since the actual LED Matrix is in horizontal format with it's origin in the upper left corner
  //but we want tetris to be executed in vertical format with it's origin in the lower left corner
  //every calculation in here is swapped on X and Y
  class TetrisGame : public IGame
  {
  private:
    //time to wait till the MoveCurrentDown() cuntion will be called
    const float timeToWait = 2.0f;
    //input offset since the next input update will be executed
    const float inputTimeToWait = 0.05f;
    int linesFilled;
    Tetris::Tetromino* currentTetromino;
    //tiemr for timeToWait
    float timer;
    //timer for inputTimeToWait
    float inputTimer;

    //renderImage which mirrors the board, so we don't actually calculate things within the official Pixel buffer
    RenderImage board;

    //Moves the current Tetromino down (on time or on controller down)
    void MoveCurrentDown();
    //check for full rows
    void CheckRows();
    //remove full rows
    void RemoveRow(int row);
  public:
    TetrisGame();
    ~TetrisGame();

    //overloaded functions from IGame
    void Load() override final;
    void Update() override final;
    void Draw() override final;
    void Reset() override final;
  };
}