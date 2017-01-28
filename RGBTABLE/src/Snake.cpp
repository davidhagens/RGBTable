#include "Snake.h"

void Games::Snake::Move()
{
  Vector2 next = this->head + Vector2{
    this->nextMove == SnakeDirection::left ? -1 : this->nextMove == SnakeDirection::right ? 1 : 0,
    this->nextMove == SnakeDirection::up ? -1 : this->nextMove == SnakeDirection::down ? 1 : 0 };
  if (next.X < 0 || next.X >= LED_W || next.Y < 0 || next.Y >= LED_H || this->board.getPixelColor(next) != COLOR_BLACK)
  {
    this->Reset();
    return;
  }
  if (next == this->currentApple)
  {
    this->SetHead(next);
    //calculate a new apple which is not inside the snake
    while (this->board.getPixelColor((this->currentApple = { rand() % LED_W, rand() % LED_H })) != COLOR_BLACK);
  }
  else
  {
    this->EraseBack();
    this->SetHead(next);
  }
}

void Games::Snake::SetHead(Vector2 v)
{
  this->board.DrawPixel(v, COLOR_BLUE);
  this->head = v;
  this->snake.push(v);
}

void Games::Snake::EraseBack()
{
  this->board.DrawPixel(this->snake.front(), COLOR_BLACK);
  this->snake.pop();
}


void Games::Snake::Load()
{
  this->Reset();
}

void Games::Snake::Update()
{
  this->timer -= this->DeltaTime();
  if (this->timer < 0)
  {
    this->timer = this->timeToWait;
    this->Move();
  }

  GameController gc = this->Controller1();
  if (gc.Left && this->currentDirection != SnakeDirection::right)
  {
    this->nextMove = SnakeDirection::left;
  }
  else if (gc.Right && this->currentDirection != SnakeDirection::left)
  {
    this->nextMove = SnakeDirection::right;
  }
  else if (gc.Up && this->currentDirection != SnakeDirection::down)
  {
    this->nextMove = SnakeDirection::up;
  }
  else if (gc.Down && this->currentDirection != SnakeDirection::up)
  {
    this->nextMove = SnakeDirection::down;
  }

  if (gc.Start)
  {
    this->Reset();
  }
}

void Games::Snake::Draw()
{
  _LEDMatrix->DrawRenderImage(&this->board);
  _LEDMatrix->DrawPixel(this->currentApple, COLOR_RED);
  _LEDMatrix->Show();
}

void Games::Snake::Reset()
{
  std::queue<Vector2>().swap(this->snake);
  this->currentApple = { rand() % LED_W, rand() % LED_H };
  Vector2 v = { rand() % LED_W, rand() % LED_H };
  while (v == this->currentApple)
  {
    v = { rand() % LED_W, rand() % LED_H };
  }
  this->SetHead(v);
}

Games::Snake::Snake()
{

}

Games::Snake::~Snake()
{

}
