#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>

Sheep::Sheep(float startX, float startY, float speed, std::vector<Sheep> *sheepList) : m_sheepList(sheepList), m_speed(speed)
{
  setPosition(startX, startY);
}

void Sheep::init()
{
  m_nearestSheep = findNearestSheep();
}

void Sheep::move(float x, float y)
{
  m_x += x;
  m_y += y;
}

void Sheep::update(uint32_t countedFrames)
{
  if (m_nearestSheep != nullptr)
    moveToNearestSheep(m_nearestSheep);

  move(rand() % 5 - 2, rand() % 5 - 2);
}

void Sheep::moveToNearestSheep(const Sheep *nearestSheep)
{
  float x = nearestSheep->m_x - m_x;
  float y = nearestSheep->m_y - m_y;
  move(x * m_speed, y * m_speed);
}

float Sheep::calcDistanceSquared(float x, float y)
{
  return ((x - m_x) * (x - m_x)) + ((y - m_y) * (y - m_y));
}

Sheep *Sheep::findNearestSheep()
{
  float currentDistanceToSheep = 1000000;

  auto &nearestSheep = *std::min_element(
      m_sheepList->begin(), m_sheepList->end(),
      [](auto &a, auto &b)
      { return a.calcDistanceSquared(b.m_x, b.m_y); });

  return &nearestSheep;
}