#pragma once
#include <stdio.h>

struct BitmapHeader
{
  int FileSize;
  int ImageDataOffset;
  int Width;
  int Height;
  short BPP;
};

class Bitmap
{
private:
  //actual pixel data
  void* data;
  int w, h;

public:
  //loads a bitmap from the given path
  //todo: move the actual loading to an extra function with return value
  Bitmap(const char* path);
  ~Bitmap();

  const int Width();
  const int Height();
  const void* Data();
};