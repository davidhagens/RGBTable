#pragma once
#include "IEffect.h"

namespace Effects
{
  namespace RandomMode
  {
    enum mode : uint8_t
    {
      pixel,
      full
      //...
    };
  }

  class Random : public IEffect
  {
  private:
    RandomMode::mode currentMode;
    size_t delay;

    void RandomModePixel();
    void RandomModeFull();

    // Inherited via IEffect
    virtual void Setup() override;
    virtual void Loop() override;

  public:
    Random(RandomMode::mode mode, size_t delay);
    ~Random();

    void SetMode(RandomMode::mode mode);
    void SetDelay(size_t delay);
  };
}