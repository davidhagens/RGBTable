#include "Tetris.h"

void Games::TetrisGame::MoveCurrentDown()
{
  Vector2 pos = this->currentTetromino->Position();
  this->currentTetromino->Erase(); //erase the current tetromino from the pixel buffer
  bool move = true;
  Pixel* pixels; //get the current Tetromino's pixels
  this->currentTetromino->GetShape()->Get(&pixels);
  for (size_t i = 0; i < 4; i++)
  {
    if (pixels[i].pos.X + pos.X - 1 < 0) //check if we are at ground level
    {
      move = false;
      break;
    }
    if (this->board.getPixelColor(pixels[i].pos + pos + Vector2{ -1, 0 }) != COLOR_BLACK) //check if there are set pixels 
    {
      move = false;
      break;
    }
  }
  if (move)
  {
    this->currentTetromino->MoveDown();
    this->currentTetromino->Draw(); //redraw the tetromino
  }
  else //we can't move down
  {
    this->currentTetromino->Draw(); //redraw the tetromino

    if (this->currentTetromino->Position().X == LED_W - 4) //we are at the highest possible position
    {
      printf("Tetris Lost with %i points\n", this->linesFilled);
      this->Reset();
      return;
    }
    else if (this->linesFilled >= LED_H) //since the score will be displayed in the upper row of pixels, our max score is LED_H - 1
    {
      printf("Tetris won \n");
      this->Reset();
      return;
    }

    this->CheckRows();
    //create a new tetromino
    delete this->currentTetromino;
    this->currentTetromino = new Tetris::Tetromino(static_cast<Tetris::TetrominoType>(rand() % 7));
  }
}

void Games::TetrisGame::CheckRows()
{
  bool full = true;
  for (int i = LED_W - 4; i >= 0; i--)
  {
    full = true;
    for (int j = 0; j < LED_H; j++)
    { //check every pixel's color to determine if the row is full or not
      if (this->board.getPixelColor({ i, j }) == COLOR_BLACK)
      {
        full = false;
        break; //to prevent useless calculation we can continue with the next row
      }
    }
    if (full)
    {
      this->RemoveRow(i);
      this->linesFilled++;
      ++i; //since every row above the removed row is now one row further down, we have to re check the new row (otherwise we would possibly not remove all filled rows at once)
    }
  }
}

void Games::TetrisGame::RemoveRow(int row)
{
  for (int x = row; x < LED_W - 2; x++) // first row is reserved for score
  {
    for (int y = 0; y < LED_H; y++)
    {
      //move every pixel one row further down
      this->board.DrawPixel(Vector2{ x, y }, this->board.getPixelColor(Vector2{ x + 1, y }));
    }
  }
}

Games::TetrisGame::TetrisGame() : board()
{
  
}

Games::TetrisGame::~TetrisGame()
{
  if (this->currentTetromino != nullptr)
    delete this->currentTetromino;
}

void Games::TetrisGame::Load()
{
  this->linesFilled = 0;
  this->currentTetromino = new Tetris::Tetromino(static_cast<Tetris::TetrominoType>(rand() % 7));
}

void Games::TetrisGame::Update()
{
  //check timers
  this->timer -= this->DeltaTime();
  if (this->timer < 0)
  {
    this->MoveCurrentDown();
    this->timer = timeToWait;
  }
  this->inputTimer -= this->DeltaTime();
  if (this->inputTimer < 0)
  {
    this->inputTimer = this->inputTimeToWait;
  }
  else return; //from here everything is related to controller input, so we don't check this if the timer hasn't elapsed

  GameController con1 = this->Controller1(); //get a controller copy (we copy this to prevent the ControllerLoop from Updating our current used Data[Yes, we could also use a mutex here, but I didn't want to block the thread])
  if (con1.Left)
  {
    //check and move left
    Vector2 pos = this->currentTetromino->Position();
    this->currentTetromino->Erase();
    bool move = true;
    Pixel* pixels;
    this->currentTetromino->GetShape()->Get(&pixels);
    for (size_t i = 0; i < 4; i++)
    {
      if ((pixels[i].pos + pos).Y - 1 < 0)
      {
        move = false;
        break;
      }
      if (this->board.getPixelColor(pixels[i].pos + pos + Vector2{ 0,-1 }) != COLOR_BLACK)
      {
        move = false;
        break;
      }
    }
    if (move)
    {
      this->currentTetromino->Move(false);
    }
    this->currentTetromino->Draw(); //redraw the pixel
  }
  else if (con1.Right)
  {
    Vector2 pos = this->currentTetromino->Position();
    this->currentTetromino->Erase();

    bool move = true;
    Pixel* pixels;
    this->currentTetromino->GetShape()->Get(&pixels);
    for (size_t i = 0; i < 4; i++)
    {
      if ((pixels[i].pos + pos).Y + 1 >= LED_H)
      {
        move = false;
        break;
      }
      if (this->board.getPixelColor(pixels[i].pos + pos + Vector2{ 0, 1 }) != COLOR_BLACK)
      {
        move = false;
        break;
      }
    }
    if (move)
    {
      this->currentTetromino->Move(true);
    }
    this->currentTetromino->Draw(); //redraw the pixel
  }
  if (con1.Down)
  {
    this->MoveCurrentDown(); //since this is an own function, we just call it
  }
  if (con1.A)
  {
    //rotate the current Tetromino
    if (this->currentTetromino->Type() == Tetris::O) return; //O can't be rotated
    this->currentTetromino->Erase();
    Tetris::Tetromino* currentCopy = new Tetris::Tetromino(this->currentTetromino->GetShape()); //create a copy of the current tetramino which will not be drawn
    currentCopy->Rotate(); //rotate the copy
    bool move = true;
    Pixel* pixels;
    currentCopy->GetShape()->Get(&pixels);
    Vector2 pos = this->currentTetromino->Position();
    for (size_t i = 0; i < 4; i++)
    {
      if ((pixels[i].pos + pos).Y >= LED_H || (pixels[i].pos + pos).Y < 0 || (pixels[i].pos + pos).X < 0) //check if we are inside our Board
      {
        move = false;
        break;
      }
      if (this->board.getPixelColor(pixels[i].pos + pos) != COLOR_BLACK) //check if every pixel is Black
      {
        move = false;
        break;
      }
    }
    if (move)
    {
      //we can rotate our current Tetromino
      this->currentTetromino->Rotate();
    }
    //and we don't need our copy anymore
    delete currentCopy;
    this->currentTetromino->Draw(); //redraw the current Tetromino
  }
#if _DEBUG
  //debug only, maybe this will go in the release version, too
  if (con1.Start)
  {
    this->Reset();
  }
#endif
}

void Games::TetrisGame::Draw()
{
  if (this->linesFilled > 0)
  {
    //Draw the score in the first row of pixels
    this->board.DrawStraightY(LED_W - 1, 0, this->linesFilled, COLOR_WHITE);
  }
  //draw the render image to the actual pixel buffer
  _LEDMatrix->DrawRenderImage(&this->board);
  _LEDMatrix->Show();
}

void Games::TetrisGame::Reset()
{
  //reset and create a new game
  delete this->currentTetromino;
  this->board.Clear();
  this->linesFilled = 0;
  this->currentTetromino = new Tetris::Tetromino(static_cast<Tetris::TetrominoType>(rand() % 7));
}
