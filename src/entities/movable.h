#pragma once

#include "renderable.h"
#include "../math/vector2.h"

class Movable : public Renderable
{
public:
  Movable();

public:
  void move(float x, float y);
  void move(const Vector2 &distance);

  void setTarget(const Vector2 &position);

  void moveTowardsTarget();

protected:
  float m_speed;
  Vector2 m_target;
};