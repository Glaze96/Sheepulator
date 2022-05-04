#define _USE_MATH_DEFINES
#include "dog.h"
#include <cmath>

Dog::Dog(float startX,
         float startY,
         float speed,
         std::vector<Movable *> &sheepList,
         std::vector<Movable *> &dogList) : Movable(), m_sheepList(sheepList), m_dogList(dogList)
{
  setPosition(startX, startY);
  m_speed = speed;
}

void Dog::update(uint32_t countedFrames)
{
  moveRandom(1.0f);
}