#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable() {
  m_directionAngle = ((rand() % 1000) - 500) / 500.f * M_PI_2;
}

void Movable::moveDirection() {
  move(Vector2::AngleToVector(m_directionAngle) * m_speed);
}

void Movable::setDirection(float angle) {
  m_directionAngle = angle;
}

void Movable::move(float x, float y)
{
  addPosition(x, y);
}

void Movable::move(const Vector2 &distance)
{
  addPosition(distance.X, distance.Y);
}
