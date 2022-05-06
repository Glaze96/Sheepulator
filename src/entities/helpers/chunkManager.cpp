#include "chunkManager.h"

ChunkManager::ChunkManager()
{
}

void ChunkManager::updateChunks(const std::vector<Movable *> &movabales)
{
  for (auto &chunk : m_chunks)
  {
    chunk.clearChunk();
    for (auto &movable : movabales)
    {
      if (chunk.isInChunk(movable))
      {
        chunk.addToChunk(movable);
        movable->setCurrentChunk(&chunk);
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

void ChunkManager::generateChunks(int totalWidth, int totalHeight, int chunkWidth)
{
  // TODO: maybe m_numChunksX - 1 ?? : maybe adding an extra one
  m_chunkWidth = chunkWidth;
  m_numChunksX = totalWidth / chunkWidth;
  m_numChunksY = totalHeight / chunkWidth;
  for (int x = 0; x < m_numChunksX; x++)
  {
    for (int y = 0; y < m_numChunksY; y++)
    {
      m_chunks.push_back(Chunk(x * m_chunkWidth, y * m_chunkWidth, m_chunkWidth));
    }
  }
}