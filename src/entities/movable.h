#pragma once
#include <iostream>
#include "../math/vector2.h"
struct Chunk;
#include "renderable.h"

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

  void moveForward(float multiplier = 1.0f); // Move forward using current direction and speed
  void moveRandom(float magnitude);

  void setCurrentChunk(Chunk* chunk);

private:
  void addAngle(float angle);
  void turnTowardsWantedAngle();
  void setCurrentAngle(float newAngle);

protected:
  float m_speed; // Base speed
  float m_currentAngle; // Radians
  float m_wantedAngle;
  float m_turnSpeed; // Turn speed in steps (radians) 0-1 , 1 = full snap
  Chunk* m_currentChunk;
};