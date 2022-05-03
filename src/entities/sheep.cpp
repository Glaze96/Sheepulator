#include "sheep.h"

Sheep::Sheep(float startX, float startY)
{
  setPosition(startX, startY);
}

void Sheep::move(float x, float y)
{
  m_x += x;
  m_y += y;
}
