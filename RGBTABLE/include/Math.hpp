#pragma once
#include <inttypes.h>

inline uint16_t SwapByteOrder(uint16_t val)
{
  return ((val & 0xff) << 8) | ((val >> 8) & 0xff);
}

inline uint32_t SwapByteOrder(uint32_t val)
{
  return ((val & 0x000000ff) << 24) +
    ((val & 0x0000ff00) << 8) +
    ((val & 0x00ff0000) >> 8) +
    ((val & 0xff000000) >> 24);
}

inline uint64_t SwapByteOrder(uint64_t val)
{
  return ((0x00000000000000FF) & (val >> 56)
    | (0x000000000000FF00) & (val >> 40)
    | (0x0000000000FF0000) & (val >> 24)
    | (0x00000000FF000000) & (val >> 8)
    | (0x000000FF00000000) & (val << 8)
    | (0x0000FF0000000000) & (val << 24)
    | (0x00FF000000000000) & (val << 40)
    | (0xFF00000000000000) & (val << 56));
}

inline uint16_t Max(uint16_t* values, uint16_t count)
{
  uint16_t ret = values[0];
  for (uint16_t i = 0; i < count; i++)
  {
    if (ret < values[i]) ret = values[i];
  }
  return ret;
}

struct _RGB
{
  uint8_t r;
  uint8_t g;
  uint8_t b;
};

struct Vector2
{
  int X, Y;
#pragma region operator
  inline Vector2 operator+(const Vector2& other)
  {
    return{ this->X + other.X, this->Y + other.Y };
  }

  inline Vector2 operator+(const int other)
  {
    return{ this->X + other, this->Y + other };
  }

  inline Vector2 operator-(const Vector2& other)
  {
    return{ this->X - other.X, this->Y - other.Y };
  }

  inline Vector2 operator-(const int other)
  {
    return{ this->X - other, this->Y - other };
  }

  inline Vector2 operator*(const Vector2& other)
  {
    return{ this->X * other.X, this->Y * other.Y };
  }

  inline Vector2 operator*(const int other)
  {
    return{ this->X * other, this->Y * other };
  }

  inline Vector2 operator/(const Vector2& other)
  {
    return{ this->X / other.X, this->Y / other.Y };
  }

  inline Vector2 operator/(const int other)
  {
    return{ this->X / other, this->Y / other };
  }

  inline void operator+=(const Vector2& other)
  {
    this->X += other.X;
    this->Y += other.Y;
  }

  inline void operator+=(const int other)
  {
    this->X += other;
    this->Y += other;
  }

  inline void operator-=(const Vector2& other)
  {
    this->X -= other.X;
    this->Y -= other.Y;
  }

  inline void operator-=(const int other)
  {
    this->X -= other;
    this->Y -= other;
  }

  inline void operator*=(const Vector2& other)
  {
    this->X *= other.X;
    this->Y *= other.Y;
  }

  inline void operator*=(const int other)
  {
    this->X *= other;
    this->Y *= other;
  }

  inline void operator/=(const Vector2& other)
  {
    this->X /= other.X;
    this->Y /= other.Y;
  }

  inline void operator/=(const int other)
  {
    this->X /= other;
    this->Y /= other;
  }

  inline bool operator==(const Vector2& other)
  {
    return this->X == other.X && this->Y == other.Y;
  }

  inline bool operator!=(const Vector2& other)
  {
    return this->X != other.X || this->Y != other.Y;
  }
#pragma endregion
};

struct Vector2F
{
  float X, Y;
#pragma region operator
  inline Vector2F operator+(const Vector2F& other)
  {
    return{ this->X + other.X, this->Y + other.Y };
  }

  inline Vector2F operator+(const float other)
  {
    return{ this->X + other, this->Y + other };
  }

  inline Vector2F operator-(const Vector2F& other)
  {
    return{ this->X - other.X, this->Y - other.Y };
  }

  inline Vector2F operator-(const float other)
  {
    return{ this->X - other, this->Y - other };
  }

  inline Vector2F operator*(const Vector2F& other)
  {
    return{ this->X * other.X, this->Y * other.Y };
  }

  inline Vector2F operator*(const float other)
  {
    return{ this->X * other, this->Y * other };
  }

  inline Vector2F operator/(const Vector2F& other)
  {
    return{ this->X / other.X, this->Y / other.Y };
  }

  inline Vector2F operator/(const float other)
  {
    return{ this->X / other, this->Y / other };
  }

  inline void operator+=(const Vector2F& other)
  {
    this->X += other.X;
    this->Y += other.Y;
  }

  inline void operator+=(const float other)
  {
    this->X += other;
    this->Y += other;
  }

  inline void operator-=(const Vector2F& other)
  {
    this->X -= other.X;
    this->Y -= other.Y;
  }

  inline void operator-=(const float other)
  {
    this->X -= other;
    this->Y -= other;
  }

  inline void operator*=(const Vector2F& other)
  {
    this->X *= other.X;
    this->Y *= other.Y;
  }

  inline void operator*=(const float other)
  {
    this->X *= other;
    this->Y *= other;
  }

  inline void operator/=(const Vector2F& other)
  {
    this->X /= other.X;
    this->Y /= other.Y;
  }

  inline void operator/=(const float other)
  {
    this->X /= other;
    this->Y /= other;
  }

  inline bool operator==(const Vector2F& other)
  {
    return this->X == other.X && this->Y == other.Y;
  }

  inline bool operator!=(const Vector2F& other)
  {
    return this->X != other.X || this->Y != other.Y;
  }
#pragma endregion
};

inline static Vector2F ToVector2F(Vector2 other)
{
  return Vector2F{ (float)other.X, (float)other.Y };
}

inline static Vector2 ToVector2(Vector2F other)
{
  return Vector2{ (int)other.X, (int)other.Y };
}

struct Rect
{
  int X, Y, W, H;
#pragma region operator
  inline Rect operator+(const Rect& other)
  {
    return{ this->X + other.X, this->Y + other.Y, this->W + other.W, this->H + other.H };
  }

  inline Rect operator+(const int other)
  {
    return{ this->X + other, this->Y + other, this->W + other, this->H + other };
  }

  inline Rect operator-(const Rect& other)
  {
    return{ this->X - other.X, this->Y - other.Y, this->W - other.W, this->H - other.H };
  }

  inline Rect operator-(const int other)
  {
    return{ this->X - other, this->Y - other, this->W - other, this->H - other };
  }

  inline Rect operator*(const Rect& other)
  {
    return{ this->X * other.X, this->Y * other.Y, this->W * other.W, this->H * other.H };
  }

  inline Rect operator*(const int other)
  {
    return{ this->X * other, this->Y * other, this->W * other, this->H * other };
  }

  inline Rect operator/(const Rect& other)
  {
    return{ this->X / other.X, this->Y / other.Y, this->W / other.W, this->H / other.H };
  }

  inline Rect operator/(const int other)
  {
    return{ this->X / other, this->Y / other, this->W / other, this->H / other };
  }

  inline void operator+=(const Rect& other)
  {
    this->X += other.X;
    this->Y += other.Y;
    this->W += other.W;
    this->H += other.H;
  }

  inline void operator+=(const int other)
  {
    this->X += other;
    this->Y += other;
    this->W += other;
    this->H += other;
  }

  inline void operator-=(const Rect& other)
  {
    this->X -= other.X;
    this->Y -= other.Y;
    this->W -= other.W;
    this->H -= other.H;
  }

  inline void operator-=(const int other)
  {
    this->X -= other;
    this->Y -= other;
    this->W -= other;
    this->H -= other;
  }

  inline void operator*=(const Rect& other)
  {
    this->X *= other.X;
    this->Y *= other.Y;
    this->W *= other.W;
    this->H *= other.H;
  }

  inline void operator*=(const int other)
  {
    this->X *= other;
    this->Y *= other;
    this->W *= other;
    this->H *= other;
  }

  inline void operator/=(const Rect& other)
  {
    this->X /= other.X;
    this->Y /= other.Y;
    this->W /= other.W;
    this->H /= other.H;
  }

  inline void operator/=(const int other)
  {
    this->X /= other;
    this->Y /= other;
    this->W /= other;
    this->H /= other;
  }
#pragma endregion
};

struct RectF
{
  float X, Y, W, H;
#pragma region operator
  inline RectF operator+(const RectF& other)
  {
    return{ this->X + other.X, this->Y + other.Y, this->W + other.W, this->H + other.H };
  }

  inline RectF operator+(const int other)
  {
    return{ this->X + other, this->Y + other, this->W + other, this->H + other };
  }

  inline RectF operator-(const RectF& other)
  {
    return{ this->X - other.X, this->Y - other.Y, this->W - other.W, this->H - other.H };
  }

  inline RectF operator-(const int other)
  {
    return{ this->X - other, this->Y - other, this->W - other, this->H - other };
  }

  inline RectF operator*(const RectF& other)
  {
    return{ this->X * other.X, this->Y * other.Y, this->W * other.W, this->H * other.H };
  }

  inline RectF operator*(const int other)
  {
    return{ this->X * other, this->Y * other, this->W * other, this->H * other };
  }

  inline RectF operator/(const RectF& other)
  {
    return{ this->X / other.X, this->Y / other.Y, this->W / other.W, this->H / other.H };
  }

  inline RectF operator/(const int other)
  {
    return{ this->X / other, this->Y / other, this->W / other, this->H / other };
  }

  inline void operator+=(const RectF& other)
  {
    this->X += other.X;
    this->Y += other.Y;
    this->W += other.W;
    this->H += other.H;
  }

  inline void operator+=(const int other)
  {
    this->X += other;
    this->Y += other;
    this->W += other;
    this->H += other;
  }

  inline void operator-=(const RectF& other)
  {
    this->X -= other.X;
    this->Y -= other.Y;
    this->W -= other.W;
    this->H -= other.H;
  }

  inline void operator-=(const int other)
  {
    this->X -= other;
    this->Y -= other;
    this->W -= other;
    this->H -= other;
  }

  inline void operator*=(const RectF& other)
  {
    this->X *= other.X;
    this->Y *= other.Y;
    this->W *= other.W;
    this->H *= other.H;
  }

  inline void operator*=(const int other)
  {
    this->X *= other;
    this->Y *= other;
    this->W *= other;
    this->H *= other;
  }

  inline void operator/=(const RectF& other)
  {
    this->X /= other.X;
    this->Y /= other.Y;
    this->W /= other.W;
    this->H /= other.H;
  }

  inline void operator/=(const int other)
  {
    this->X /= other;
    this->Y /= other;
    this->W /= other;
    this->H /= other;
  }
#pragma endregion
};
