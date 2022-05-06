#include "chunkManager.h"

ChunkManager::ChunkManager()
{
}

void ChunkManager::generateChunks(int totalWidth, int totalHeight, int chunkWidth)
{
  m_chunkWidth = chunkWidth;
  m_numChunksX = totalWidth / chunkWidth;
  m_numChunksY = totalHeight / chunkWidth;

  for (int y = 0; y < m_numChunksY; y++)
  {
    std::vector<Chunk> row;
    for (int x = 0; x < m_numChunksX; x++)
    {
      row.push_back(Chunk(x, y, m_chunkWidth));
    }
    m_chunks.push_back(row);
  }
}

void ChunkManager::updateChunks(const std::vector<Movable *> &movables)
{
  for (int y = 0; y < m_numChunksY; y++)
  {
    for (int x = 0; x < m_numChunksX; x++)
    {
      Chunk &chunk = m_chunks[y][x];
      chunk.clearChunk();
      for (auto &movable : movables)
      {
        if (chunk.isInChunk(movable))
        {
          chunk.addToChunk(movable);
          movable->setCurrentChunk(&chunk);
        }
      }
    }
  }
};

std::vector<Movable *> ChunkManager::getMovablesInChunk(Chunk *chunk)
{
  if (chunk != nullptr)
    return chunk->getMovables();

  std::cout << "!!! null chunk !!!" << std::endl;
  return std::vector<Movable *>();
}

std::vector<Movable *> ChunkManager::getMovablesInChunkSurrounding(const Vector2 &movablePosition)
{
  std::vector<Movable *> finalMovables;
  int chunkPosX = movablePosition.X / (float)m_chunkWidth;
  int chunkPosY = movablePosition.Y / (float)m_chunkWidth;

  for (int x = -1; x <= 1; x++)
  {
    for (int y = -1; y <= 1; y++)
    {
      int checkPosX = std::clamp(chunkPosX + x, 0, m_numChunksX - 1);
      int checkPosY = std::clamp(chunkPosY + y, 0, m_numChunksY - 1);
      
      std::vector<Movable *> movables = m_chunks[checkPosY][checkPosX].getMovables();
      finalMovables.insert(finalMovables.end(), movables.begin(), movables.end());
    }
  }

  return finalMovables;
}
