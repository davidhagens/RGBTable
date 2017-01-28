#pragma once
#include "IGame.h"
#include <queue>

namespace Games
{
  namespace SnakeDirection
  {
    enum direction : uint8_t
    {
      up,
      right,
      down,
      left
    };
  }

  class Snake : public IGame
  {
  private:
    //time to the next move
    float timeToWait = 0.5f;
    float timer;
    std::queue<Vector2> snake;
    //board to draw on, this will be mirrored to the LEDMatrix renderImage
    RenderImage board;
    SnakeDirection::direction currentDirection;
    SnakeDirection::direction nextMove;

    Vector2 currentApple;
    Vector2 head;

    void Move();
    void SetHead(Vector2 v);
    void EraseBack();

    void Load() override final;
    void Update() override final;
    void Draw() override final;
    void Reset() override final;

  public:
    Snake();
    ~Snake();
  };
}