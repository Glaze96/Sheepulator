#define _USE_MATH_DEFINES
#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

Sheep::Sheep(float startX,
             float startY,
             float speed,
             int viewRange,
             std::vector<Movable *> *sheepList,
             std::vector<Movable *> *dogList,
             std::vector<std::vector<Movable *>> *sheepGrid) : Movable(), m_viewRange(viewRange), m_sheepList(sheepList), m_dogList(dogList), m_sheepGrid(sheepGrid)
{
  m_position.X = startX;
  m_position.Y = startY;
  m_speed = speed;
}

void Sheep::init()
{
}

void Sheep::update(uint32_t countedFrames)
{
  // moveTarget(findNearestNew(m_sheepGrid, m_sheepList));
  moveTarget(findNearest(m_dogList), true);
  moveRandom(0.05);
}

void Sheep::moveTarget(Movable *target, bool away)
{
  if (target == nullptr)
    return;

  Vector2 dif = (target->getPosition() - getPosition());

  Vector2 direction = away ? -dif.normalized() : dif.normalized();

  if (dif.magnitude() > 5.0f)
    move(direction * m_speed);
}

void Sheep::moveRandom(float magnitude)
{
  m_directionAngle += ((rand() % 1000 - 499) / 500.f) * M_PI * magnitude;
  moveDirection();
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
    float newDistance = Vector2::DistanceSquared(list->at(i)->getPosition(), m_position);

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

Movable *Sheep::findNearestNew(std::vector<std::vector<Movable *>> *gridList, std::vector<Movable *> *list)
{
  std::vector<Movable *> near;

  for (int x = m_position.X - m_viewRange; x < m_position.X + m_viewRange; x++)
  {
    for (int y = m_position.Y - m_viewRange; y < m_position.Y + m_viewRange; y++)
    {
      int xPos = x;
      int yPos = y;

      if (xPos < 0)
        xPos = 0;
      if (xPos > 1280 - 1)
        xPos = 1280 - 1;

      if (yPos < 0)
        yPos = 0;
      if (yPos > 720 - 1)
        yPos = 720 - 1;

      Movable *newMovable = gridList->at(yPos)[xPos];
      if (newMovable != nullptr)
        near.push_back(newMovable);
    }
  }
  Movable *nearest = findNearest(&near);
  return nearest;
}