#include "Controller.h"

Controller* Controller::__instance;

Controller* Controller::Instance()
{
  if (__instance == nullptr)
    __instance = new Controller();
  return __instance;
}

void Controller::Destroy()
{
  delete __instance;
}

Controller::Controller()
{
  this->conSerial = new Serial(0xC0, 9600);
}

Controller::~Controller()
{
  delete this->conSerial;
}

const uint8_t Controller::GetCon0()
{
  return this->con0;
}

const uint8_t Controller::GetCon1()
{
  return this->con1;
}

void Controller::Update()
{
  this->conSerial->Purge();
  uint8_t dat = 0x0C; //identifier for first controller data
  this->conSerial->WriteData(&dat, 1);
  dat = 0x1C; //identifier for second controller data
  this->conSerial->WriteData(&dat, 1);

  // the arduino will send two bytes per controller, one is 0x0c or 0x1c, second is the actual NES data
  uint8_t buf[4];
  while (this->conSerial->HasData() < 4) //wait until we have both answers for controller 1 and 2
  {
    Sleep(0);
  }
  this->conSerial->ReadData(buf, 4);
  //buf should actually be 0x0c con0, 0x1c, con1; but we check this to be safe, if the data is corrupted, we throw this loop away and check again later
  if (buf[0] == 0x0C) this->con0 = buf[1];
  else if (buf[0] == 0x1C) this->con1 = buf[1];
  if (buf[2] == 0x1C) this->con1 = buf[3];
  else if (buf[2] == 0x0C) this->con0 = buf[3];
}
