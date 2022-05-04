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
  setPosition(startX, startY);
  m_speed = speed;
}

void Sheep::init()
{
}


/*What's the point of countedFrames???
 *
 * On sheep update:
 * 1. Clear sheeps position in sheepGrid
 * 2. Move sheep
 * 3. Set new position in sheepGrid
 * 
 */

void Sheep::update(uint32_t countedFrames, std::vector<std::vector<Movable *>> * ptr_sheepGrid, int h, int w)
{

  
  int x = std::clamp((int)this->getPosition().X, 0, (int)w - 1);  //Get current coordinates
  int y = std::clamp((int)this->getPosition().Y, 0, (int)h - 1);
  
  
  //std::cout << " pre nullified: " << (*ptr_sheepGrid)[y][x] << std::endl;
  
  (*ptr_sheepGrid)[y][x] = nullptr; //Clear current pos
  
  //std::cout << "post nullified: " << (*ptr_sheepGrid)[y][x] << std::endl;


  // moveTarget(findNearestNew(m_sheepGrid, m_sheepList));
  moveTarget(findNearest(m_dogList), true);
  moveRandom(0.05);

  
  x = std::clamp((int)this->getPosition().X, 0, (int)w - 1);  //Get updated coordinates
  y = std::clamp((int)this->getPosition().Y, 0, (int)h - 1);
  
  (*ptr_sheepGrid)[y][x] = (Sheep *)this;  //Set new coordinates to point to this instance of sheep
  
}
// void Sheep::update(uint32_t countedFrames)
// {
//   // moveTarget(findNearestNew(m_sheepGrid, m_sheepList));
//   moveTarget(findNearest(m_dogList), true);
//   moveRandom(0.05);
// }

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