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
             float speed,
             int viewRange,
             std::vector<Movable *> *sheepList,
             std::vector<Movable *> *dogList,
             std::vector<std::vector<Movable *>> *sheepGrid) : Movable(), m_viewRange(viewRange), m_sheepList(sheepList), m_dogList(dogList), m_sheepGrid(sheepGrid)
{
  setPosition(startX, startY);
  m_speed = speed;
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

void Sheep::update(uint32_t countedFrames)
{

  int y = (int)this->getPosition().Y;
  int x = (int)this->getPosition().X;
  (*m_sheepGrid)[y][x] = nullptr; //Clear current pos

  // moveTarget(findNearestNew(m_sheepGrid, m_sheepList));
  moveTarget(findNearest(m_dogList), true); // Move away from dogs
  moveRandom(0.05); // Move a bit random

  y = (int)this->getPosition().Y;
  x = (int)this->getPosition().X;

  (*m_sheepGrid)[y][x] = (Sheep *)this;  //Set new coordinates to point to this instance of sheep
  
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

Movable *Sheep::findNearestNew(std::vector<std::vector<Movable *>> *gridList, std::vector<Movable *> *list)
{
  std::vector<Movable *> near;

  for (int x = getPosition().X - m_viewRange; x < getPosition().X + m_viewRange; x++)
  {
    for (int y = getPosition().Y - m_viewRange; y < getPosition().Y + m_viewRange; y++)
    {
      int xPos = std::clamp((int)this->getPosition().X, 0, (int)Settings::SCREEN_WIDTH - 1);
      int yPos = std::clamp((int)this->getPosition().Y, 0, (int)Settings::SCREEN_HEIGHT - 1);

      Movable *newMovable = gridList->at(yPos)[xPos];
      if (newMovable != nullptr)
        near.push_back(newMovable);
    }
  }
  Movable *nearest = findNearest(&near);
  return nearest;
}