#include "movable.h"


Movable::Movable() : m_speed(0.1f) {

}

void Movable::move(float x, float y)
{
  m_position.add(x, y);
}

void Movable::move(const Vector2 &distance)
{
  m_position.add(distance);
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