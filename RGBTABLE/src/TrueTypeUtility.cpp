#include "TrueTypeUtility.h"
#include <cstring>

TTF::TrueTypeTable* TTF::GetTrueTypetable(const char * tag, TrueTypeTable * tables, uint16_t numTables)
{
  for (int i = 0; i < numTables; i++)
  {
    if (strncmp(tables[i].tag, tag, 4) == 0)
      return &tables[i];
  }
  return nullptr;
}

#pragma region Reader

void TTF::ReadTrueTypeTable(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeTable & table)
{
  for (size_t i = 0; i < 4; i++)
  {
    table.tag[i] = fileReader->ReadUint8();
  }
  table.checksum = fileReader->ReadUint32();
  table.offset = fileReader->ReadUint32();
  table.length = fileReader->ReadUint32();
}

void TTF::ReadTrueTypeHeader(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeHeader & header)
{
  header.version = fileReader->ReadUint32();
  header.fontRevision = fileReader->ReadUint32();
  header.checkSumAdjustment = fileReader->ReadUint32();
  header.magicNumber = fileReader->ReadUint32();
  header.flags = fileReader->ReadUint16();
  header.unitsPerEM = fileReader->ReadUint16();
  header.created = fileReader->ReadUint64();
  header.modified = fileReader->ReadUint64();
  header.xMin = fileReader->ReadInt16();
  header.yMin = fileReader->ReadInt16();
  header.xMax = fileReader->ReadInt16();
  header.yMax = fileReader->ReadInt16();
  header.macStyle = fileReader->ReadUint16();
  header.lowestRecPPEM = fileReader->ReadUint16();
  header.fontDirectionHint = fileReader->ReadInt16();
  header.indexToLocFormat = fileReader->ReadInt16();
  header.glyphDataFormat = fileReader->ReadInt16();
}

void TTF::ReadTrueTypeGeneral(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeGeneral & general)
{
  general.scalerType = fileReader->ReadUint32();
  general.numTables = fileReader->ReadInt16();
  general.searchRange = fileReader->ReadUint16();
  general.entrySelector = fileReader->ReadUint16();
  general.rangeShift = fileReader->ReadUint16();
}
#pragma endregion

#pragma region Glyph
void TTF::TrueTypeGlyph::ReadCompoundGlyph(ByteOrderSwappingBinaryFileReader* fileReader)
{
  this->type = TTF::compound;
}

void TTF::TrueTypeGlyph::ReadSimpleGlyph(ByteOrderSwappingBinaryFileReader* fileReader)
{
  this->type = TTF::simple;
  this->contourEnds = new uint16_t[this->header.numberOfContours];
  for (uint16_t i = 0; i < this->header.numberOfContours; i++)
  {
    this->contourEnds[i] = fileReader->ReadUint16();
  }
  //skip the instruction bytes
  fileReader->SeekCurrent(fileReader->ReadUint16());

  //since we have no contours we also have no points
  if (this->header.numberOfContours == 0)
  {
    return;
  }

  //the highest value inside of contourEnds is the highest point index, so this index + 1 is our pointCount
  this->pointCount = Max(this->contourEnds, this->header.numberOfContours) + 1;

  //read flags
  uint8_t* flags = new uint8_t[this->pointCount];
  this->onCurve.resize(this->pointCount);
  this->points = new Vector2[this->pointCount];
  for (uint16_t i = 0; i < this->pointCount; i++)
  {
    uint8_t flag = fileReader->ReadUint8();
    flags[i] = flag;
    this->onCurve[i] = flag & TRUETYPEFLAG_ONCURVE;
    //repeat the same flag over rCount, rCount is saved in the next byte
    if (flag & TRUETYPEFLAG_REPEAT)
    {
      uint8_t rCount = fileReader->ReadUint8();
      //save a temporary I (+1 because the current flag is already set)
      uint16_t itmp = i + 1;
      //since we set all flags between i and i + rCount, we skip i to the next non repeat index
      i += rCount;
      //set all the repeated flags
      for (uint8_t j = 0; j < rCount; j++)
      {
        flags[itmp + j] = flag;
        this->onCurve[itmp + j] = flag & TRUETYPEFLAG_ONCURVE;
      }
    }
  }
  //read in the actual coords (0 represents the X axis, 1 the Y axis)
  this->ReadCoords(fileReader, flags, 0, TRUETYPEFLAG_XISBYTE, TRUETYPEFLAG_XDELTA);
  this->ReadCoords(fileReader, flags, 1, TRUETYPEFLAG_YISBYTE, TRUETYPEFLAG_YDELTA);
  delete[] flags;
}

void TTF::TrueTypeGlyph::ReadCoords(ByteOrderSwappingBinaryFileReader* fileReader, uint8_t* flags, uint8_t axis, const uint8_t ISBYTE, const uint8_t DELTA)
{
  int16_t val = 0;
  for (uint16_t i = 0; i < this->pointCount; i++)
  {
    //get the flag for the current point
    uint8_t flag = flags[i];
    if (flag & ISBYTE) //the point value is saved as uint8
    {
      //if the DELTA flag is set it's a positive value, else it's negative
      val += (flag & DELTA) ? fileReader->ReadUint8() : -fileReader->ReadUint8();
    }
    //when the ISBYTE flag isn't set and the DELTA flag isn't set, the point is saved as int16, so we NOT the flag and check the DELTA bit
    else if (~flag & DELTA)//the point is saved as int16
    {
      val += fileReader->ReadInt16();
    }
    //else: value isn't changed since last time
    //when we are in debug mode we print the value and it's data type and if the current flag was repeated or not
#if _DEBUG
    if (val < (axis == 0 ? this->header.xMin : this->header.yMin))
    {
      printf("value %i of point %i on axis %s is lower than min %i ", val, i, axis == 0 ? "X" : "Y", axis == 0 ? this->header.xMin : this->header.yMin);
      printf("it was a %s and the flag was %s\n", ~flag & DELTA ? "int16" : "uint8", flag & TRUETYPEFLAG_REPEAT ? "repeated" : "not repeated");
    }
    if (val >(axis == 0 ? this->header.xMax : this->header.yMax))
    {
      printf("value %i of point %i on axis %s is higher than max %i ", val, i, axis == 0 ? "X" : "Y", axis == 0 ? this->header.xMax : this->header.yMax);
      printf("it was a %s and the flag was %s\n", ~flag & DELTA ? "int16" : "uint8", flag & TRUETYPEFLAG_REPEAT ? "repeated" : "not repeated");
    }
#endif
    //the vector2 struct contains to int's, first one is X and second is Y, so we can cast the point array
    //and interpret it as an int array where we can set the value at index AXIS
    reinterpret_cast<int*>(&this->points[i])[axis] = val;
  }
}

TTF::TrueTypeGlyph::TrueTypeGlyph()
{
}

TTF::TrueTypeGlyph::TrueTypeGlyph(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeHeader& header)
{
  this->header.numberOfContours = fileReader->ReadInt16();
  this->header.xMin = fileReader->ReadInt16();
  this->header.yMin = fileReader->ReadInt16();
  this->header.xMax = fileReader->ReadInt16();
  this->header.yMax = fileReader->ReadInt16();

  if (this->header.xMin < header.xMin || this->header.xMax > header.xMax)
  {
    printf("Xmin is lower than allowed xmin or xmax is higher than allowed xmax");
  }
  if (this->header.yMin < header.yMin || this->header.yMax > header.yMax)
  {
    printf("yMin is lower than allowed or yMax is higher than allowed");
  }

  if (this->header.numberOfContours == -1)
    this->ReadCompoundGlyph(fileReader);
  else
    this->ReadSimpleGlyph(fileReader);
}

TTF::TrueTypeGlyph::~TrueTypeGlyph()
{
  if (this->points != nullptr) delete[] this->points;
  if (this->contourEnds != nullptr) delete[] this->contourEnds;
}

TTF::GlyphType TTF::TrueTypeGlyph::Type()
{
  return this->type;
}

uint16_t TTF::TrueTypeGlyph::ContourAt(uint16_t index)
{
  if (index < this->header.numberOfContours)
  {
    return this->contourEnds[index];
  }
  return 0;
}

uint16_t TTF::TrueTypeGlyph::ContourCount()
{
  return this->header.numberOfContours;
}

Vector2 TTF::TrueTypeGlyph::At(uint16_t index)
{
  if (index < this->pointCount)
    return this->points[index];
  return{ 0,0 };
}

uint16_t TTF::TrueTypeGlyph::PointCount()
{
  return this->pointCount;
}

bool TTF::TrueTypeGlyph::OnCurve(uint16_t index)
{
  return this->onCurve.at(index);
}
#pragma endregion

#pragma region LOCA
TTF::TrueTypeLocaTable::TrueTypeLocaTable(ByteOrderSwappingBinaryFileReader* fileReader, uint16_t glyphCount, int16_t locFormat)
{
  this->glyphCount = glyphCount + 1;
  this->offsets = new uint32_t[this->glyphCount];
  if (locFormat == 0) //short offsets
  {
    for (uint16_t i = 0; i < this->glyphCount; i++)
    {
      //the glyph offset is saved as uint16 divided by 2
      this->offsets[i] = fileReader->ReadUint16() * 2;
    }
  }
  else //long offsets
  {
    for (uint16_t i = 0; i < this->glyphCount; i++)
    {
      //the glyph offset is saved as uint32
      this->offsets[i] = fileReader->ReadUint32();
    }
  }
}

TTF::TrueTypeLocaTable::~TrueTypeLocaTable()
{
  if (this->offsets != nullptr) delete[] this->offsets;
}

uint32_t TTF::TrueTypeLocaTable::GetOffset(uint16_t glyphIndex)
{
  if (glyphIndex < this->glyphCount)
    return this->offsets[glyphIndex];
  return 0;
}
#pragma endregion
