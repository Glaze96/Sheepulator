#define _USE_MATH_DEFINES
#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "../settings.h"
#include "../globals.h"

Sheep::Sheep(float startX,
             float startY,
             std::vector<Movable *> *sheepList,
             std::vector<Movable *> *dogList,
             ChunkManager &chunkManager) : Movable(),
                                           m_sheepList(sheepList),
                                           m_dogList(dogList),
                                           m_chunkManager(chunkManager)
{
  setPosition(startX, startY);

  m_turnSpeed = 0.08f;
  // m_speed = (((rand() % 1000) / 1000) * 0.6f) + 0.15f; // give a random speed
  m_speed = 20.0f * Time::Instance()->DeltaTime;
  m_viewRange = 40;
}

void Sheep::init()
{
}

/*
 *
 * On sheep update:
 * 1. Clear sheeps position in sheepGrid
 * 2. Move sheep
 * 3. Set new position in sheepGrid
 *
 */
void Sheep::update()
{
  flock();
}

void Sheep::flock()
{
  // std::vector<Movable *> nearestNeighbors = findNeighbors(m_sheepGrid);
  std::vector<Movable *> nearestNeighbors = m_chunkManager.getMovablesInChunkSurrounding(getPosition());

  int numNeigbors = nearestNeighbors.size();

  // CHECK FOR FLOCK
  if (numNeigbors >= 10 && !m_inFlock)
  {
    m_inFlock = true;

    float randomDistFromCenter = ((rand() % 100) / 100.0f + 1.0f) * numNeigbors / 10.0f;
    m_flockPositionOffset = Vector2::RandomUnitVector() * randomDistFromCenter;
  }

  if (numNeigbors <= 4)
  {
    m_inFlock = false;
  }

  // FLOCK MOVEMENT
  if (m_inFlock)
  {
    Vector2 centerOfFlock = findNeighborCenter(nearestNeighbors);
    moveTowardsPosition(centerOfFlock + m_flockPositionOffset, 1.0f);

    float flockAvergeAngle = findNeighborAngle(nearestNeighbors);
    float randomAngleOffset = 0;
    if (Time::Instance()->FrameCounter % 40 == 0)
    {
      float randomAngleOffset = (((rand() % 1000) / 500.0f) - 1.0f) * 0.1f;
    }
    setWantedAngle(flockAvergeAngle);
  }
  else // if NOT in flock
  {
    if (Time::Instance()->FrameCounter % 30 == 0)
    {
      float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
      setWantedAngle(r);
    }
  }

  moveForward(1.0f);
}

void Sheep::moveTowardsPosition(Vector2 pos, float multiplier, float distanceCap)
{
  Vector2 dif = (pos - getPosition());

  // Cannot check on grid here because it will find itself due to smaller than 1 steps
  // if (sheepAtNewPos == nullptr || sheepAtNewPos == this)
  // {
  // }

  if (dif.magnitude() > distanceCap)
    move(dif.normalized() * m_speed * multiplier);
}

void Sheep::moveWithNeigbors(const std::vector<Movable *> &neighbors)
{
}

// find nearest Movable in the given list
Movable *Sheep::findNearest(const std::vector<Movable *> *list)
{
  if (list->size() == 0)
    return nullptr;
  int numMovables = list->size();
  int lastNearest = 0;
  int nearestIndex = 0;
  float minDistance = INFINITY;

  for (int i = 0; i < numMovables; i++)
  {
    float newDistance = Vector2::DistanceSquared(list->at(i)->getPosition(), getPosition());

    // Ignore self
    if (newDistance < 1.0f)
      continue;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }
  return list->at(nearestIndex);
}

// Find the center position of the neighbors
Vector2 Sheep::findNeighborCenter(const std::vector<Movable *> &neighbors)
{
  float totalX = 0;
  float totalY = 0;
  int count = neighbors.size();

  for (auto &n : neighbors)
  {
    totalX += n->getPosition().X;
    totalY += n->getPosition().Y;
  }

  return Vector2(totalX / count, totalY / count);
}

// Get average angle out of all the neigbors
float Sheep::findNeighborAngle(const std::vector<Movable *> &neighbors)
{
  float averageAngle = 0;
  int count = neighbors.size();

  float totalX = 0;
  float totalY = 0;

  for (auto &n : neighbors)
  {
    Vector2 vectorFromAngle = Vector2::VectorFromAngle(n->getAngle());
    totalX += vectorFromAngle.X;
    totalY += vectorFromAngle.Y;
  }

  Vector2 finalVector(totalX, totalY);
  // // No need for unit vector?
  // Vector2 finalVector(totalX / count, totalY / count);

  averageAngle = finalVector.getAngleRad();
  // std::cout << "Average angle: " << averageAngle << std::endl;
  return averageAngle;
}