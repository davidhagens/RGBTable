#pragma once
#include "Math.hpp"
#include <inttypes.h>
#include "Bitmap.h"
#include "RGB.hpp"
#include "Shape.h"

#define LED_W 36
#define LED_H 18
#define LED_COUNT LED_W * LED_H
#define LED_S0_COUNT LED_W * 10 //first 10 rows, the actual led matrix is powered by two Arduino UNO
#define LED_S1_COUNT LED_W * 8 //last 8 rows
#define LED_BYTES LED_COUNT * 3 //3 bytes per pixel (r,g,b) * 648 (LED_COUNT)
#define LED_S0_BYTES LED_S0_COUNT * 3 //bytes used for the first 10 rows
#define LED_S1_BYTES LED_S1_COUNT * 3 //bytes used for the last 8 rows
//override modes to set a bitmap or a color
#define OVERRIDE_MODE_ALL 0x00
#define OVERRIDE_MODE_BLACK_AS_ALPHA 0x01
#define OVERRIDE_MODE_MERGE_ADD 0x02
#define OVERRIDE_MODE_MERGE_MULTIPLY 0x03
#define OVERRIDE_MODE_MERGE_MULTIPLY_AND_AVERAGE 0x04

//some RGB values for better readability
#define COLOR_BLACK   RGB{0,0,0}
#define COLOR_WHITE   RGB{255,255,255}
#define COLOR_RED     RGB{255,0,0}
#define COLOR_GREEN   RGB{0,255,0}
#define COLOR_BLUE    RGB{0,0,255}
#define COLOR_YELLOW  RGB{255,255,0}
#define COLOR_CYAN    RGB{0,255,255}
#define COLOR_MAGENTA RGB{255,0,255}
#define COLOR_ORANGE  RGB{255,165,0}

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
  void DrawLine(Vector2 start, Vector2 end, const RGB color, const uint8_t overrideMode = 0x00);
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