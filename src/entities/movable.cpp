#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable() {
  float r = (rand() % 1000) / 1000.0f;
  m_directionAngle = r * M_PI * 2.0f;
}

void Movable::moveDirection() {
  move(cos(m_directionAngle) * m_speed, sin(m_directionAngle) * m_speed);
}

void Movable::move(float x, float y)
{
  addPosition(x, y);
}

void Movable::move(const Vector2 &distance)
{
  addPosition(distance.X, distance.Y);
}

void Movable::moveRandom(float magnitude)
{
  // std::cout << "before: " << m_directionAngle << std::endl;
  float r = (rand() % 1000) / 1000.0f - 0.5f;
  // // std::cout << "before: " << r << std::endl;

  m_directionAngle += r * magnitude;
  // std::cout << "after: " << m_directionAngle << std::endl;
  moveDirection();
}