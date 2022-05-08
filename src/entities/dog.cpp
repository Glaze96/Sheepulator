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
  std::vector<Movable *> nearestSheep = m_chunkManager.getMovablesInChunkSurrounding(getPosition(), m_viewRange, true);

  m_time += Time::Instance()->DeltaTime;
  // Hearding
  if (nearestSheep.size() > 20)
  {
    int numSheep = nearestSheep.size();
    for (auto &sheep : nearestSheep)
    {
      sheep->setWantedAngle((sheep->getPosition() - getPosition()).getAngleRad());
      sheep->moveForward(0.35f);
    }

    Vector2 flockCenter = findFlockCenter(nearestSheep);
    // Vector2 difference = flockCenter - getPosition();

    // 1. make bigger circles for bigger flocks
    // 2. one dog per flock
    Vector2 penPosition = Vector2(Settings::SCREEN_WIDTH / 2, Settings::SCREEN_HEIGHT / 2);
    Vector2 penFlockDirection = (penPosition - flockCenter).normalized();
    Vector2 test = Vector2::VectorFromAngle(penFlockDirection.getAngleRad() + sin(m_time) * M_PI * 0.45f).normalized() * 50.0f;
    Vector2 wantedFlockPosition = flockCenter - test;

    moveTowardsPosition(wantedFlockPosition);
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