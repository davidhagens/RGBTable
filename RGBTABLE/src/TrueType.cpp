#include "TrueType.h"
#define GetTable(tag) TTF::GetTrueTypetable(tag, this->tables, this->general.numTables)

const TTF::TrueTypeHeader& TTF::TrueType::GetHeader()
{
  return this->header;
}

TTF::TrueTypeGlyph* TTF::TrueType::GetGlyph(uint8_t glyphIndex)
{
  //TODO: get the actual glyphIndex base on the CMAP table
  if (glyphIndex >= this->glyphCount)
  {
    return this->glyphs[0];
  }
  return this->glyphs[glyphIndex];
}

uint16_t TTF::TrueType::GetGlyphCount()
{
  return this->glyphCount;
}

TTF::TrueType::TrueType(const char * path)
{
  this->fileReader = new ByteOrderSwappingBinaryFileReader(path);
}

TTF::TrueType::~TrueType()
{
  if (this->tables != nullptr)
  {
    delete[] this->tables;
  }
  if (this->glyphs != nullptr)
  {
    for (size_t i = 0; i < this->glyphCount; i++)
    {
      delete this->glyphs[i];
    }
    delete[] this->glyphs;
  }
  if (this->fileReader != nullptr)
  {
    delete this->fileReader;
  }
  if (this->loca != nullptr)
  {
    delete this->loca;
  }
}

int8_t TTF::TrueType::Load()
{
  if (!this->fileReader->ReadResult())
  {
    return 1;
  }

  //read the offset table (described here: https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6.html)
  ReadTrueTypeGeneral(this->fileReader, this->general);
  //read table information
  this->tables = new TrueTypeTable[this->general.numTables];
  for (size_t i = 0; i < this->general.numTables; i++)
  {
    ReadTrueTypeTable(this->fileReader, this->tables[i]);
    //at this point we could calculate the tables checksum, 
    //but we just asume that the file will be okay... maybe we will do this in the future
  }
  //read header
  this->fileReader->Seek(GetTable("head")->offset);
  ReadTrueTypeHeader(this->fileReader, this->header);

  //Get glyphcount (+4 because the first 4 byte in the maxp table 
  //  is a fixed version number [https://developer.apple.com/fonts/TrueType-Reference-Manual/RM06/Chap6maxp.html])
  //We will just ignore all other values in this table
  this->fileReader->Seek(GetTable("maxp")->offset + 4);
  this->glyphCount = this->fileReader->ReadUint16();

  //read in the loca table
  this->fileReader->Seek(GetTable("loca")->offset);
  this->loca = new TrueTypeLocaTable(this->fileReader, this->glyphCount, this->header.indexToLocFormat);

  //read in the actual glyphs
  this->glyphs = new TrueTypeGlyph*[this->glyphCount];
  uint32_t glyfOffset = GetTable("glyf")->offset;
  for (size_t i = 0; i < this->glyphCount; i++)
  {
    this->fileReader->Seek(glyfOffset + this->loca->GetOffset(static_cast<uint16_t>(i)));
    this->glyphs[i] = new TrueTypeGlyph(this->fileReader, this->header);
  }

  //TODO: read in the CMAP table to get the actual glyph index on base of a char (it's not ASCII nor Unicode mapping)

  //we don't need the fileReader anymore since we read in every thing we need, so we call it's destructor (it will delete the file data array)
  delete this->fileReader;
  this->fileReader = nullptr;
  return 0;
}
#undef GetTable