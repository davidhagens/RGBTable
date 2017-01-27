#include "Tetromino.h"

Games::Tetris::Tetromino::Tetromino(TetrominoType type)
{
  this->type = type;
  this->shape = new Shape(4);
  switch (type)
  {
  case I:
  {
    Pixel pixels[4] = {
      { { 0,0  }, COLOR_CYAN },
      { { 0,-1 }, COLOR_CYAN },
      { { 0,1  }, COLOR_CYAN },
      { { 0,2  }, COLOR_CYAN }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case J:
  {
    Pixel pixels[4] = {
      { { -1,1 }, COLOR_BLUE },
      { { 0,-1 }, COLOR_BLUE },
      { { 0,0  }, COLOR_BLUE },
      { { 0,1  }, COLOR_BLUE }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case L:
  { 
    Pixel pixels[4] = {
      { { 0,0  }, COLOR_ORANGE },
      { { 0,-1 }, COLOR_ORANGE },
      { { 0,1  }, COLOR_ORANGE },
      { { 1,1  }, COLOR_ORANGE }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case O:
  {
    Pixel pixels[4] = {
      { { 0,0  }, COLOR_YELLOW },
      { { 1,0  }, COLOR_YELLOW },
      { { 0,1  }, COLOR_YELLOW },
      { { 1,1  }, COLOR_YELLOW }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case S:
  {
    Pixel pixels[4] = {
      { { 0,0  }, COLOR_GREEN },
      { { 0,-1 }, COLOR_GREEN },
      { { 1,0  }, COLOR_GREEN },
      { { 1,1  }, COLOR_GREEN }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case T:
  {
    Pixel pixels[4] = {
      { { 0,0  }, COLOR_MAGENTA },
      { { 0,-1 }, COLOR_MAGENTA },
      { { -1,0 }, COLOR_MAGENTA },
      { { 0,1  }, COLOR_MAGENTA }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  case Z:
  {
    Pixel pixels[4] = {
      { { 0,0   }, COLOR_RED },
      { { 0,-1  }, COLOR_RED },
      { { -1,0  }, COLOR_RED },
      { { -1,1  }, COLOR_RED }
    };
    this->shape->Set(pixels, 4);
  }
  break;
  }
  this->pos = { LED_W - 4, LED_H / 2 };
}

Games::Tetris::Tetromino::Tetromino(Shape * shape)
{
  Pixel* pixels;
  shape->Get(&pixels);
  this->shape = new Shape(4);
  this->shape->Set(pixels, 4);
}

Games::Tetris::Tetromino::~Tetromino()
{
  delete this->shape;
}

Vector2 Games::Tetris::Tetromino::Position()
{
  return this->pos;
}

Shape* Games::Tetris::Tetromino::GetShape()
{
  return this->shape;
}

Games::Tetris::TetrominoType Games::Tetris::Tetromino::Type()
{
  return this->type;
}

void Games::Tetris::Tetromino::SetPos(Vector2 pos)
{
  this->pos = pos;
}

void Games::Tetris::Tetromino::Rotate()
{
  Pixel* pixels;
  this->shape->Get(&pixels);
  if (this->type != O)
  {
    for (size_t i = 0; i < 4; i++)
    {
      int y = pixels[i].pos.Y;
      pixels[i].pos.Y = pixels[i].pos.X * -1;
      pixels[i].pos.X = y;
    }
  }
}

void Games::Tetris::Tetromino::Move(bool right)
{
  if (right)
  {
    ++this->pos.Y;
  }
  else
  {
    --this->pos.Y;
  }
}

void Games::Tetris::Tetromino::MoveDown()
{
  --this->pos.X;

}

void Games::Tetris::Tetromino::Draw()
{
  _LEDMatrix->DrawShape(this->shape, this->pos);
}

void Games::Tetris::Tetromino::Erase()
{
  _LEDMatrix->DrawShape(this->shape, this->pos, COLOR_BLACK);
}
