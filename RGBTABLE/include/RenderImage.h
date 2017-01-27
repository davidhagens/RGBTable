#pragma once
#include "LEDMatrix.h"

class RenderImage
{
protected:
  uint8_t* img;

  //calculate the actual pixel position within the strip of an index or a Vector2 position
  //more information about this is inside the function definition
  uint16_t GetPixelIdx(const uint16_t idx);
  uint16_t GetPixelIdx(const Vector2 pos);

public:
  RenderImage();
  virtual ~RenderImage();

  //clear the color buffer
  void Clear();

  //draws a pixel at the specified index, overrideMode is optional
  void DrawPixel(const uint16_t idx, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a pixel at the specified Point, overrideMode is optional
  void DrawPixel(const Vector2 point, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a pixel with it's custom color
  void DrawPixel(const Pixel pixel, const uint8_t overrideMode = 0x00);
  //draws a pixel with a given color, this will override the pixels custom color
  void DrawPixel(const Pixel pixel, const RGB color, const uint8_t overrideMode = 0x00);
  //draws all pixels from startIdx to endIdx, overrideMode is optional
  void DrawPixels(const uint16_t startIdx, const uint16_t endIdx, const RGB color, const uint8_t overrideMode = 0x00);

  //draws a filled rectangle, overrideMode is optional
  void FillRect(const Rect rect, const RGB color, const uint8_t overrideMode = 0x00);
  //draws an unfilled rectangle, overrideMode is optional
  void DrawRect(const Rect rect, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a filled circle, overrideMode is optional
  void FillCircle(const Vector2 point, const uint16_t radius, const RGB color, const uint8_t overrideMode = 0x00);
  //draws an unfilled circle, overrideMode is optional
  void DrawCircle(const Vector2 point, const uint16_t radius, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a line, overrideMode is optional
  void DrawLine(const Vector2 start, const Vector2 end, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a straight line in X direction
  void DrawStraightX(const uint16_t Y, const uint16_t X1, const uint16_t X2, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a straight line in Y direction
  void DrawStraightY(const uint16_t X, const uint16_t Y1, const uint16_t Y2, const RGB color, const uint8_t overrideMode = 0x00);

  //draws a shape at position
  void DrawShape(Shape* shape, const Vector2 pos, const uint8_t overrideMode = 0x00);
  //draws a shape at position with specific color (this will override the pixel's custom color)
  void DrawShape(Shape* shape, const Vector2 pos, const RGB color, const uint8_t overrideMode = 0x00);
  //draws a loaded bitmap image, overrideMode is optional
  void DrawBitmap(Bitmap* bitmap, const uint8_t overrideMode = 0x00);
  //draws another renderimage into this img buffer. this only supports overriding all pixels
  void DrawRenderImage(RenderImage* image);

  //returns the current RGB value in the pixel buffer at the given index or the given position
  RGB getPixelColor(const uint16_t idx);
  RGB getPixelColor(const Vector2 point);
};