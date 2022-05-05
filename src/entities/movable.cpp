#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable()
{
  float r = (rand() % 1000) / 1000.0f;
  m_directionAngle = r * M_PI * 2.0f;
  m_turnSpeed = 0.02f;
}

void Movable::addAngle(float angle)  {
    float wantedAngle = m_directionAngle + angle;
    m_directionAngle = fmod(wantedAngle, M_PI * 2.0);
  }

void Movable::moveForward()
{
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
  float r = (rand() % 1000) / 1000.0f - 0.5f;

  m_directionAngle += r * m_turnSpeed;
  moveForward();
}

void Movable::turnTowardsAngle(float targetAngle)
{

  float angleDif = m_directionAngle - targetAngle;

  if (angleDif > M_PI)
  {
    angleDif -= M_PI * 2.0f;
  }
  if (angleDif < -M_PI)
  {
    angleDif += M_PI * 2.0f;
  }

  addAngle(angleDif * m_turnSpeed);
}

