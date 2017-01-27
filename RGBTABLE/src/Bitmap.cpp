#include "Bitmap.h"
#include "LEDMatrix.h"

Bitmap::Bitmap(const char * path)
{
  //todo move this to another function with return value for errors
  BitmapHeader header = { 0 };
  FILE* file = nullptr;
  fopen_s(&file, path, "rb");
  if (file == nullptr)
  {
    printf("failed to open file %s", path);
    return;
  }
  //get file size and read file
  fseek(file, 0, SEEK_END);
  auto bytes = ftell(file);
  auto info = new char[bytes];
  fseek(file, 0, SEEK_SET);
  fread(info, bytes, 1, file);
  fclose(file);

  //read data into bmp header
  header.FileSize = *reinterpret_cast<int*>(&info[2]);
  header.ImageDataOffset = *reinterpret_cast<int*>(&info[10]);
  header.Width = *reinterpret_cast<int*>(&info[18]);
  header.Height = *reinterpret_cast<int*>(&info[22]);
  header.BPP = *reinterpret_cast<short*>(&info[28]);

  //check if the header data is correct
  if (header.Width != LED_W || header.Height != LED_H || header.BPP != 24)
  {
    printf("file has the wrong format, format should be: imgsize 36 x 18; BPP: 24");
    delete[] info;
    return;
  }

  this->w = header.Width;
  this->h = header.Height;

  this->data = new uint8_t[LED_BYTES];
  uint8_t* d = reinterpret_cast<uint8_t*>(this->data); //just for easier calculations on the data array

  //switch pixels to RGB format with origin in the upper left corner
  for (int y = 0; y < this->h; y++)
  {
    for (int x = 0; x < this->w; x++)
    {
      int idx = (y * this->w + x) * 3; //data index
      int idx2 = ((this->h - y - 1) * this->w + x) * 3 + header.ImageDataOffset; //info index
      //swap from the Bitmap's BGR format to the internal used RGB format
      d[idx] = info[idx2 + 2];
      d[idx + 1] = info[idx2 + 1];
      d[idx + 2] = info[idx2];
    }
  }
  delete[] info;
}

Bitmap::~Bitmap()
{
  if (this->data != nullptr)
  {
    delete[] this->data;
  }
}

const int Bitmap::Width()
{
  return this->w;
}

const int Bitmap::Height()
{
  return this->h;
}

const void * Bitmap::Data()
{
  return this->data;
}
