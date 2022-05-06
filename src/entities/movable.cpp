#define _USE_MATH_DEFINES
#include "movable.h"
#include <cmath>
#include "../globals.h"

Movable::Movable()
{
  float val = (rand() % 1000) / 1000.0f;
  setCurrentAngle(val * M_PI * 2.0f);
  setWantedAngle(val * M_PI * 2.0f);
}

void Movable::addAngle(float addAngle)
{
  setCurrentAngle(m_currentAngle + addAngle);
}

void Movable::setWantedAngle(float newAngle)
{
  m_wantedAngle = fmod(newAngle, M_PI * 2.0f);
  if (m_currentAngle < 0)
    m_wantedAngle += M_PI * 2.0f;
}

void Movable::setCurrentChunk(Chunk *chunk) {
  m_currentChunk = chunk;
}

void Movable::setCurrentAngle(float newAngle)
{
  m_currentAngle = fmod(newAngle, M_PI * 2.0f);
  if (m_currentAngle < 0)
    m_currentAngle += M_PI * 2.0f;
}

void Movable::moveForward(float multiplier)
{
  turnTowardsWantedAngle();
  move(Vector2::VectorFromAngle(m_currentAngle) * m_speed * multiplier);
}

void Movable::move(float x, float y)
{
  addPosition(x * Time::Instance()->DeltaTime, y * Time::Instance()->DeltaTime);
}

void Movable::move(const Vector2 &distance)
{
  move(distance.X, distance.Y);
}

void Movable::moveRandom(float magnitude)
{
  // float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
  // setWantedAngle(r);
  // setWantedAngle(M_PI);
  // moveForward();
  std::cout << "MOVE RANDOM NOT IMPLEMENTED" << std::endl;
}

void Movable::turnTowardsWantedAngle()
{
  float dif = 0;
  
  // create difference const variable

  if (abs(m_wantedAngle - m_currentAngle) < M_PI)
    dif = m_wantedAngle - m_currentAngle;
  else if (m_wantedAngle > m_currentAngle)
    dif = m_wantedAngle - m_currentAngle - M_PI * 2.0f;
  else
    dif = m_wantedAngle - m_currentAngle + M_PI * 2.0f;

  addAngle(dif * m_turnSpeed);
}
