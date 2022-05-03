#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>

Sheep::Sheep(float startX, float startY, float speed) : m_speed(speed)
{
  m_position.X = startX;
  m_position.Y = startY;
  // printf("X-START: %f, Y-START: %f \n", m_position.X, m_position.X);
}

void Sheep::init(std::vector<Sheep> *sheepList)
{
  m_sheepList = sheepList;
  m_nearestSheep = findNearestSheep();
}

void Sheep::move(float x, float y)
{
  m_position.add(x, y);
}

void Sheep::move(const Vector2 &distance)
{
  m_position.add(distance);
}

void Sheep::setTarget(const Vector2 &position)
{
  m_target = position;
}

void Sheep::moveToTarget()
{
  Vector2 dif = m_target - m_position;
  move(dif.normalized() * m_speed);
}

// MAIN LOGIC LOOP OF THE SHEEP
void Sheep::update(uint32_t countedFrames)
{
  moveToNearestSheep(m_nearestSheep);

  // moveToTarget();
}

void Sheep::moveToNearestSheep(Sheep *nearestSheep)
{
  Vector2 dif = (nearestSheep->m_position - m_position);
  if (dif.magnitude() > 1.0f)
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
    float newDistance = Vector2::Distance(m_sheepList->at(i).m_position, m_position);

    if (newDistance < 1.0f)
      break;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }

  // std::cout << "nearest index: " << nearestIndex << std::endl;

  return &m_sheepList->at(nearestIndex);
}