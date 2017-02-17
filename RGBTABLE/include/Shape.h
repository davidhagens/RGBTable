#pragma once
#include <vector>
#include "Math.h"
#include "RGB.hpp"
class Shape
{
private:
  //array of points which define this shape
  Pixel* points;
  //arraysize of points
  int count;
public:
  //creates an empty shape with the given length (warning: this can't be changed later on)
  Shape(const int count);
  ~Shape();

  //copies the fiven Pixel values to the shape's internal array
  bool Set(const Pixel* points, const int count);

  //returns the pixelcount and assignes the dereferenced points argument to the pixel array
  const int Get(Pixel** points);
  //returns the pixel count
  const int Count();
};