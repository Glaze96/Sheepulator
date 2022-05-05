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
  float getAngle() { return m_directionAngle; }
  void setAngle(float newAngle) {
    m_directionAngle = fmod(newAngle, M_PI * 2.0);
  };

  void addAngle(float angle);

public:
  void move(float x, float y);
  void move(const Vector2 &distance);

  void moveForward(); // Move forward using direction and speed
  void moveRandom(float magnitude);

  void turnTowardsAngle(float targetAngle);


protected:
  float m_speed; // Base speed
  float m_directionAngle; // Radians
  float m_turnSpeed; // Turn speed in steps (radians) 1 = full snap
};