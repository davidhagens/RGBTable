#pragma once
#include "LEDMatrix.h"
#include <thread>
/*
  Effect Interface
  Effects are full scale LED Effects (like a rainbow or a random mode, or everything you can imagine (and actually code...))
  Effects are functionally like an Arduino, so it has a Setup and a Loop function
*/
namespace Effects
{
  class IEffect
  {
  private:
    static void RunThread(IEffect* _this);

    //loop counter, possible usable in an effect
    size_t loops;
    bool quit;
    std::thread runningThread;

  protected:
    size_t Loops();
    bool Quit();

    virtual void Setup() = 0;
    virtual void Loop() = 0;

  public:
    IEffect();
    virtual ~IEffect();

    //this runs setup and loops the loop until it should stop
    void Run();
    //Exits a running effect
    void Exit();
  };
}