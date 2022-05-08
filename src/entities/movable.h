#pragma once
#include <iostream>
#include "../math/vector2.h"
struct Chunk;
#include "renderable.h"

class Movable : public Renderable
{
public:
  Movable(const Vector2 &startPos, const Vector2 &playArea, float speed, float currentAngle, float turnSpeed);

public:
  float getCurrentAngle() { return m_currentAngle; }
  float getWantedAngle() { return m_wantedAngle; }
  void setWantedAngle(float newAngle);
  void setCurrentAngle(float newAngle);

public:
  void move(float x, float y);
  void move(const Vector2 &distance);

  void moveForward(float multiplier = 1.0f); // Move forward using current direction and speed
  void moveRandom(float magnitude);

  void setCurrentChunk(Chunk* chunk);
  void moveTowardsPosition(Vector2 pos, float multiplier = 1.0f, float distanceCap = 2.0f);

private:
  void addAngle(float angle);
  void turnTowardsWantedAngle();

protected:
  float m_speed; // Base speed
  float m_currentAngle; // Radians
  float m_wantedAngle;
  float m_turnSpeed; // Turn speed in steps (radians) 0-1 , 1 = full snap
  Chunk* m_currentChunk;
  Vector2 m_playArea;
};