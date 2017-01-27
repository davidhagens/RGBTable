#include "Shape.h"

Shape::Shape(int count)
{
  this->points = new Pixel[count];
  this->count = count;
}

Shape::~Shape()
{
  if (this->points != nullptr) delete[] this->points;
}

bool Shape::Set(const Pixel* points, const int count)
{
  if (this->count >= count)
  {
    //if we have enough space to copy, we copy the given pixels to our own pixel array
    memcpy_s(this->points, this->count * sizeof(Pixel), points, count * sizeof(Pixel));
    return true;
  }
  return false;
}

const int Shape::Get(Pixel ** points)
{
  if (points != nullptr)
  {
    *points = this->points;
  }
  return this->count;
}

const int Shape::Count()
{
  return this->count;
}
