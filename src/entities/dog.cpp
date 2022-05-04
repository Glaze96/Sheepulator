#define _USE_MATH_DEFINES
#include "dog.h"
#include <cmath>

Dog::Dog(float startX,
         float startY,
         float speed,
         std::vector<Movable *> &sheepList,
         std::vector<Movable *> &dogList) : m_sheepList(sheepList), m_dogList(dogList)
{
  setPosition(startX, startY);
  m_speed = speed;
}

void Dog::update(uint32_t countedFrames)
{
  moveRandom(0.01f);
}

void Dog::moveRandom(float magnitude)
{
  m_directionAngle += ((rand() % 1000 - 499) / 500.f) * M_PI * magnitude;
  moveDirection();
}