#pragma once
#include "renderable.h"

class Sheep : public Renderable
{
public:
  Sheep(float startX, float startY);

public:
  void move(float x, float y);
  
private:
  float m_xVelocity, m_yVelocity;
};