#include "chunk.h"

Chunk::Chunk(int chunkPosX,
             int chunkPosY,
             int width) : m_worldPosX(chunkPosX * width),
                          m_worldPosY(chunkPosY * width),
                          m_chunkPosX(chunkPosX),
                          m_chunkPosY(chunkPosY),
                          m_width(width){};

bool Chunk::isInChunk(Movable *movable)
{
  Vector2 movablePos = movable->getPosition();
  if (movablePos.X >= m_worldPosX && movablePos.X < m_worldPosX + m_width &&
      movablePos.Y >= m_worldPosY && movablePos.Y < m_worldPosY + m_width)
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
