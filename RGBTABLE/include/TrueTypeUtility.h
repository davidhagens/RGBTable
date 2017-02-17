#pragma once
#include "Math.hpp"
#include "BinaryFileReader.h"
#include <vector>

namespace TTF
{
  enum GlyphType
  {
    simple,
    compound
  };

  typedef int64_t longDateTime;
  typedef int16_t fword;
  typedef uint16_t ufword;

  //contains general information provided by the offset table
  struct TrueTypeGeneral
  {
    uint32_t scalerType;
    uint16_t numTables;
    uint16_t searchRange;
    uint16_t entrySelector;
    uint16_t rangeShift;
  };

  struct TrueTypeTable
  {
    char tag[4];
    uint32_t checksum;
    uint32_t offset;
    uint32_t length;
  };

  //true type header defined here: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6head.html 
  struct TrueTypeHeader
  {
    uint32_t version;
    uint32_t fontRevision;
    uint32_t checkSumAdjustment;
    uint32_t magicNumber;
    uint16_t flags;
    uint16_t unitsPerEM;
    longDateTime created;
    longDateTime modified;
    fword xMin;
    fword yMin;
    fword xMax;
    fword yMax;
    uint16_t macStyle;
    uint16_t lowestRecPPEM;
    int16_t fontDirectionHint;
    int16_t indexToLocFormat;
    int16_t glyphDataFormat;
  };

  //searches for the table with the specified tag and returns it
  TrueTypeTable* GetTrueTypetable(const char* tag, TrueTypeTable* tables, uint16_t numTables);

  struct TrueTypeGlyphHeader
  {
    int16_t numberOfContours;
    fword xMin;
    fword yMin;
    fword xMax;
    fword yMax;
  };

  void ReadTrueTypeTable(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeTable& table);
  void ReadTrueTypeHeader(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeHeader& header);
  void ReadTrueTypeGeneral(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeGeneral& ttgeneral);

  //flag prototypes defined here: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6glyf.html
#define TRUETYPEFLAG_ONCURVE 0x01
#define TRUETYPEFLAG_XISBYTE 0x02
#define TRUETYPEFLAG_YISBYTE 0x04
#define TRUETYPEFLAG_REPEAT  0x08
#define TRUETYPEFLAG_XDELTA  0x10
#define TRUETYPEFLAG_YDELTA  0x20

  class TrueTypeGlyph
  {
  private:
    TrueTypeGlyphHeader header;
    GlyphType type;
    //sicne the only flag we need outside of loading is OnCurve and a std::vector<bool> is a bit array, we use it to save a lot of space.
    std::vector<bool> onCurve;
    Vector2* points;
    uint16_t* contourEnds;
    uint16_t pointCount;

    void ReadCompoundGlyph(ByteOrderSwappingBinaryFileReader* fileReader);
    void ReadSimpleGlyph(ByteOrderSwappingBinaryFileReader* fileReader);
    void ReadCoords(ByteOrderSwappingBinaryFileReader* fileReader, uint8_t* flags, uint8_t axis, const uint8_t ISBYTE, const uint8_t DELTA);

  public:
    TrueTypeGlyph();
    TrueTypeGlyph(ByteOrderSwappingBinaryFileReader* fileReader, TrueTypeHeader& header);
    ~TrueTypeGlyph();

    GlyphType Type();
    uint16_t ContourAt(uint16_t index);
    uint16_t ContourCount();
    Vector2 At(uint16_t index);
    uint16_t PointCount();
    bool OnCurve(uint16_t index);
  };

  //the TrueType Table with the offsets to the actual glyphs
  class TrueTypeLocaTable
  {
  private:
    uint32_t* offsets;
    uint16_t glyphCount;
  public:
    TrueTypeLocaTable(ByteOrderSwappingBinaryFileReader* fileReader, uint16_t glyphCount, int16_t locFormat);
    ~TrueTypeLocaTable();

    uint32_t GetOffset(uint16_t glyphIndex);
  };
}