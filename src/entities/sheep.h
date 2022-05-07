#pragma once
#include <vector>
#include <stdlib.h>
#include <stdint.h>
#include "../math/vector2.h"
#include "movable.h"
#include "dog.h"
#include "chunk/chunk.h"
#include "chunk/chunkManager.h"

class Sheep : public Movable
{
public:
  Sheep(float startX,
        float startY,
        std::vector<Movable *> *sheepList,
        std::vector<Movable *> *dogList,
        ChunkManager &chunkManager,
        Vector2 playArea);
  void init();

public:
  void update(); // Main logic loop

private:
  void moveTowardsPosition(Vector2 pos, float multiplier = 1.0f, float distanceCap = 2.0f);
  void moveWithNeigbors(const std::vector<Movable *> &neighbors);

  void flock(); // FLOCK AI

  Movable *findNearest(const std::vector<Movable *> *list);

  Vector2 findNeighborCenter(const std::vector<Movable *> &neigbors);
  float findNeighborAngle(const std::vector<Movable *> &neigbors);
  void setNeighborAngle(const std::vector<Movable *> &neigbors, float angle);

private:
  std::vector<Movable *> *m_sheepList;
  std::vector<Movable *> *m_dogList;
  Movable *m_nearestSheep;
  Movable *m_nearestDog;
  std::vector<Movable *> *m_neighbors;

  ChunkManager &m_chunkManager;

  bool m_inFlock;
  float m_flockWantedAngle;
  Vector2 m_prefferedFlockPosition;

  int m_viewRange;
  Vector2 m_flockPositionOffset;
  int m_smartTick;

  Vector2 m_playArea;
};