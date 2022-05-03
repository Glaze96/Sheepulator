#include "movable.h"


Movable::Movable() : m_speed(0.1f) {

}

void Movable::move(float x, float y)
{
  move(Vector2(x, y));
}

void Movable::move(const Vector2 &distance)
{
  m_position += distance;
}

void Movable::setTarget(const Vector2 &position)
{
  m_target = position;
}

void Movable::moveTowardsTarget()
{
  Vector2 dif = m_target - m_position;
  move(dif.normalized() * m_speed);
}