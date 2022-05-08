#pragma once
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "../math/vector2.h"
#include "movable.h"
#include "dog.h"
#include "agent.h"

class Sheep : public Agent
{
public:
  Sheep(const Vector2 &startPos,
        const Vector2 &playArea,
        float speed,
        float currentAngle,
        float turnSpeed,
        float viewRange,
        ChunkManager &chunkManager,
        std::vector<Movable *> &sheepList,
        std::vector<Movable *> &dogList);

  void init();

public:
  void update(); // Main logic loop

private:
  void moveWithFlock(const std::vector<Movable *> &flock);

  void flock(); // FLOCK AI

private:
  std::vector<Movable *> *m_flock;

  bool m_inFlock;
  float m_flockWantedAngle;
  Vector2 m_prefferedFlockPosition;

  int m_viewRange;
  Vector2 m_flockPositionOffset;
  int m_smartTick;
};