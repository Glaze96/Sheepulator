#pragma once

#include "movable.h"
#include <stdint.h>
#include <vector>

class Dog : public Movable
{
public:
  Dog(float startX,
      float startY,
      float speed,
      std::vector<Movable *> &sheepList,
      std::vector<Movable *> &dogList);

public:
  void update(uint32_t countedFrames); // Main logic loop
private:
  std::vector<Movable *> &m_sheepList;
  std::vector<Movable *> &m_dogList;
  Movable *m_nearestSheep;
  Movable *m_nearestDog;
};