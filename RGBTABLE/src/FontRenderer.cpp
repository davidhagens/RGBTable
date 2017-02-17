#include "FontRenderer.h"

FontRenderer::FontRenderer(const char * path)
{
  this->img = new RenderImage();
  this->font = new TTF::TrueType(path);
}

FontRenderer::~FontRenderer()
{
  if (this->img != nullptr) delete this->img;
  if (this->font != nullptr) delete this->font;
}

int8_t FontRenderer::LoadFont()
{
  int8_t ret;
  if ((ret = this->font->Load()))
  {
    return ret;
  }
  //todo anpassen sodass die größe auf exakt 18 pixel auf Y entspricht
  this->scale = 18.0f / (this->font->GetHeader().yMax - this->font->GetHeader().yMin);//this->font->GetHeader().unitsPerEM;
  return 0;
}

uint16_t FontRenderer::GetGlyphCount()
{
  return this->font->GetGlyphCount();
}

void FontRenderer::DrawLetter(const uint8_t letter, Vector2 pos, RGB color)
{
  TTF::TrueTypeGlyph* glyph = this->font->GetGlyph(letter);

  int point = 0;
  int contour = 0;
  bool first = true;
  Vector2F start = { 0,0 };
  Vector2F current = { 0,0 };
  while (point < glyph->PointCount())
  {
    Vector2F next = ToVector2F(glyph->At(point));
    //shift the character to fit in an positive space TODO: optimize without function call
    next.X -= this->font->GetHeader().xMin;
    next.Y -= this->font->GetHeader().yMin;
    //scale the next point to the current scaling
    next *= this->scale;
    //flip on horizontal cause the font's origin is lower left but our's is upper left
    next = { next.X, 18 - next.Y };
    if (!first)
    {
      this->img->DrawLine(ToVector2(current) + pos, ToVector2(next) + pos, color);
      //renderer->DrawLine(ToVector2(current) + pos, ToVector2(next) + pos, color);
    }
    else
    {
      start = next;
      first = false;
    }
    current = next;
    if (point == glyph->ContourAt(contour)) //current point is the last point in the contour, so the next one starts a new contour
    {
      //draw a line back to the start point
      this->img->DrawLine(ToVector2(current) + pos, ToVector2(start) + pos, color);
      ++contour;
      first = true;
    }
    ++point;
  }
}

void FontRenderer::Show(RenderImage* renderer)
{
  renderer->DrawRenderImage(this->img);
}

void FontRenderer::Clear()
{
  this->img->Clear();
}
