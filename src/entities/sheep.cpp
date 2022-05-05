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

Sheep::Sheep(float startX,
             float startY,
             std::vector<Movable *> *sheepList,
             std::vector<Movable *> *dogList,
             std::vector<std::vector<Movable *>> &sheepGrid) : Movable(),
                                                               m_sheepList(sheepList),
                                                               m_dogList(dogList),
                                                               m_sheepGrid(sheepGrid)
{
  setPosition(startX, startY);
  m_sheepGrid[startY][startX] = this;

  m_turnSpeed = 0.3f;
  // m_speed = (((rand() % 1000) / 1000) * 0.6f) + 0.15f; // give a random speed
  m_speed = 1.0f; 
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
void Sheep::update(float deltaTime)
{

  int y = (int)getPosition().Y;
  int x = (int)getPosition().X;
  m_sheepGrid[y][x] = nullptr; // Clear current pos

  flock();

  y = (int)getPosition().Y;
  x = (int)getPosition().X;
  m_sheepGrid[y][x] = this; // Update grid
}

void Sheep::flock()
{
  std::vector<Movable *> nearestNeighbors = findNeighbors(m_sheepGrid);

  int numNeigbors = nearestNeighbors.size();

  if (numNeigbors >= 5 && !m_inFlock)
  {
    m_inFlock = true;

    float randomDistFromCenter = ((rand() % 100) / 100.0f + 1.0f) * numNeigbors / 3.0f;
    m_flockPositionOffset = Vector2::RandomUnitVector() * randomDistFromCenter;


    float flockAvergeAngle = findNeighborAngle(nearestNeighbors);
    // float randomAngleOffset = (((rand() % 1000) / 1000.0f) - 0.5f) * 0.02f;
    // setWantedAngle(flockAvergeAngle);

    // moveForward();
  }
  else {
    m_inFlock = false;
  }

  if (m_inFlock)
  {
    Vector2 centerOfFlock = findNeighborCenter(nearestNeighbors);
    moveTowardsPosition(centerOfFlock + m_flockPositionOffset);
  }
  else {
    moveRandom(0.5f);
  }

}

void Sheep::moveTowardsTarget(Movable *target, float distanceCap, bool away)
{
  if (target == nullptr)
    return;

  moveTowardsPosition(target->getPosition(), distanceCap, away);
}

void Sheep::moveTowardsPosition(Vector2 pos, float distanceCap, bool away)
{
  Vector2 dif = (pos - getPosition());

  Vector2 direction = away ? -dif.normalized() : dif.normalized();
  // Cannot check on grid here because it will find itself due to smaller than 1 steps
  Vector2 newPosition = getPosition() + (direction * m_speed);
  Sheep *sheepAtNewPos = (Sheep *)m_sheepGrid[(int)newPosition.Y][(int)newPosition.X];

  if (sheepAtNewPos == nullptr || sheepAtNewPos == this)
  {
  }
  if (dif.magnitude() > distanceCap)
    move(direction * m_speed);
}

void Sheep::moveWithNeigbors(const std::vector<Movable *> &neighbors)
{
}

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

    if (newDistance < 2.0f)
      continue;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }
  return list->at(nearestIndex);
}

Movable *Sheep::findNearestOnGrid(std::vector<std::vector<Movable *>> *gridList, std::vector<Movable *> *list)
{
  // std::vector<Movable *> near = findNeighbors(gridList);
  // Movable *nearest = findNearest(&near);
  // return nearest;
  return nullptr;
}

std::vector<Movable *> Sheep::findNeighbors(const std::vector<std::vector<Movable *>> &gridList)
{
  std::vector<Movable *> near;

  for (int x = getPosition().X - m_viewRange; x < getPosition().X + m_viewRange; x++)
  {
    for (int y = getPosition().Y - m_viewRange; y < getPosition().Y + m_viewRange; y++)
    {
      int xPos = std::clamp(x, 0, (int)Settings::SCREEN_WIDTH - 1);
      int yPos = std::clamp(y, 0, (int)Settings::SCREEN_HEIGHT - 1);

      Movable *newMovable = m_sheepGrid[yPos][xPos];
      if (newMovable != nullptr)
      {
        near.push_back(newMovable);
      }
    }
  }

  return near;
}

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

float Sheep::findNeighborAngle(const std::vector<Movable *> &neighbors)
{
  if (neighbors.size() == 0)
    return 0;

  float averageAngle = 0;
  int count = neighbors.size();

  std::vector<Vector2> angleVectors;

  float totalX = 0;
  float totalY = 0;

  for (auto &n : neighbors)
  {
    Vector2 vectorFromAngle = Vector2::AngleToVector(n->getAngle());
    angleVectors.push_back(vectorFromAngle);
    totalX += vectorFromAngle.X;
    totalY += vectorFromAngle.Y;
  }

  Vector2 finalVector(totalX / count, totalY / count);

  return finalVector.getAngleRad();
}