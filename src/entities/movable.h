#pragma once
#include <math.h>
#include "renderable.h"
#include "../math/vector2.h"
#include <iostream>

class Movable : public Renderable
{
public:
  Movable();

public:
  float getAngle() { return m_currentAngle; }
  void setWantedAngle(float newAngle);

public:
  void move(float x, float y);
  void move(const Vector2 &distance);

  void moveForward(); // Move forward using current direction and speed
  void moveRandom(float magnitude);


private:
  void addAngle(float angle);
  void setAngle(float newAngle);
  void turnTowardsWantedAngle();

protected:
  float m_speed; // Base speed
  float m_currentAngle; // Radians
  float m_wantedAngle;
  float m_turnSpeed; // Turn speed in steps (radians) 0-1 , 1 = full snap
};