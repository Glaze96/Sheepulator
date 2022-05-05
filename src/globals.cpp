#include "globals.h"

Time* Time::instance = nullptr;

Time *Time::Instance()
{
  if (!instance)
    instance = new Time();

  return instance;
}