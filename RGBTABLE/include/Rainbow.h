#pragma once
#include "IEffect.h"

namespace Effects
{
  namespace RainbowMode
  {
    enum mode : uint8_t
    {
      pixel,
      lineX,
      lineY,
      full
    };
  }

  class Rainbow : public IEffect
  {
  private:
    uint16_t wheelPos;
    RainbowMode::mode currentMode;
    size_t delay;

    void RainbowModePixel();
    void RainbowModeLineX();
    void RainbowModeLineY();
    void RainbowModeFull();

    // Inherited via IEffect
    virtual void Setup() override;
    virtual void Loop() override;

  public:
    Rainbow(RainbowMode::mode mode, size_t delay);
    ~Rainbow();

    void SetMode(RainbowMode::mode mode);
    void setDelay(size_t delay);
  };
}