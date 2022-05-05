#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>

Movable::Movable()
{
  float r = (rand() % 1000) / 1000.0f;
  setAngle(r * M_PI * 2.0f);
}

void Movable::addAngle(float addAngle)
{
  setAngle(m_currentAngle + addAngle);
}

void Movable::setWantedAngle(float newAngle)
{
  m_wantedAngle = fmod(newAngle, M_PI * 2);
  if (m_currentAngle < 0)
  {
    m_wantedAngle += M_PI * 2.0f;
  }
}

void Movable::setAngle(float newAngle)
{
  m_currentAngle = fmod(newAngle, M_PI * 2);
  if (m_currentAngle < 0)
  {
    m_currentAngle += M_PI * 2.0f;
  }
}

void Movable::moveForward()
{
  turnTowardsWantedAngle();
  move(Vector2::AngleToVector(m_currentAngle) * m_speed);
}

void Movable::move(float x, float y)
{
  addPosition(x, y);
}

void Movable::move(const Vector2 &distance)
{
  move(distance.X, distance.Y);
}

void Movable::moveRandom(float magnitude)
{
  float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
  setWantedAngle(r);
  moveForward();
}

void Movable::turnTowardsWantedAngle()
{
  float dif = 0;

  if (abs(m_wantedAngle - m_currentAngle) < M_PI)
    dif = m_wantedAngle - m_currentAngle;
  else if (m_wantedAngle > m_currentAngle)
    dif = m_wantedAngle - m_currentAngle - M_PI * 2.0f;
  else
    dif = m_wantedAngle - m_currentAngle + M_PI * 2.0f;

  addAngle(dif * m_turnSpeed);
}
