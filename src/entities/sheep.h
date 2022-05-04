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
  Sheep(float startX,
        float startY,
        float speed,
        int viewRange,
        std::vector<Movable *> *sheepList,
        std::vector<Movable *> *dogList,
        std::vector<std::vector<Movable *>> *sheepGrid);
  void init();

public:
  void update(uint32_t countedFrames); // Main logic loop

private:
  void moveTarget(Movable *target, bool away = false);

  void moveRandom(float magnitude);

  Movable *findNearest(const std::vector<Movable *> *list);
  Movable *findNearestNew(std::vector<std::vector<Movable *>> *gridList, std::vector<Movable *> *list);

private:
  std::vector<Movable *> *m_sheepList;
  std::vector<Movable *> *m_dogList;
  Movable *m_nearestSheep;
  Movable *m_nearestDog;
  std::vector<std::vector<Movable *>> *m_sheepGrid;
  int m_viewRange;
};