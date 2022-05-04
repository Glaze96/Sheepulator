#include "dog.h"

Dog::Dog(float startX,
         float startY,
         float speed,
         std::vector<Movable *> &sheepList,
         std::vector<Movable *> &dogList) : m_sheepList(sheepList), m_dogList(dogList)
{
  m_position.X = startX;
  m_position.Y = startY;
  m_speed = speed;
}

void Dog::update(uint32_t countedFrames)
{
}