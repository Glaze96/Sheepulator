#pragma once

#include "renderable.h"
#include "../math/vector2.h"

class Movable : public Renderable
{
public:
  Movable(float speed);

public:
  void move(float x, float y);
  void move(const Vector2 &distance);

  void moveDirection();
  void setDirection(float angle);

protected:
  float m_speed; // Base speed
  float m_directionAngle; // Radians
};