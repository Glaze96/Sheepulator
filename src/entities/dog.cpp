#include "dog.h"
#include "../globals.h"

Dog::Dog(
    const Vector2 &startPos,
    const Vector2 &playArea,
    float speed,
    float currentAngle,
    float turnSpeed,
    ChunkManager &chunkManager,
    std::vector<Movable *> &sheepList,
    std::vector<Movable *> &dogList) : Agent(startPos, playArea, speed, currentAngle, turnSpeed, chunkManager, sheepList, dogList)
{
  m_smartTick = rand() % 200 + 50;
  m_viewRange = 256;
}

void Dog::update()
{
  std::vector<Movable *> nearestSheep = m_chunkManager.getMovablesInChunkSurrounding(getPosition(), m_viewRange);

  // Hearding
  if (nearestSheep.size() > 20)
  {
    m_time += Time::Instance()->DeltaTime;
    int numSheep = nearestSheep.size();
    for (auto &sheep : nearestSheep)
    {
      sheep->setWantedAngle((sheep->getPosition() - getPosition()).getAngleRad());
      sheep->moveForward(0.35f);
    }

    Vector2 flockCenter = findFlockCenter(nearestSheep);
    // Vector2 difference = flockCenter - getPosition();
    
    // TODO: FIX TANGENT PROBLEM
    Vector2 penPosition = Vector2(Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 2);
    Vector2 penFlockDirection = (penPosition - flockCenter).normalized();
    Vector2 wantedFlockPosition = flockCenter - (penFlockDirection * 50.0f);

    Vector2 tangent = Vector2::VectorFromAngle(penFlockDirection.getAngleRad() * (M_PI / 2.0f));
    float offsetAngle = sin(m_time * M_PI * 0.5f) * sqrt(numSheep) * 2.0f;
    std::cout << offsetAngle << std::endl;
    moveTowardsPosition(wantedFlockPosition + tangent * offsetAngle);
  }
  else // idle
  {
    if (Time::Instance()->FrameCounter % m_smartTick == 0)
    {
      float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
      setWantedAngle(r);
    }
    moveForward(0.2f);
  }
}