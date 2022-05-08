#pragma once

#include "movable.h"
#include <stdint.h>
#include <vector>
#include "agent.h"

struct ChunkManager;

class Dog : public Agent
{
public:
  Dog(const Vector2 &startPos,
      const Vector2 &playArea,
      float speed,
      float currentAngle,
      float turnSpeed,
      ChunkManager &chunkManager,
      std::vector<Movable *> &sheepList,
      std::vector<Movable *> &dogList);

public:
  void update(); // Main logic loop
private:
  int m_smartTick;
  float m_viewRange;
};