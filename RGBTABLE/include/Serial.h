/*
  this mostly comes from the Arduino Serial Connection C++ Tutorial on the Arduino Playground
  http://playground.arduino.cc/Interfacing/CPPWindows
  */
#pragma once
#define ARDUINO_WAIT_TIME 2000

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

class Serial
{
private:
  static std::vector<std::string> AvailableComPorts;
public:
  //gets all available com ports via CreateFile()
  static void ReadAvailableComPorts();
  
private:
  //Serial comm handler
  HANDLE hSerial;
  //Connection status
  bool connected;
  //Get various information about the connection
  COMSTAT status;
  //Keep track of last error
  DWORD errors;

public:
  //Initialize Serial communication to the found COM Port and a given BAUD Rate
  Serial(const uint8_t identifier, const unsigned int BAUD = 1000000);
  //Close the connection
  ~Serial();

  //Returns the number of bytes in the serial buffer, returns 0 if no bytes are available
  const int HasData();

  //Clears the serial bus
  void Purge();

  //Read data in a buffer, if nbChar is greater than the
  //maximum number of bytes available, it will return only the
  //bytes available. The function return -1 when nothing could
  //be read, the number of bytes actually read.
  const int ReadData(void* buffer, const unsigned int nbChar);

  //Writes data from a buffer through the Serial connection
  //return true on success.
  const bool WriteData(const void* buffer, const unsigned int nbChar);

  //Check if we are actually connected
  const bool IsConnected();
};