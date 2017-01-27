#include "IGame.h"

void IGame::Loop(IGame* _this)
{
  while (!_this->quit)
  {
    auto currentTime = std::chrono::steady_clock::now();
    //wait until we reached our targetted frame rate
    while ((_this->deltaTime = (currentTime.time_since_epoch() - _this->lastFrame.time_since_epoch()).count() / 1000000000.0f) < _this->targetFrameRateMS)
    {
      currentTime = std::chrono::steady_clock::now();
      //yield and sleep to lower the CPU usage within the loop
      std::this_thread::yield();
      Sleep(1);
    }
    //save time in seconds 
    _this->time = (currentTime.time_since_epoch() - _this->startTime.time_since_epoch()).count() / 1000000000.0f;
    _this->Update();
    _this->Draw();
    _this->lastFrame = currentTime;
  }
}

void IGame::ControllerLoop(IGame* _this)
{
  while (!_this->quit)
  {
    //update the controller data from the Arduino
    _Controller->Update();
    _this->mutex.lock();
    _this->controller1 = GameController(_Controller->GetCon0());
    _this->controller2 = GameController(_Controller->GetCon1());
    _this->mutex.unlock();
    //yield and sleep to lower the CPU usage within the loop
    std::this_thread::yield();
    Sleep(1);
  }
}

float IGame::Time()
{
  return this->time;
}

float IGame::DeltaTime()
{
  return this->deltaTime;
}

GameController IGame::Controller1()
{
  //return a copy of the current controller data
  this->mutex.lock();
  GameController ret(this->controller1);
  this->mutex.unlock();
  return ret;
}

GameController IGame::Controller2()
{
  //return a copy of the current controller data
  this->mutex.lock();
  GameController ret(this->controller2);
  this->mutex.unlock();
  return ret;
}

IGame::IGame()
{
}

IGame::~IGame()
{
}

void IGame::StartLoop()
{
  //call the instances of Controller and LEDMatrix to make sure that they're existing
  _Controller;
  _LEDMatrix;

  this->Load();
  //save Start time and start the threads
  this->startTime = std::chrono::steady_clock::now();
  this->loopThread = std::thread(Loop, this);
  this->controllerThread = std::thread(ControllerLoop, this);
}

void IGame::SetTargetFrameRate(uint16_t FPS)
{
  //convert FPS to seconds
  this->targetFrameRateMS = 1.0f / FPS;
}

void IGame::Quit()
{
  //terminate and wait till both threads have finished
  this->quit = true;
  this->loopThread.join();
  this->controllerThread.join();
}

