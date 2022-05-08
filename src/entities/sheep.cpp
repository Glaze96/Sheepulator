#define _USE_MATH_DEFINES
#include "sheep.h"
#include <cmath>
#include <algorithm>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <cmath>
#include "../settings.h"
#include "../globals.h"

Sheep::Sheep(const Vector2 &startPos,
             const Vector2 &playArea,
             float speed,
             float currentAngle,
             float turnSpeed,
             float viewRange,
             ChunkManager &chunkManager,
             std::vector<Movable *> &sheepList,
             std::vector<Movable *> &dogList) : Agent(startPos, playArea, speed, currentAngle, turnSpeed, chunkManager, sheepList, dogList), m_viewRange(viewRange)
{
  m_smartTick = rand() % (200) + 100;
}

void Sheep::init()
{
}

/*
 *
 * On sheep update:
 * 1. Clear sheeps position in sheepGrid
 * 2. Move sheep
 * 3. Set new position in sheepGrid
 *
 */
void Sheep::update()
{
  flock();
}

void Sheep::flock()
{

  // std::vector<Movable *> nearestNeighbors = findNeighbors(m_sheepGrid);
  std::vector<Movable *> nearestNeighbors = m_chunkManager.getMovablesInChunkSurrounding(getPosition(), m_viewRange);

  int numNeigbors = nearestNeighbors.size();

  // CHECK FOR FLOCK
  if (numNeigbors >= 15 && !m_inFlock)
  {
    m_inFlock = true;

    m_flockWantedAngle = findFlockAngle(nearestNeighbors);
    m_prefferedFlockPosition = Vector2::RandomUnitVector();
    float distanceFromCenter = (((rand() % 10000) / 10000.0f) + 0.1f) * sqrt(numNeigbors);
    m_flockPositionOffset = m_prefferedFlockPosition * distanceFromCenter;
  }

  if (numNeigbors <= 10)
  {
    m_inFlock = false;
  }

  // FLOCK MOVEMENT
  if (m_inFlock)
  {
    if (Time::Instance()->FrameCounter % (m_smartTick * 2) == 0)
    {
      float flockAvergeAngle = findFlockAngle(nearestNeighbors);
      float randomAngleOffset = (((rand() % 1000) / 500.0f) - 1.0f) * M_PI * 0.5f;
      setFlockAngle(nearestNeighbors, flockAvergeAngle + randomAngleOffset);
      // std::cout << flockAvergeAngle << std::endl;
    }

    if (Time::Instance()->FrameCounter % (m_smartTick * 4) == 0)
    {
      m_prefferedFlockPosition = Vector2::RandomUnitVector();
      float distanceFromCenter = (((rand() % 10000) / 10000.0f) + 0.1f) * sqrt(numNeigbors);
      m_flockPositionOffset = m_prefferedFlockPosition * distanceFromCenter;
    }

    // setCurrentAngle(m_flockWantedAngle);

    Vector2 centerOfFlock = findFlockCenter(nearestNeighbors);

    moveTowardsPosition(centerOfFlock + m_flockPositionOffset, 0.4f);
  }
  else // if NOT in flock
  {
    if (Time::Instance()->FrameCounter % m_smartTick == 0)
    {
      float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
      setWantedAngle(r);
    }
  }

  Vector2 currentPos = getPosition();
  float wallBuffer = 60.0f;

  if (currentPos.X < wallBuffer || m_playArea.X - currentPos.X < wallBuffer ||
      currentPos.Y < wallBuffer || m_playArea.Y - currentPos.Y < wallBuffer)
  {
    Vector2 differenceToCenter = Vector2(m_playArea.X / 2.0f, m_playArea.Y / 2.0f) - currentPos;
    float newAngle = differenceToCenter.getAngleRad();
    setWantedAngle(newAngle);
    // std::cout << "at edge" << std::endl;
  }

  if (m_inFlock)
  {
    moveForward(1.0f);
  }
  else
  {
    moveForward(0.2f);
  }
}
