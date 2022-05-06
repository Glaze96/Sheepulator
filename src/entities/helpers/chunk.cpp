#include "chunk.h"

Chunk::Chunk(int worldPosX, int worldPosY, int width) : m_worldPosX(worldPosX), m_worldPosY(worldPosY), m_width(width){};

bool Chunk::isInChunk(Movable *movable)
{
  Vector2 movablePos = movable->getPosition();
  Vector2 chunkPos = Vector2(m_worldPosX, m_worldPosY);
  if (movablePos.X >= chunkPos.X && movablePos.X < chunkPos.X + m_width &&
      movablePos.Y >= chunkPos.Y && movablePos.Y < chunkPos.Y + m_width)
  {
    return true;
  }
  return false;
};

void Chunk::addToChunk(Movable *movable)
{
  m_movables.push_back(movable);
}

void Chunk::clearChunk()
{
  m_movables.clear();
}

std::vector<Movable *> Chunk::getMovables()
{
  return m_movables;
}
