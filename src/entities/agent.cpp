#include "agent.h"

Agent::Agent(
    const Vector2 &startPos,
    const Vector2 &playArea,
    float speed,
    float currentAngle,
    float turnSpeed,
    ChunkManager &chunkManager,
    std::vector<Movable *> &sheepList,
    std::vector<Movable *> &dogList) : Movable(startPos, playArea, speed, currentAngle, turnSpeed),
                                       m_chunkManager(chunkManager),
                                       m_sheepList(sheepList),
                                       m_dogList(dogList)
{
}

// Find the center position of the flock
Vector2 Agent::findFlockCenter(const std::vector<Movable *> &flock)
{
  float totalX = 0;
  float totalY = 0;
  int count = flock.size();

  for (auto &n : flock)
  {
    totalX += n->getPosition().X;
    totalY += n->getPosition().Y;
  }

  return Vector2(totalX / count, totalY / count);
}

// Get average angle out of all the flock
float Agent::findFlockAngle(const std::vector<Movable *> &flock)
{
  float totalX = 0;
  float totalY = 0;

  for (auto &n : flock)
  {
    totalY += sin(n->getCurrentAngle());
    totalX += cos(n->getCurrentAngle());
  }

  return atan2(totalY, totalX);
}

// SET angle of the flock
void Agent::setFlockAngle(const std::vector<Movable *> &flock, float angle)
{
  for (auto &n : flock)
  {
    n->setWantedAngle(angle);
  }
}

Movable *Agent::findNearest(const std::vector<Movable *> *list)
{
  if (list->size() == 0)
    return nullptr;
  int numMovables = list->size();
  int lastNearest = 0;
  int nearestIndex = 0;
  float minDistance = INFINITY;

  for (int i = 0; i < numMovables; i++)
  {
    float newDistance = Vector2::DistanceSquared(list->at(i)->getPosition(), getPosition());

    // Ignore self
    if (newDistance < 1.0f)
      continue;

    if (newDistance < minDistance)
    {
      nearestIndex = i;
      minDistance = newDistance;
    }
  }
  return list->at(nearestIndex);
}