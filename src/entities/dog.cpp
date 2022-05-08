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
  m_viewRange = 120;
}

void Dog::update()
{
  if (Time::Instance()->FrameCounter % m_smartTick == 0)
  {
    float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
    setWantedAngle(r);
  }

  std::vector<Movable *> nearestSheep = m_chunkManager.getMovablesInChunkSurrounding(getPosition(), m_viewRange);

  // Hearding
  if (nearestSheep.size() > 20)
  {
    Vector2 flockCenter = findFlockCenter(nearestSheep);
    Vector2 difference = flockCenter - getPosition();
    for (auto &sheep : nearestSheep)
    {
      sheep->setWantedAngle((sheep->getPosition() - getPosition()).getAngleRad());
      sheep->moveForward(0.35f);
    }

    setWantedAngle(difference.getAngleRad());
    if (difference.magnitude() > sqrt(nearestSheep.size()) + 10.0f)
      moveForward(0.4f);
  }
  else // idle
  {
    if (Time::Instance()->FrameCounter % m_smartTick == 0)
    {
      std::cout << "idle" << std::endl;
      float r = ((rand() % 1000) / 1000.0f) * M_PI * 2.0f;
      setWantedAngle(r);
    }
  }
  moveForward(0.6f);
}