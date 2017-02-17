#include "Serial.h"

std::vector<std::string> Serial::AvailableComPorts;

void Serial::ReadAvailableComPorts()
{
  char* portPrefix = "COM";
  for (size_t i = 0; i < 255; i++) //check for 255 com ports if they are available
  {
    std::string portName = i >= 10 ? "\\\\.\\COM" : "COM";
    char istr[8];
    _itoa_s(i, istr, 10);
    portName.append(istr);
    HANDLE hSerial = CreateFile(portName.c_str(),
      GENERIC_READ | GENERIC_WRITE,
      0,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);
    //WE assume that this serial port is available if it's not invalid
    if (hSerial != INVALID_HANDLE_VALUE)
    {
      Serial::AvailableComPorts.push_back(portName);
    }
    CloseHandle(hSerial);
  }
}

Serial::Serial(uint8_t identifier, unsigned int BAUD)
{
  //Search for available COM ports if we have'nt done it yet
  if (Serial::AvailableComPorts.size() == 0) Serial::ReadAvailableComPorts();

  //We're not yet connected
  this->connected = false;
  size_t currentPort = 0;

  //iterate over all available com ports until we are connected
  while (!this->connected && currentPort < Serial::AvailableComPorts.size())
  {
    //Try to connect to the given port throuh CreateFile
    this->hSerial = CreateFile(Serial::AvailableComPorts.at(currentPort).c_str(),
      GENERIC_READ | GENERIC_WRITE,
      0,
      NULL,
      OPEN_EXISTING,
      FILE_ATTRIBUTE_NORMAL,
      NULL);

    //Check if the connection was successfull
    if (this->hSerial == INVALID_HANDLE_VALUE)
    {
      printf("Can't open port %s", Serial::AvailableComPorts.at(currentPort).c_str());
      ++currentPort;
    }
    else
    {
      //If connected we try to set the comm parameters
      DCB dcbSerialParams = { 0 };

      //Try to get the current
      if (!GetCommState(this->hSerial, &dcbSerialParams))
      {
        //If impossible, show an error
        printf("failed to get current serial parameters!");
      }
      else
      {
        //Define serial connection parameters for the arduino board
        dcbSerialParams.BaudRate = BAUD;
        dcbSerialParams.ByteSize = 8;
        dcbSerialParams.StopBits = ONESTOPBIT;
        dcbSerialParams.Parity = NOPARITY;
        //Setting the DTR to Control_Enable ensures that the Arduino is properly
        //reset upon establishing a connection
        dcbSerialParams.fDtrControl = DTR_CONTROL_ENABLE;

        //Set the parameters and check for their proper application
        if (!SetCommState(hSerial, &dcbSerialParams))
        {
          printf("ALERT: Could not set Serial Port parameters");
        }
        else
        {
          //Flush any remaining characters in the buffers 
          PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
          //We wait 2s as the arduino board will be reseting
          Sleep(ARDUINO_WAIT_TIME);
          uint8_t write = 0xFF;
          if (this->WriteData(&write, 1))
          {
            Sleep(ARDUINO_WAIT_TIME);
            unsigned char ret;
            this->ReadData((char*)&ret, 1);
            if (ret == identifier)
            {
              this->connected = true;
              break;
            }

            if (!this->connected)
            {
              ++currentPort;
              CloseHandle(this->hSerial);
            }
          }
        }
      }
    }
  }
}

Serial::~Serial()
{
  //Check if we are connected before trying to disconnect
  if (this->connected)
  {
    //We're no longer connected
    this->connected = false;
    //Close the serial handler
    CloseHandle(this->hSerial);
  }
}

const int Serial::HasData()
{
  //Use the ClearCommError function to get status info on the Serial port
  ClearCommError(this->hSerial, &this->errors, &this->status);
  return this->status.cbInQue;
}

void Serial::Purge()
{
  PurgeComm(this->hSerial, PURGE_RXCLEAR | PURGE_TXCLEAR);
}

const int Serial::ReadData(void* buffer, const unsigned int nbChar)
{
  //Number of bytes we'll have read
  DWORD bytesRead;
  //Number of bytes we'll really ask to read
  unsigned int toRead;

  //Use the ClearCommError function to get status info on the Serial port
  ClearCommError(this->hSerial, &this->errors, &this->status);

  //Check if there is something to read
  if (this->status.cbInQue > 0)
  {
    //If there is we check if there is enough data to read the required number
    //of characters, if not we'll read only the available characters to prevent
    //locking of the application.
    if (this->status.cbInQue > nbChar)
    {
      toRead = nbChar;
    }
    else
    {
      toRead = this->status.cbInQue;
    }

    //Try to read the require number of chars, and return the number of read bytes on success
    if (ReadFile(this->hSerial, buffer, toRead, &bytesRead, NULL))
    {
      return bytesRead;
    }

  }

  //If nothing has been read, or that an error was detected return 0
  return 0;

}


const bool Serial::WriteData(const void* buffer, const unsigned int nbChar)
{
  DWORD bytesSend;

  //Try to write the buffer on the Serial port
  if (!WriteFile(this->hSerial, buffer, nbChar, &bytesSend, 0))
  {
    DWORD error = GetLastError();
    //In case it don't work get comm error and return false
    ClearCommError(this->hSerial, &this->errors, &this->status);

    return false;
  }
  else
    return true;
}

const bool Serial::IsConnected()
{
  //Simply return the connection status
  return this->connected;
}