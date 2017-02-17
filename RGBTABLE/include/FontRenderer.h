#pragma once
#include "RenderImage.h"
#include "TrueType.h"
#include "RenderImage.h"

class FontRenderer
{
private:
  TTF::TrueType* font;
  RenderImage* img;
  float scale;
public:
  FontRenderer(const char* path);
  ~FontRenderer();

  int8_t LoadFont();
  uint16_t GetGlyphCount();
  void DrawLetter(const uint8_t letter, Vector2 pos, RGB color);

  void Show(RenderImage* renderer);
  void Clear();
};