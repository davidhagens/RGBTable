#include "BinaryFileReader.h"

ByteOrderSwappingBinaryFileReader::ByteOrderSwappingBinaryFileReader(const char * path)
{
  FILE* file = nullptr;
  fopen_s(&file, path, "rb");
  if (file == nullptr)
  {
    readResult = false;
    return;
  }
  fseek(file, 0, SEEK_END);
  this->fileSize = ftell(file);
  this->fileData = new uint8_t[this->fileSize];
  fseek(file, 0, SEEK_SET);

  fread(this->fileData, this->fileSize, 1, file);
  fclose(file);
  readResult = true;
}

ByteOrderSwappingBinaryFileReader::~ByteOrderSwappingBinaryFileReader()
{
  if (this->fileData != nullptr)
  {
    delete[] this->fileData;
  }
}

void ByteOrderSwappingBinaryFileReader::Seek(uint32_t offset)
{
  this->filePointer = offset;
}

void ByteOrderSwappingBinaryFileReader::SeekCurrent(uint32_t offset)
{
  this->filePointer += offset;
}

uint32_t ByteOrderSwappingBinaryFileReader::Tell()
{
  return this->filePointer;
}

uint8_t ByteOrderSwappingBinaryFileReader::ReadUint8()
{
  return this->fileData[this->filePointer++];
}

uint16_t ByteOrderSwappingBinaryFileReader::ReadUint16()
{
  uint16_t ret = SwapByteOrder(*reinterpret_cast<uint16_t*>(this->fileData + this->filePointer));
  this->filePointer += 2;
  return ret;
}

uint32_t ByteOrderSwappingBinaryFileReader::ReadUint32()
{
  uint32_t ret = SwapByteOrder(*reinterpret_cast<uint32_t*>(this->fileData + this->filePointer));
  this->filePointer += 4;
  return ret;
}

uint64_t ByteOrderSwappingBinaryFileReader::ReadUint64()
{
  uint64_t ret = SwapByteOrder(*reinterpret_cast<uint64_t*>(this->fileData + this->filePointer));
  this->filePointer += 8;
  return ret;
}

int8_t ByteOrderSwappingBinaryFileReader::ReadInt8()
{
  return *reinterpret_cast<int8_t*>(this->fileData + this->filePointer++);
}

int16_t ByteOrderSwappingBinaryFileReader::ReadInt16()
{
  int16_t ret = static_cast<int16_t>(SwapByteOrder(*reinterpret_cast<uint16_t*>(this->fileData + this->filePointer)));
  this->filePointer += 2;
  return ret;
}

int32_t ByteOrderSwappingBinaryFileReader::ReadInt32()
{
  int32_t ret = static_cast<int32_t>(SwapByteOrder(*reinterpret_cast<uint32_t*>(this->fileData + this->filePointer)));
  this->filePointer += 4;
  return ret;
}

inline int64_t ByteOrderSwappingBinaryFileReader::ReadInt64()
{
  int64_t ret = static_cast<int64_t>(SwapByteOrder(*reinterpret_cast<uint64_t*>(this->fileData + this->filePointer)));
  this->filePointer += 8;
  return ret;
}

bool ByteOrderSwappingBinaryFileReader::ReadResult()
{
  return this->readResult;
}
