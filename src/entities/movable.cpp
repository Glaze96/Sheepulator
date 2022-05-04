#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable(float speed) : m_speed(speed) {
  m_directionAngle = ((rand() % 1000) - 500) / 1000.f * M_PI_2;
}

void Movable::moveDirection() {
  move(Vector2::AngleToVector(m_directionAngle) * m_speed);
}

void Movable::setDirection(float angle) {
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
