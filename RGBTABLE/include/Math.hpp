#pragma once
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

  inline Vector2F operator+(const int other)
  {
    return{ this->X + other, this->Y + other };
  }

  inline Vector2F operator-(const Vector2F& other)
  {
    return{ this->X - other.X, this->Y - other.Y };
  }

  inline Vector2F operator-(const int other)
  {
    return{ this->X - other, this->Y - other };
  }

  inline Vector2F operator*(const Vector2F& other)
  {
    return{ this->X * other.X, this->Y * other.Y };
  }

  inline Vector2F operator*(const int other)
  {
    return{ this->X * other, this->Y * other };
  }

  inline Vector2F operator/(const Vector2F& other)
  {
    return{ this->X / other.X, this->Y / other.Y };
  }

  inline Vector2F operator/(const int other)
  {
    return{ this->X / other, this->Y / other };
  }

  inline void operator+=(const Vector2F& other)
  {
    this->X += other.X;
    this->Y += other.Y;
  }

  inline void operator+=(const int other)
  {
    this->X += other;
    this->Y += other;
  }

  inline void operator-=(const Vector2F& other)
  {
    this->X -= other.X;
    this->Y -= other.Y;
  }

  inline void operator-=(const int other)
  {
    this->X -= other;
    this->Y -= other;
  }

  inline void operator*=(const Vector2F& other)
  {
    this->X *= other.X;
    this->Y *= other.Y;
  }

  inline void operator*=(const int other)
  {
    this->X *= other;
    this->Y *= other;
  }

  inline void operator/=(const Vector2F& other)
  {
    this->X /= other.X;
    this->Y /= other.Y;
  }

  inline void operator/=(const int other)
  {
    this->X /= other;
    this->Y /= other;
  }
#pragma endregion
};

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