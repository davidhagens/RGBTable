#pragma once
#include <stdio.h>
#include <inttypes.h>
#include "Math.hpp"

class ByteOrderSwappingBinaryFileReader
{
private:
  uint8_t* fileData;
  uint32_t filePointer;
  uint32_t fileSize;
  bool readResult;

public:
  ByteOrderSwappingBinaryFileReader(const char* path);
  ~ByteOrderSwappingBinaryFileReader();

  //Sets the internal file pointer to the given offset
  void Seek(uint32_t offset);
  //increments the internal file pointer by the given offset
  void SeekCurrent(uint32_t offset);
  uint32_t Tell();

  //returns the values and increments the file pointer to the next byte
  uint8_t  ReadUint8();
  uint16_t ReadUint16();
  uint32_t ReadUint32();
  uint64_t ReadUint64();
  int8_t ReadInt8();
  int16_t ReadInt16();
  int32_t ReadInt32();
  int64_t ReadInt64();

  bool ReadResult();
};
