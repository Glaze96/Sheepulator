#define _USE_MATH_DEFINES
#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <cmath>

Sheep::Sheep(float startX, float startY, float speed, std::vector<Movable *> &sheepList, std::vector<Movable *> &dogList) : m_sheepList(sheepList), m_dogList(dogList), Movable(speed)
{
  m_position.X = startX;
  m_position.Y = startY;
  m_speed = speed;
}

void Sheep::init()
{
  m_nearestSheep = findNearest(m_sheepList);
}

void Sheep::update(uint32_t countedFrames)
{
  if (m_dogList.size() > 0)
  {
    m_nearestDog = findNearest(m_dogList);
    moveAwayFromDog(m_nearestDog);
  }
  else
  {
    moveRandom();
  }
}

void Sheep::moveToNearestSheep(Movable *nearestSheep)
{
  Vector2 dif = (nearestSheep->getPosition() - m_position);
  if (dif.magnitude() > 5.0f)
    move(dif.normalized() * m_speed);
}

void Sheep::moveAwayFromDog(Movable *nearestDog)
{
  Vector2 dif = (m_position - nearestDog->getPosition());
  move(dif.normalized() * m_speed);
}

void Sheep::moveRandom() {
  m_directionAngle += ((rand() % 1000 - 499) / 500.f) * M_PI * 0.1f; 
  moveDirection();
}

Movable *Sheep::findNearest(const std::vector<Movable *> &list)
{
  int numMovables = list.size();
  int lastNearest = 0;
  int nearestIndex = 0;
  float minDistance = INFINITY;

  for (int i = 0; i < numMovables; i++)
  {
    float newDistance = Vector2::DistanceSquared(list.at(i)->getPosition(), m_position);

    if (newDistance < 1.0f)
      continue;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }
  return list.at(nearestIndex);
}