#pragma once
#include <vector>
#include "renderable.h"
#include <stdlib.h>
#include <stdint.h>

class Sheep : public Renderable
{
public:
  Sheep(float startX, float startY, float speed, std::vector<Sheep> *sheepList);

public:
  void move(float x, float y);
  void update(uint32_t countedFrames);
  void init();

private:
  void moveToNearestSheep(const Sheep *nearestSheep);
  Sheep *findNearestSheep();

  float calcDistanceSquared(float x, float y);

private:
  float m_xVelocity, m_yVelocity;
  std::vector<Sheep> *m_sheepList;
  Sheep *m_nearestSheep;
  float m_speed;
};