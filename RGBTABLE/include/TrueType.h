#pragma once
#include <cstdio>
#include <inttypes.h>
#include "TrueTypeUtility.h"
#include "BinaryFileReader.h"

//this is inspired by http://stevehanov.ca/blog/index.php?id=143 and based on the true type documentation by Apple:
//https://developer.apple.com/fonts/TrueType-Reference-Manual/
//I refer a few times to actual links from Apple's documentation

/*
Error types of Load():
0x01: File not opened




*/
namespace TTF
{
  class TrueType
  {
  private:
    ByteOrderSwappingBinaryFileReader* fileReader;
    TrueTypeGeneral general;
    TrueTypeHeader header;
    TrueTypeLocaTable* loca;
    TrueTypeTable* tables;
    uint16_t glyphCount;
    TrueTypeGlyph** glyphs;

  public:
    TrueType(const char* path);
    ~TrueType();

    const TrueTypeHeader& GetHeader();
    TrueTypeGlyph* GetGlyph(uint8_t glyphIndex);
    uint16_t GetGlyphCount();

    int8_t Load();

  };
}