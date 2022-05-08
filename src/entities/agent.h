#pragma once
#include "movable.h"
#include "chunk/chunkManager.h"
class Agent : public Movable
{
public:
  Agent(
      const Vector2 &startPos,
      const Vector2 &playArea,
      float speed,
      float currentAngle,
      float turnSpeed,
      ChunkManager &chunkManager,
      std::vector<Movable *> &sheepList,
      std::vector<Movable *> &dogList);

  Movable *findNearest(const std::vector<Movable *> *list);

  Vector2 findFlockCenter(const std::vector<Movable *> &flock);
  float findFlockAngle(const std::vector<Movable *> &flock);
  void setFlockAngle(const std::vector<Movable *> &flock, float angle);

protected:
  ChunkManager &m_chunkManager;
  std::vector<Movable *> &m_sheepList;
  std::vector<Movable *> &m_dogList;

};