#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable(float speed) : m_speed(speed) {
  m_directionAngle = ((rand() % 1000) - 500) / 1000.f * M_PI * 2.0f;
}

void Movable::moveDirection() {
  move(Vector2(cos(m_directionAngle) * m_speed, sin(m_directionAngle) * m_speed));
}

void Movable::changeDirection(float angle) {
  m_directionAngle = angle;
}

void Movable::move(float x, float y)
{
  m_position.X += x;
  m_position.Y += y;
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