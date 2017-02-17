#include "IEffect.h"

void Effects::IEffect::RunThread(IEffect* _this)
{
  while (!_this->quit)
  {
    _this->Loop();
    ++_this->loops;
  }
}

size_t Effects::IEffect::Loops()
{
  return this->loops;
}

bool Effects::IEffect::Quit()
{
  return this->quit;
}

Effects::IEffect::IEffect()
{
  this->loops = 0;
  this->quit = false;
}

Effects::IEffect::~IEffect()
{
  if (!this->quit) this->Exit();
}

void Effects::IEffect::Run()
{
  this->Setup();

  this->runningThread = std::thread(RunThread, this);
}

void Effects::IEffect::Exit()
{
  this->quit = true;
  this->runningThread.join();
}
