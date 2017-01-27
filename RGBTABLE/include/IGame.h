#pragma once
#include "Controller.h"
#include "LEDMatrix.h"
#include <chrono>
#include <thread>
#include "GameController.hpp"
#include <mutex>

class IGame
{
private:
  //chrono timepoints to check time
  std::chrono::steady_clock::time_point startTime;
  std::chrono::steady_clock::time_point lastFrame;
  //calculated deltaTime and TimeSinceStartup value in seconds
  float deltaTime;
  float time;

  //time for each frame to be executed in seconds
  float targetFrameRateMS;
  //thread handling
  bool quit = false;

  std::mutex mutex;
  std::thread loopThread; //main game loop, calls update & draw
  std::thread controllerThread; //controller loop, updates the controller serial

  //saved controller data since the last check
  GameController controller1;
  GameController controller2;

  //main game loop, calculates time and calls Update() and Draw() functions
  static void Loop(IGame* _this);
  //since the controller update can possible sleep several milliseconds while waiting for an answer, we just do this in another thread
  static void ControllerLoop(IGame* _this);

protected:
  //returns the complete Time since Startup(this will be recorded after the Load() function was executed)
  float Time();
  //returns the elapsed time since the last frame (recorded before the Update() function is executed)
  float DeltaTime();
  //returns a copy of the current controllerdata for NES controller 0 & NES controller 1
  GameController Controller1();
  GameController Controller2();

  //abstract functions that has to be overloaded by the actual game
  virtual void Load() = 0;
  virtual void Update() = 0;
  //Draw will be called after the Update loop, this should call the LEDMatrix::Show() function and can call the actual draw functions
  virtual void Draw() = 0;
  //Resets the game to it's startup. This will not affect the timeSinceStartup
  virtual void Reset() = 0;


public:
  IGame();
  ~IGame();

  //starts the game within a new thread with it's own loop
  void StartLoop();
  //sets the targetted framerate (or exactly the time to wait in seconds), this could vary per game, e.g. Tetris can run at 30 FPS
  void SetTargetFrameRate(uint16_t FPS);
  //stops all threads and blocks until they are finished
  void Quit();
};