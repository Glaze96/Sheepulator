#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>

Sheep::Sheep(float startX, float startY, float speed)
{
  m_position.X = startX;
  m_position.Y = startY;
}

void Sheep::init(std::vector<Sheep> *sheepList)
{
  m_sheepList = sheepList;
  m_nearestSheep = findNearestSheep();
}

void Sheep::update(uint32_t countedFrames)
{
  // moveToNearestSheep(m_nearestSheep);

  move(rand() % 11 - 5, rand() % 11 - 5);
}

void Sheep::moveToNearestSheep(Sheep *nearestSheep)
{
  Vector2 dif = (nearestSheep->m_position - m_position);
  if (dif.magnitude() > 5.0f)
    move(dif.normalized() * m_speed);
}

Sheep *Sheep::findNearestSheep()
{
  int numSheeps = m_sheepList->size();
  int lastNearest = 0;
  int nearestIndex = 0;
  float minDistance = 100000000000;

  for (int i = 0; i < numSheeps; i++)
  {
    float newDistance = Vector2::DistanceSquared(m_sheepList->at(i).m_position, m_position);

    if (newDistance < 1.0f)
      continue;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }
  // const auto nearestSheep = *std::min_element(
  //   m_sheepList.begin(), m_sheepList.end(),
  //   [](auto &a, auto &b) { return a.calcDistanceSquared(b); })

  return &m_sheepList->at(nearestIndex);
}