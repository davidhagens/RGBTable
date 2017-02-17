#pragma once
#include <inttypes.h>
#include "Math.hpp"
struct RGB
{
  uint8_t r, g, b;

#pragma region operator
  inline RGB operator+(const RGB& other)
  {
    RGB ret = { (uint8_t)(this->r + other.r), uint8_t(this->g + other.g), uint8_t(this->b + other.b) };
    return ret;
  }

  inline RGB operator-(const RGB& other)
  {
    RGB ret = { (uint8_t)(this->r - other.r), (uint8_t)(this->g - other.g), (uint8_t)(this->b - other.b) };
    return ret;
  }

  inline RGB operator*(const RGB& other)
  {
    RGB ret = { (uint8_t)(this->r * other.r), (uint8_t)(this->g * other.g), (uint8_t)(this->b * other.b) };
    return ret;
  }

  inline RGB operator/(const RGB& other)
  {
    RGB ret = { (uint8_t)(this->r / other.r), (uint8_t)(this->g / other.g), (uint8_t)(this->b / other.b) };
    return ret;
  }

  inline RGB operator+=(const RGB& other)
  {
    this->r += other.r;
    this->g += other.g;
    this->b += other.b;
  }

  inline RGB operator-=(const RGB& other)
  {
    this->r -= other.r;
    this->g -= other.g;
    this->b -= other.b;
  }

  inline RGB operator*=(const RGB& other)
  {
    this->r *= other.r;
    this->g *= other.g;
    this->b *= other.b;
  }

  inline RGB operator/=(const RGB& other)
  {
    this->r /= other.r;
    this->g /= other.g;
    this->b /= other.b;
  }

  inline bool operator==(const RGB& other)
  {
    return this->r == other.r && this->g == other.g && this->b == other.b;
  }

  inline bool operator!=(const RGB& other)
  {
    return !(*this == other);
  }
#pragma endregion
};

struct Pixel
{
  Vector2 pos;
  RGB color;
};

class Tools
{
public:
  //RGB Wheel implementation on top of this https://commons.wikimedia.org/wiki/File:HSV-RGB-comparison.svg picture
  inline static RGB Wheel(uint16_t wheelPos)
  {
    wheelPos = wheelPos % 360;
    //60 degrees
    if (wheelPos < 60)
    {
      return RGB{ 255, (uint8_t)(wheelPos * 4.25f), 0 };
    }
    wheelPos -= 60;
    //120 degrees
    if (wheelPos < 60)
    {
      return RGB{ (uint8_t)(255 - wheelPos * 4.25f), 255, 0 };
    }
    wheelPos -= 60;
    //180 degrees
    if (wheelPos < 60)
    {
      return RGB{ 0, 255, (uint8_t)(wheelPos * 4.25f) };
    }
    wheelPos -= 60;
    //240°
    if (wheelPos < 60)
    {
      return RGB{ 0, (uint8_t)(255 - wheelPos * 4.25f), 255 };
    }
    wheelPos -= 60;
    //300°
    if (wheelPos < 60)
    {
      return RGB{ (uint8_t)(wheelPos * 4.25f), 0, 255 };
    }
    wheelPos -= 60;
    //360°
    if (wheelPos < 60)
    {
      return RGB{ 255, 0, (uint8_t)(255 - wheelPos * 4.25f) };
    }
    return RGB{ 0,0,0 };
  }

  inline static uint32_t RGBToInt(RGB val)
  {
    return *reinterpret_cast<uint32_t*>(&val);
  }

  inline static RGB IntToRGB(uint32_t val)
  {
    return *reinterpret_cast<RGB*>(&val);
  }
};