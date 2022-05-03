#pragma once
#include <vector>
#include "renderable.h"
#include <stdlib.h>
#include <stdint.h>
#include "../math/vector2.h"

class Sheep : public Renderable
{
public:
  Sheep(float startX, float startY, float speed);
  void init(std::vector<Sheep> *sheepList);

public:
  void move(float x, float y);
  void move(const Vector2 &distance);
  
  void setTarget(const Vector2 &position);
  void moveToTarget();

  void update(uint32_t countedFrames); // Main logic loop 

private:
  void moveToNearestSheep(Sheep *nearestSheep);
  Sheep *findNearestSheep();

private:
  float m_xVelocity, m_yVelocity;
  std::vector<Sheep> *m_sheepList;
  Sheep *m_nearestSheep;
  float m_speed;
  Vector2 m_target;
};