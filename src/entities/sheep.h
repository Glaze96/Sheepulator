#pragma once
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "../math/vector2.h"
#include "movable.h"
#include "dog.h"

class Sheep : public Movable
{
public:
  Sheep(float startX, float startY, float speed, std::vector<Movable *> &sheepList, std::vector<Movable *> &dogList);
  void init();

public:
  void update(uint32_t countedFrames); // Main logic loop

private:
  void moveToNearestSheep(Sheep *nearestSheep);
  Movable *findNearest(const std::vector<Movable *> &list);

private:
  std::vector<Movable *> &m_sheepList;
  std::vector<Movable *> &m_dogList;
  Movable *m_nearestSheep;
  Movable *m_nearestDog;
};