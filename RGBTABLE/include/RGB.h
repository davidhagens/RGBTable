#pragma once
#include <inttypes.h>
#include "Math.hpp"
struct RGB
{
  uint8_t r, g, b;

#pragma region operator
  inline RGB operator+(const RGB& other)
  {
    RGB ret = { this->r + other.r, this->g + other.g, this->b + other.b };
    return ret;
  }

  inline RGB operator-(const RGB& other)
  {
    RGB ret = { this->r - other.r, this->g - other.g, this->b - other.b };
    return ret;
  }

  inline RGB operator*(const RGB& other)
  {
    RGB ret = { this->r * other.r, this->g * other.g, this->b * other.b };
    return ret;
  }

  inline RGB operator/(const RGB& other)
  {
    RGB ret = { this->r / other.r, this->g / other.g, this->b / other.b };
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