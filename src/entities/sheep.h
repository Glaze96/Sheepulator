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
        std::vector<Movable *> *sheepList,
        std::vector<Movable *> *dogList,
        std::vector<std::vector<Movable *>> &sheepGrid);
  void init();

public:
  void update(float frameTime); // Main logic loop
private:
  void moveTowardsTarget(Movable *target, float distanceCap = 1.0f, bool away = false);
  void moveTowardsPosition(Vector2 pos, float distanceCap = 1.0f, bool away = false);
  void moveWithNeigbors(const std::vector<Movable *> &neighbors);

  void flock();

  Movable *findNearest(const std::vector<Movable *> *list);
  Movable *findNearestOnGrid(std::vector<std::vector<Movable *>> *gridList, std::vector<Movable *> *list);
  std::vector<Movable *> findNeighbors(const std::vector<std::vector<Movable *>> &gridList);

  Vector2 findNeighborCenter(const std::vector<Movable *> &neigbors);
  float findNeighborAngle(const std::vector<Movable *> &neigbors);

private:
  std::vector<Movable *> *m_sheepList;
  std::vector<Movable *> *m_dogList;
  Movable *m_nearestSheep;
  Movable *m_nearestDog;
  std::vector<Movable *> *m_neighbors;
  std::vector<std::vector<Movable *>> &m_sheepGrid;
  
  int m_viewRange;
};