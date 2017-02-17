#include "RenderImage.h"

uint16_t RenderImage::GetPixelIdx(const uint16_t idx)
{
  //so the LED Table has the following layout:
  /*
  0  1  2  3  4  5  6  7  8  9  10
  21 20 19 18 17 16 15 14 13 12 11
  22 23 24 25 26 27 28 29 30 31 32
  ...

  */
  //in the future this function should also take care of mirroring and other stuff
  uint16_t y = idx / LED_W;
  uint16_t x = idx % LED_W;
  if (y % 2 == 1) return (y * LED_W) + LED_W - x - 1;
  return idx;
}

uint16_t RenderImage::GetPixelIdx(const Vector2 pos)
{
  //same as the function above
  if (pos.Y % 2 == 1) return (pos.Y * LED_W) + LED_W - pos.X - 1;
  return (pos.Y * LED_W) + pos.X;
}

RenderImage::RenderImage()
{
  this->img = new uint8_t[LED_BYTES];
  memset(this->img, 0, LED_BYTES);
}

RenderImage::~RenderImage()
{
  delete[] this->img;
}

void RenderImage::Clear()
{
  memset(this->img, 0, LED_BYTES);
}

void RenderImage::DrawPixel(const uint16_t idx, const RGB color, const uint8_t overrideMode)
{
  if (idx > LED_COUNT) return; //we can't draw a pixel if it's not inside our LED_COUNT
  switch (overrideMode)
  {
  case OVERRIDE_MODE_ALL:
    //simple memcpy, we don't need to check the data inside the pixel buffer
    memcpy_s(this->img + (this->GetPixelIdx(idx) * 3), 3, &color, 3);
    break;
  case OVERRIDE_MODE_BLACK_AS_ALPHA:
    if (color.r + color.g + color.b > 0) //since we only set one color we can return if this color is black
    {
      memcpy_s(this->img + (this->GetPixelIdx(idx) * 3), 3, &color, 3);
    }
    break;
  case OVERRIDE_MODE_MERGE_ADD:
  {
    uint16_t _idx = this->GetPixelIdx(idx);
    this->img[_idx * 3] += color.r;
    this->img[_idx * 3 + 1] += color.g;
    this->img[_idx * 3 + 2] += color.b;
  }
  break;
  case OVERRIDE_MODE_MERGE_MULTIPLY:
  {
    uint16_t _idx = this->GetPixelIdx(idx);
    this->img[_idx * 3] *= color.r;
    this->img[_idx * 3 + 1] *= color.g;
    this->img[_idx * 3 + 2] *= color.b;
  }
  break;
  case OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE:
  {
    uint16_t _idx = this->GetPixelIdx(idx);
    (this->img[_idx * 3] *= color.r) /= 2;
    (this->img[_idx * 3 + 1] *= color.g) /= 2;
    (this->img[_idx * 3 + 2] *= color.b) /= 2;
  }
  break;
  }
}

void RenderImage::DrawPixel(const Vector2 point, const RGB color, const uint8_t overrideMode)
{
  if (point.X < 0 || point.X >= LED_W || point.Y < 0 || point.Y >= LED_H) return; //pixel is not inside the led matrix
  switch (overrideMode)
  {
  case OVERRIDE_MODE_ALL:
    memcpy_s(this->img + (this->GetPixelIdx(point) * 3), 3, &color, 3);
    break;
  case OVERRIDE_MODE_BLACK_AS_ALPHA:
    if (color.r + color.g + color.b > 0) //since we only set one color we can return if this color is black
    {
      memcpy_s(this->img + (this->GetPixelIdx(point) * 3), 3, &color, 3);
    }
    break;
  case OVERRIDE_MODE_MERGE_ADD:
  {
    uint16_t _idx = this->GetPixelIdx(point);
    this->img[_idx * 3] += color.r;
    this->img[_idx * 3 + 1] += color.g;
    this->img[_idx * 3 + 2] += color.b;
  }
  break;
  case OVERRIDE_MODE_MERGE_MULTIPLY:
  {
    uint16_t _idx = this->GetPixelIdx(point);
    this->img[_idx * 3] *= color.r;
    this->img[_idx * 3 + 1] *= color.g;
    this->img[_idx * 3 + 2] *= color.b;
  }
  break;
  case OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE:
  {
    uint16_t _idx = this->GetPixelIdx(point);
    (this->img[_idx * 3] *= color.r) /= 2;
    (this->img[_idx * 3 + 1] *= color.g) /= 2;
    (this->img[_idx * 3 + 2] *= color.b) /= 2;
  }
  break;
  }
}

void RenderImage::DrawPixel(const Pixel pixel, const uint8_t overrideMode)
{
  this->DrawPixel(pixel.pos, pixel.color, overrideMode);
}

void RenderImage::DrawPixel(const Pixel pixel, const RGB color, const uint8_t overrideMode)
{
  this->DrawPixel(pixel.pos, color, overrideMode);
}

void RenderImage::DrawPixels(const uint16_t startIdx, const uint16_t endIdx, const RGB color, const uint8_t overrideMode)
{
  switch (overrideMode)
  {
  case OVERRIDE_MODE_ALL:
    for (uint16_t i = startIdx; i < endIdx; i++)
    {
      memcpy_s(this->img + (this->GetPixelIdx(i) * 3), 3, &color, 3);
    }
    break;
  case OVERRIDE_MODE_BLACK_AS_ALPHA:
    if (color.r + color.g + color.b > 0) //since we only set one color we can return if this color is black (which actually wouldn't make sence...)
    {
      for (uint16_t i = startIdx; i < endIdx; i++)
      {
        memcpy_s(this->img + (this->GetPixelIdx(i) * 3), 3, &color, 3);
      }
    }
    break;
  case OVERRIDE_MODE_MERGE_ADD:
    for (uint16_t i = startIdx; i < endIdx; i++)
    {
      uint16_t idx = this->GetPixelIdx(i);
      this->img[idx * 3] += color.r;
      this->img[idx * 3 + 1] += color.g;
      this->img[idx * 3 + 2] += color.b;
    }
    break;
  case OVERRIDE_MODE_MERGE_MULTIPLY:
    for (uint16_t i = startIdx; i < endIdx; i++)
    {
      uint16_t idx = this->GetPixelIdx(i);
      this->img[idx * 3] *= color.r;
      this->img[idx * 3 + 1] *= color.g;
      this->img[idx * 3 + 2] *= color.b;
    }
    break;
  case OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE:
    for (uint16_t i = startIdx; i < endIdx; i++)
    {
      uint16_t idx = this->GetPixelIdx(i);
      (this->img[idx * 3] *= color.r) /= 2;
      (this->img[idx * 3 + 1] *= color.g) /= 2;
      (this->img[idx * 3 + 2] *= color.b) /= 2;
    }
    break;
  }
}

void RenderImage::FillRect(const Rect rect, const RGB color, const uint8_t overrideMode)
{
  for (int y = rect.Y; y < rect.H; y++)
  {
    for (int x = rect.X; x < rect.W; x++)
    {
      this->DrawPixel(Vector2{ x, y }, color, overrideMode);
    }
  }
}

void RenderImage::DrawRect(const Rect rect, const RGB color, const uint8_t overrideMode)
{
  this->DrawLine({ rect.X,          rect.Y }, { rect.X + rect.W, rect.Y }, color, overrideMode);
  this->DrawLine({ rect.X,          rect.Y }, { rect.X,          rect.Y + rect.H }, color, overrideMode);
  this->DrawLine({ rect.X + rect.W, rect.Y }, { rect.X + rect.W, rect.Y + rect.H }, color, overrideMode);
  this->DrawLine({ rect.X,          rect.Y + rect.H }, { rect.X + rect.W, rect.Y + rect.H }, color, overrideMode);
}

#define plot(x, y) this->DrawPixel(Vector2{x, y}, color, overrideMode)
#define line(x0, x1, y) this->DrawStraightX(y, x0, x1, color, overrideMode);
void RenderImage::FillCircle(const Vector2 point, const uint16_t radius, const RGB color, const uint8_t overrideMode)
{
  //Bresenham's circle (Midpoint Circle) algorithm from https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C
  //modified to fill circles

  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  plot(point.X, point.Y + radius);
  plot(point.X, point.Y - radius);
  line(point.X - radius, point.X + radius, point.Y);

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;
    line(point.X - x, point.X + x, point.Y + y);
    line(point.X - x, point.X + x, point.Y - y);
    line(point.X - y, point.X + y, point.Y + x);
    line(point.X - y, point.X + y, point.Y - x);
  }
}

void RenderImage::DrawCircle(const Vector2 point, const uint16_t radius, const RGB color, const uint8_t overrideMode)
{
  //Bresenham's circle (Midpoint Circle) algorithm from https://rosettacode.org/wiki/Bitmap/Midpoint_circle_algorithm#C

  int f = 1 - radius;
  int ddF_x = 0;
  int ddF_y = -2 * radius;
  int x = 0;
  int y = radius;

  plot(point.X, point.Y + radius);
  plot(point.X, point.Y - radius);
  plot(point.X + radius, point.Y);
  plot(point.X - radius, point.Y);

  while (x < y)
  {
    if (f >= 0)
    {
      y--;
      ddF_y += 2;
      f += ddF_y;
    }
    x++;
    ddF_x += 2;
    f += ddF_x + 1;
    plot(point.X + x, point.Y + y);
    plot(point.X - x, point.Y + y);
    plot(point.X + x, point.Y - y);
    plot(point.X - x, point.Y - y);
    plot(point.X + y, point.Y + x);
    plot(point.X - y, point.Y + x);
    plot(point.X + y, point.Y - x);
    plot(point.X - y, point.Y - x);
  }
}
#undef plot
#undef line

void RenderImage::DrawLine(Vector2 start, Vector2 end, const RGB color, const uint8_t overrideMode)
{
  //Bresenham's line algorithm from http://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C.2B.2B
  const bool steep = (fabs(end.Y - start.Y) > fabs(end.X - start.X));
  if (steep)
  {
    std::swap(start.X, start.Y);
    std::swap(end.X, end.Y);
  }

  if (start.X > end.X)
  {
    std::swap(start.X, end.X);
    std::swap(start.Y, end.Y);
  }

  const float dx = (const float)end.X - start.X;
  const float dy = fabs((float)end.Y - start.Y);

  float error = dx / 2.0f;
  const int ystep = (start.Y < end.Y) ? 1 : -1;
  int y = (int)start.Y;

  const int maxX = (int)end.X;

  for (int x = (int)start.X; x<maxX; x++)
  {
    if (steep)
    {
      this->DrawPixel(Vector2{ y, x }, color);
    }
    else
    {
      this->DrawPixel(Vector2{ x, y }, color);
    }

    error -= dy;
    if (error < 0)
    {
      y += ystep;
      error += dx;
    }
  }
}

void RenderImage::DrawStraightX(const uint16_t Y, const uint16_t X1, const uint16_t X2, const RGB color, const uint8_t overrideMode)
{
  for (uint16_t x = X1; x < X2; x++)
  {
    this->DrawPixel(Vector2{ x, Y }, color, overrideMode);
  }
}

void RenderImage::DrawStraightY(const uint16_t X, const uint16_t Y1, const uint16_t Y2, const RGB color, const uint8_t overrideMode)
{
  for (uint16_t y = Y1; y < Y2; y++)
  {
    this->DrawPixel(Vector2{ X, y }, color, overrideMode);
  }
}

void RenderImage::DrawShape(Shape * shape, const Vector2 pos, const uint8_t overrideMode)
{
  Pixel* pixels = nullptr;
  int c = shape->Get(&pixels);
  for (int i = 0; i < c; i++)
  {
    Pixel p(pixels[i]);
    p.pos += pos;
    this->DrawPixel(p, overrideMode);
  }
}

void RenderImage::DrawShape(Shape * shape, const Vector2 pos, const RGB color, const uint8_t overrideMode)
{
  Pixel* pixels = nullptr;
  int c = shape->Get(&pixels);
  for (int i = 0; i < c; i++)
  {
    Pixel p(pixels[i]);
    p.pos += pos;
    this->DrawPixel(p, color, overrideMode);
  }
}

void RenderImage::DrawBitmap(Bitmap * bitmap, const uint8_t overrideMode)
{
  uint8_t* bitmapData = (uint8_t*)bitmap->Data();
  switch (overrideMode)
  {
  case OVERRIDE_MODE_ALL:
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      uint16_t idx = i * 3;
      uint16_t idx2 = this->GetPixelIdx(i) * 3;
      this->img[idx2] = bitmapData[idx];
      this->img[idx2 + 1] = bitmapData[idx + 1];
      this->img[idx2 + 2] = bitmapData[idx + 2];
    }
    break;
  case OVERRIDE_MODE_BLACK_AS_ALPHA:
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      uint16_t idx2 = this->GetPixelIdx(i) * 3;
      uint16_t idx = i * 3;
      if (bitmapData[idx] + bitmapData[idx + 1] + bitmapData[idx + 2] != 0)
      {
        this->img[idx2] = bitmapData[idx];
        this->img[idx2 + 1] = bitmapData[idx + 1];
        this->img[idx2 + 2] = bitmapData[idx + 2];
      }
    }
    break;
  case OVERRIDE_MODE_MERGE_ADD:
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      uint16_t idx = i * 3;
      uint16_t idx2 = this->GetPixelIdx(i) * 3;
      this->img[idx2] += bitmapData[idx];
      this->img[idx2 + 1] += bitmapData[idx + 1];
      this->img[idx2 + 2] += bitmapData[idx + 2];
    }
    break;
  case OVERRIDE_MODE_MERGE_MULTIPLY:
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      uint16_t idx = i * 3;
      uint16_t idx2 = this->GetPixelIdx(i) * 3;
      this->img[idx2] *= bitmapData[idx];
      this->img[idx2 + 1] *= bitmapData[idx + 1];
      this->img[idx2 + 2] *= bitmapData[idx + 2];
    }
    break;
  case OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE:
    for (uint16_t i = 0; i < LED_COUNT; i++)
    {
      uint16_t idx = i * 3;
      uint16_t idx2 = this->GetPixelIdx(i) * 3;
      (this->img[idx2] *= bitmapData[idx]) /= 2;
      (this->img[idx2 + 1] *= bitmapData[idx + 1]) /= 2;
      (this->img[idx2 + 2] *= bitmapData[idx + 2]) /= 2;
    }
    break;
  }
}

void RenderImage::DrawRenderImage(RenderImage * image)
{
  memcpy_s(this->img, LED_BYTES, image->img, LED_BYTES);
}

RGB RenderImage::getPixelColor(uint16_t idx)
{
  idx = this->GetPixelIdx(idx) * 3;
  return{ this->img[idx], this->img[idx + 1], this->img[idx + 2] };
}

RGB RenderImage::getPixelColor(Vector2 point)
{
  uint16_t idx = this->GetPixelIdx(point) * 3;
  return{ this->img[idx], this->img[idx + 1], this->img[idx + 2] };
}
