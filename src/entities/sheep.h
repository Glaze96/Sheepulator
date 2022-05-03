#pragma once
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "../math/vector2.h"
#include "movable.h"

class Sheep : public Movable
{
public:
  Sheep(float startX, float startY, float speed);
  void init(std::vector<Sheep> *sheepList);

public:
  void update(uint32_t countedFrames); // Main logic loop 

private:
  void moveToNearestSheep(Sheep *nearestSheep);
  Sheep *findNearestSheep();

private:
  std::vector<Sheep> *m_sheepList;
  Sheep *m_nearestSheep;
};