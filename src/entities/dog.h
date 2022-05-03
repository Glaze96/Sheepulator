#include "movable.h"
#include <stdint.h>

class Dog : public Movable
{
public:
  Dog();

public:
  void update(uint32_t countedFrames); // Main logic loop 

public:

};